#include "thread.h"
#include "types.h"

static thd_t*   thd_queue[MAX_THREADS];
static thd_t*   cur_thd_data;
static uint32_t curr_thd_entry;
static thd_t    main_thd_data; // prio == 0, rest > 0 and not the same

static void
thd_init_queue(thd_t* thd)
{
	if (!curr_thd_entry)
	{
		cur_thd_data =  thd_queue[0] = &main_thd_data;
		curr_thd_entry++;
	}

	thd_queue[curr_thd_entry] = thd;
	curr_thd_entry++;
}

static thd_t*
thd_of_prio(void)
{
	uint32_t thd_size = 0;
	uint32_t  min_entry = 0;
	int32_t max_prio_thd = -1;

	for ( ; thd_size < MAX_THREADS; thd_size++ )
	{
		if ((thd_queue[thd_size]->prio > min_entry) &&
		    (thd_queue[thd_size]->state == THREAD_SLEEPING) &&
			(thd_queue[thd_size]->signal))
		{
			min_entry 	 = thd_queue[thd_size]->prio;
			max_prio_thd = thd_size;
		}
	}

	return (max_prio_thd == -1) ? 0 : thd_queue[max_prio_thd];
}

static void
thd_switch(thd_t* to, thd_t* from)
{
	__asm volatile ("cpsid 	i");

	to->state    = THREAD_RUNNING;
	cur_thd_data = to;
	from->state  = THREAD_SLEEPING;

	__ctxt_switch((uint32_t)to, (uint32_t)from);
}

static void
thd_priv_init(thd_t *thd_data)
{
	thd_data->r4  = 0;
	thd_data->r5  = 0;
	thd_data->r6  = 0;
	thd_data->r7  = 0;
	thd_data->r8  = 0;
	thd_data->r9  = 0;
	thd_data->r10 = 0;
	thd_data->r11 = 0;
	thd_data->sp  = 0;
	thd_data->lr  = 0;
	thd_data->f = (void *)0;

	for (uint8_t msg_size = 0; msg_size < THREAD_MAX_MESSAGE; msg_size++)
	{
		thd_data->msg[msg_size].type = 0;
		thd_data->msg[msg_size].data = 0;
	}
	thd_data->state = THREAD_SLEEPING;
	thd_data->prio  = 0;

	thd_data->msg_index = 0;
	thd_data->signal    = 0;
}


void
thd_sys_init(void)
{
	for (uint8_t count = 0; count < MAX_THREADS; count++)
	{
		thd_queue[count] = 0;
	}
	cur_thd_data = 0;
	curr_thd_entry = 0;
	thd_priv_init(&main_thd_data);
}

thd_t *
thd_create(thd_func_t thd_f, void* wrk_area, uint32_t prio)
{
	uint32_t *data_area = (uint32_t *)((uint32_t)wrk_area & 0xFFFFFFFC);
	thd_t    *thd_data;
	uint8_t   msg_size;

	thd_data = (thd_t *)data_area;
	thd_priv_init(thd_data);

	data_area += sizeof(thd_t);

	thd_data->sp  = (uint32_t)thd_data;
	thd_data->prio  = prio;
	thd_data->lr = (uint32_t)thd_f;
	thd_data->f  = thd_f;

	thd_init_queue(thd_data);

	return thd_data;
}

void
thd_schd(void)
{
	thd_t * to_thd_ptr   = thd_of_prio();
	thd_t * from_thd_ptr = cur_thd_data;
	uint32_t result;

	if (to_thd_ptr != 0U)
	{
		__asm volatile ("MRS %0, psp"  : "=r" (result) );

		from_thd_ptr->sp = result;

		thd_switch(to_thd_ptr, from_thd_ptr);
	}
	else
	{
		__asm volatile ("WFI");
	}
}


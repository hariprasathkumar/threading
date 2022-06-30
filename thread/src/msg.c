#include "msg.h"


static uint32_t
msg_get_index(thd_t* to)
{
	uint32_t signal_prio = 0;

	while ((to->signal) && (signal_prio < THREAD_MAX_MESSAGE))
	{
		if (to->signal & (1 << signal_prio))
		{
			to->signal &= ~((uint32_t)(1 << signal_prio));

			break;
		}

		signal_prio++;
	}

	return (signal_prio == THREAD_MAX_MESSAGE) ? MSG_BOX_EMPTY : signal_prio;
}

static uint32_t
msg_set_index(thd_t* to)
{
	uint32_t signal_prio = 0;

	while (signal_prio < THREAD_MAX_MESSAGE)
	{
		if (!(to->signal & (1 << signal_prio)))
		{
			to->signal |= ((uint32_t)(1 << signal_prio));

			break;
		}

		signal_prio++;
	}

	return (signal_prio == THREAD_MAX_MESSAGE) ? MSG_BOX_FULL : signal_prio;
}

uint32_t
msg_post(thd_t* to, thd_priv_t *msg)
{
	uint32_t msg_index ;
	uint32_t ret = MSG_ACTION_FAILURE;

	if ( (msg_index = msg_set_index(to)) != MSG_BOX_FULL)
	{
		to->msg[msg_index].type = msg->type;
		to->msg[msg_index].data = msg->data;

		ret = MSG_ACTION_SUCCESS;
	}

	return ret;
}

uint32_t
msg_retrieve(thd_t* to, thd_priv_t *msg)
{
	uint32_t msg_index;
	uint32_t ret = MSG_ACTION_FAILURE;

	if ( (msg_index = msg_get_index(to)) != MSG_BOX_EMPTY)
	{
		msg->type = to->msg[msg_index].type;
		msg->data = to->msg[msg_index].data;

		ret = MSG_ACTION_SUCCESS;
	}

	return ret;
}


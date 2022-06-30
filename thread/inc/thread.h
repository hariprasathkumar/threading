#ifndef THREAD_INC_THREAD_H_
#define THREAD_INC_THREAD_H_

#include "types.h"

#define THREAD_MAX_MESSAGE	(10U)
#define MAX_THREADS			(3U)
#define THREAD_SP_OFFSET	()

typedef void (*thd_func_t)(void *);

typedef enum {
	THREAD_RUNNING,
	THREAD_SLEEPING,
} thd_state_t;

typedef struct {
	uint32_t type;
	void*    data;
} thd_priv_t;

typedef struct {
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t lr;
	uint32_t sp;
	thd_func_t  f;
	thd_priv_t  msg[THREAD_MAX_MESSAGE];
	uint32_t    prio;
	uint32_t    msg_index;
	uint32_t    signal;
	thd_state_t state;
} thd_t;


thd_t *
thd_create(thd_func_t thd_f, void* wrk_area, uint32_t prio);

extern
void __ctxt_switch(uint32_t to, uint32_t from);

void
thd_sys_init(void);

void
thd_schd(void);

#endif /* THREAD_INC_THREAD_H_ */

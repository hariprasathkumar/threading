#include "timer.h"

#include "gpio.h"
#include "types.h"
#include "msg.h"

static t_func_t f;

static uint32_t
timer_get_port_base(uint32_t port)
{
	const uint32_t addr[1] = {
			TIMER_BASE,
	};

	if (port > 1)
	{
		return 0;
	}
	else
	{
		return addr[port];
	}
}


void
timer_periodic_init(uint32_t timer_sel, t_func_t callback)
{
	uint32_t timer_base = timer_get_port_base(timer_sel);

	// ensure timer is disabled (tnen = 0)
	REG(timer_base + TIMER_CONTROL) &= ~1;
	REG(timer_base + TIMER_SYNCHRONIZE) = 1;
	// write config reg = 0
	REG(timer_base + TIMER_CFG) = 0;
	// configure tnmr with 0x02 for periodic mode
	REG(timer_base + TIMER_TIMERA_MODE) = 2;
	// load start value into interval load register
	REG(timer_base + TIMER_TIMERA_INTERVAL_LOAD) = 0xFFFFFF;
	// set appropriate interrupt mask reg
	REG(timer_base + TIMER_IRQ_MASK) = 1;
	// set tnen = 1
	REG(timer_base + TIMER_CONTROL) |= 1;

	f = callback;
}


void
systimer_handler(void)
{
	  f();

	  /* unused */
	  REG(TIMER_BASE + TIMER_IRQ_CLEAR) = 1;
}


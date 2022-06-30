/*
 * tick.h
 *
 *  Created on: 21-Jun-2022
 *      Author: focal
 */

#ifndef HAL_INC_TIMER_H_
#define HAL_INC_TIMER_H_

#include "types.h"

#define TIMER_BASE			(0x40030000)
#define TIMER_CFG 			(0x000)
#define TIMER_TIMERA_MODE	(0x004)
#define TIMER_TIMERB_MODE	(0x008)
#define TIMER_CONTROL		(0x00C)
#define TIMER_SYNCHRONIZE	(0x010)
#define TIMER_IRQ_MASK		(0x018)
#define TIMER_RAW_STATUS	(0x01C)
#define TIMER_MASKD_STATUS	(0x020)
#define TIMER_IRQ_CLEAR		(0x024)
#define TIMER_TIMERA_INTERVAL_LOAD	(0x028)
#define TIMER_TIMERB_INTERVAL_LOAD	(0x02C)
#define TIMER_TIMEA_MATCH			(0x030)
#define TIMER_TIMEB_MATCH			(0x034)
#define TIMER_TIMEA_PRESCALE		(0x038)
#define TIMER_TIMEB_PRESCALE		(0x03C)
#define TIMER_TIMEA_PRESCALE_MATCH	(0x040)
#define TIMER_TIMEB_PRESCALE_MATCH	(0x044)
#define TIMER_TIMER_A				(0x048)
#define TIMER_TIMER_B				(0x04C)
#define TIMER_TIMER_A_VALUE			(0x050)
#define TIMER_TIMER_B_VALUE			(0x054)
#define TIMER_TIMER_RTC_PREDIVIDE	(0x058)
#define TIMER_TIMER_A_PRESCALE_SNAPSHOT	(0x05C)
#define TIMER_TIMER_B_PRESCALE_SNAPSHOT	(0x060)
#define TIMER_TIMER_A_PRESCALE_VALUE	(0x064)
#define TIMER_TIMER_B_PRESCALE_VALUE	(0x068)
#define TIMER_TIMER_PERIPH_PROPERTIES	(0xFC0)

#define TIMER_SEL_A	(0u)

typedef void (*t_func_t)(void);

void
timer_periodic_init(uint32_t timer_sel, t_func_t callback);

void
systimer_handler(void);


#endif /* HAL_INC_TIMER_H_ */

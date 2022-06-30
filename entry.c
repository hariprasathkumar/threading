#include "sysctrl.h"
#include "gpio.h"
#include "timer.h"
#include "thread.h"
#include "types.h"
#include "msg.h"
#include "nvic.h"

extern unsigned int __thd1_wrk_area_start__;
extern unsigned int __thd2_wrk_area_start__;
thd_t* thread_ref1;
thd_t* thread_ref2;
uint32_t color;

#define MSG_NONE			(0U)
#define MSG_CHG_COLOR		(1U)

#define MSG_CHG_COLOR_RED	(0U) /* red */
#define MSG_CHG_COLOR_BLUE	(1U) /* blue */
#define MSG_CHG_COLOR_GREEN	(2U) /* green */

static uint32_t*
chg_color(void)
{
	color++;

	if (color == (MSG_CHG_COLOR_GREEN+1))
	{
		color = MSG_CHG_COLOR_RED;
	}

	return &color;
}

static void
pwrdwn_leds(void)
{
	gpio_clr(GPIO_SEL_PORT_F, 1);
	gpio_clr(GPIO_SEL_PORT_F, 2);
	gpio_clr(GPIO_SEL_PORT_F, 3);
}

void
timer_callback(void)
{
	thd_priv_t msg;

	msg.type = MSG_CHG_COLOR;
	msg.data     = (void*)chg_color();

	msg_post(thread_ref1, &msg);

	msg.type = MSG_CHG_COLOR;
	msg.data     = (void*)chg_color();

	msg_post(thread_ref2, &msg);

}

static void
hal_init(void)
{
	sysctrl_clock_enable(SYSCTRL_PERIPH_GPIO_F);

	/* 1 (R), 2 (B), 3 (G) */
	gpio_out_en(GPIO_SEL_PORT_F, 1);
	gpio_out_en(GPIO_SEL_PORT_F, 2);
	gpio_out_en(GPIO_SEL_PORT_F, 3);

	sysctrl_clock_enable(SYSCTRL_PERIPH_TIMER_A);
	timer_periodic_init(TIMER_SEL_A, timer_callback);

	nvic_set_enable(19);
	nvic_set_priority(19, 1);
}


static void
thread1_f(void* p)
{
	thd_priv_t msg;

	while (1)
	{
		msg_retrieve(thread_ref1, &msg);

		pwrdwn_leds();
		gpio_clr(GPIO_SEL_PORT_F, *(uint32_t *)msg.data + 1);

		thd_schd();
	}
}

static void
thread2_f(void* p)
{
	thd_priv_t msg;

	while (1)
	{
		msg_retrieve(thread_ref2, &msg);

		pwrdwn_leds();
		gpio_set(GPIO_SEL_PORT_F, *(uint32_t *)msg.data + 1);

		thd_schd();
	}
}
/*
 * A simple multi threading project from scratch
 * */

void entry(void)
{
	/* HW init */
	hal_init();
	color = MSG_CHG_COLOR_RED;

	thd_sys_init();
	thread_ref1 = thd_create(thread1_f, (void *)&__thd1_wrk_area_start__, 1);
	thread_ref2 = thd_create(thread2_f, (void *)&__thd2_wrk_area_start__, 2);

	__asm volatile ("cpsie 	i");


	while(1)
	{
		thd_schd();
	}
}

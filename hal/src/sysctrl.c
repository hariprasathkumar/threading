#include "types.h"
#include "sysctrl.h"

#define SYSCTRL_BASE				(0x400FE000U)

/* Clock enable */
#define SYSCTRL_GPIO_CLOCK_GATE		(0x608U)
#define SYSCTRL_GPIO_CLOCK_GATE_2	(0x608U)
#define SYSCTRL_GPIO_CLOCK_GATE_3	(0x608U)
#define SYSCTRL_TIMER_CLOCK_GATE	(0x604U)


void
sysctrl_clock_enable(uint32_t periph)
{
	switch(periph)
	{
		case SYSCTRL_PERIPH_GPIO_A:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |= (1U << 0U);
			break;
		}

		case SYSCTRL_PERIPH_GPIO_B:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |= (1U << 1U);
			break;
		}

		case SYSCTRL_PERIPH_GPIO_C:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |=	(1U << 2U);
			break;
		}

		case SYSCTRL_PERIPH_GPIO_D:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |= (1U << 3U);
			break;
		}

		case SYSCTRL_PERIPH_GPIO_E:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |= (1U << 4U);
			break;
		}

		case SYSCTRL_PERIPH_GPIO_F:
		{
			REG(SYSCTRL_BASE + SYSCTRL_GPIO_CLOCK_GATE) |= (1U << 5U);
			break;
		}

		case SYSCTRL_PERIPH_TIMER_A:
		{
			REG(SYSCTRL_BASE + SYSCTRL_TIMER_CLOCK_GATE) |= (1U << 0U);
			break;
		}
		default:
		{
			break;
		}
	}
}

#ifndef HAL_INC_SYSCTRL_H_
#define HAL_INC_SYSCTRL_H_

#include <stdint.h>


#define SYSCTRL_PERIPH_GPIO_A	(1U << 0U)
#define SYSCTRL_PERIPH_GPIO_B	(1U << 1U)
#define SYSCTRL_PERIPH_GPIO_C	(1U << 2U)
#define SYSCTRL_PERIPH_GPIO_D	(1U << 3U)
#define SYSCTRL_PERIPH_GPIO_E	(1U << 4U)
#define SYSCTRL_PERIPH_GPIO_F	(1U << 5U)
#define SYSCTRL_PERIPH_TIMER_A	(1U << 6U)

void
sysctrl_clock_enable(uint32_t periph);


#endif /* HAL_INC_SYSCTRL_H_ */

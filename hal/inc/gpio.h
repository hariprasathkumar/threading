
#ifndef HAL_INC_GPIO_H_
#define HAL_INC_GPIO_H_

#include <stdint.h>

#define GPIO_SEL_PORT_A		(0U)
#define GPIO_SEL_PORT_B		(1U)
#define GPIO_SEL_PORT_C		(2U)
#define GPIO_SEL_PORT_D		(3U)
#define GPIO_SEL_PORT_E		(4U)
#define GPIO_SEL_PORT_F		(5U)

void
gpio_out_en(uint32_t port, uint32_t io_no);

void
gpio_clr(uint32_t port, uint32_t io_no);

void
gpio_set(uint32_t port, uint32_t io_no);


#endif /* HAL_INC_GPIO_H_ */

#include "types.h"
#include "gpio.h"

#define GPIO_PORT_A_BASE	(0x40004000U)
#define GPIO_PORT_B_BASE	(0x40005000U)
#define GPIO_PORT_C_BASE	(0x40006000U)
#define GPIO_PORT_D_BASE	(0x40007000U)
#define GPIO_PORT_E_BASE	(0x40024000U)
#define GPIO_PORT_F_BASE	(0x40025000U)

#define GPIO_DATA			(0x000U)
#define GPIO_DIR			(0x400U)
#define GPIO_PD				(0x514U)
#define GPIO_EN				(0x51CU)

static uint32_t
gpio_get_port_base(uint32_t port)
{
	const uint32_t addr[6] = {
			GPIO_PORT_A_BASE,
			GPIO_PORT_B_BASE,
			GPIO_PORT_C_BASE,
			GPIO_PORT_D_BASE,
			GPIO_PORT_E_BASE,
			GPIO_PORT_F_BASE
	};

	if (port > 5)
	{
		return 0;
	}
	else
	{
		return addr[port];
	}
}

void
gpio_set(uint32_t port, uint32_t io_no)
{
	uint32_t reg_base = gpio_get_port_base(port);

	if (io_no > 7)
	{
		return;
	}

	REG(reg_base + GPIO_DATA + (1 << (io_no + 2))) = (1 << io_no);
}

void
gpio_clr(uint32_t port, uint32_t io_no)
{
	uint32_t reg_base = gpio_get_port_base(port);

	if (io_no > 7)
	{
		return;
	}

	REG(reg_base + GPIO_DATA + (1 << (io_no + 2))) = 0;
}

void
gpio_out_en(uint32_t port, uint32_t io_no)
{
	uint32_t reg_base = gpio_get_port_base(port);

	if (io_no > 7)
	{
		return;
	}

	REG(reg_base + GPIO_DIR) |= (1 << io_no);
	REG(reg_base + GPIO_PD)	 |= (1 << io_no);
	REG(reg_base + GPIO_EN)  |= (1 << io_no);
}


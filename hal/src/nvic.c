#include "types.h"
#include "nvic.h"

void
nvic_set_enable(uint32_t irq_no)
{
	uint32_t reg_ofs = (irq_no >> 5U);
	uint32_t en_bit  =  irq_no - (reg_ofs << 5);

	REG(NVIC_BASE + NVIC_EN_REG_OFS + (reg_ofs << 2U)) |= (1U << en_bit);
}

void
nvic_set_priority(uint32_t irq_no, uint32_t prio)
{
	uint32_t shift   = ((irq_no & 0x03U) << 3U);
	uint32_t ofs     = ((irq_no >> 2U) << 2U);

	REG(NVIC_BASE + NVIC_PRI_REG_OFS + ofs) &= ~((uint32_t)(0xE0U << shift));
	REG(NVIC_BASE + NVIC_PRI_REG_OFS + ofs) |=  (((prio << 5U) & 0xE0U) <<  shift);
}


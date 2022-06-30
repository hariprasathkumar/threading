

#ifndef HAL_INC_NVIC_H_
#define HAL_INC_NVIC_H_

#define NVIC_BASE			(0xE000E000U)

#define NVIC_EN_REG_OFS		(0x00000100U)
#define NVIC_PRI_REG_OFS	(0x00000400U)

void
nvic_set_enable(uint32_t irq_no);

void
nvic_set_priority(uint32_t irq_no, uint32_t prio);

#endif /* HAL_INC_NVIC_H_ */

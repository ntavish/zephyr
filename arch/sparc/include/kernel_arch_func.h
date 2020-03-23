/*
 * Copyright (c) 2018 ispace, inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Private kernel definitions (SPARC)
 *
 */

/* this file is only meant to be included by kernel_structs.h */

#ifndef ZEPHYR_ARCH_SPARC_INCLUDE_KERNEL_ARCH_FUNC_H_
#define ZEPHYR_ARCH_SPARC_INCLUDE_KERNEL_ARCH_FUNC_H_

#include <kernel_arch_data.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

extern K_THREAD_STACK_ARRAY_DEFINE(z_interrupt_stacks, CONFIG_MP_NUM_CPUS,
				   CONFIG_ISR_STACK_SIZE);

/**
 * @brief Perform architecture-specific initialization
 *
 * This routine performs architecture-specific initialization of the
 * kernel.  Trivial stuff is done inline; more complex initialization
 * is done via function calls.
 *
 * @return N/A
 */
static ALWAYS_INLINE void arch_kernel_init(void)
{
	/* It's safe to set it here. Even though we use
	 * z_interrupt_stacks for kernel initialization, we currently do
	 * not enable Trap while in exception handler.  We do enable
	 * it in interrupt handler, though.
	 */
	_kernel.irq_stack =
		Z_THREAD_STACK_BUFFER(z_interrupt_stacks[0]) +
				      CONFIG_ISR_STACK_SIZE;
}

/* SPARC currently supports USE_SWITCH and USE_SWITCH only */
void arch_switch(void *switch_to, void **switched_from);

static inline bool arch_is_in_isr(void)
{
	return _kernel.nested != 0U;
}

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_ARCH_SPARC_INCLUDE_KERNEL_ARCH_FUNC_H_ */

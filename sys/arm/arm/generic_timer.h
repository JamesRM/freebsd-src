/*-
 * Copyright (C) 2015-2021 Mihai Carabas <mihai.carabas@gmail.com>
 * Copyright (C) 2017-2019 Alexandru Elisei <alexandru.elisei@gmail.com>
 * Copyright (C) 2017-2021 Darius Mihai <darius.mihai.m@gmail.com>
 * Copyright (C) 2019-2021 Andrei Martin <andrei.cos.martin@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _ARM_GENERIC_TIMER_H_
#define _ARM_GENERIC_TIMER_H_

#define	GT_PHYS_SECURE		0
#define	GT_PHYS_NONSECURE	1
#define	GT_VIRT			2
#define	GT_HYP			3

int	arm_tmr_setup_intr(int gt_type, driver_filter_t filter,
    driver_intr_t handler, void *arg);
int	arm_tmr_teardown_intr(int gt_type);

#endif

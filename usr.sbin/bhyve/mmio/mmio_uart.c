/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright TODO
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/linker_set.h>

#include <sys/param.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

#include <machine/vmm.h>
#include <vmmapi.h>

#include "bhyverun.h"
#include "debug.h"

#include "mmio_emul.h"
#include "mmio_virtio.h"
#include "uart_emul.h"

static void
mmio_uart_intr_assert(void *arg, uint32_t irq)
{
	struct vmctx *ctx = arg;

	vm_assert_irq(ctx, irq, 0);
}

static void
mmio_uart_intr_deassert(void *arg, uint32_t irq)
{
	struct vmctx *ctx = arg;

	vm_deassert_irq(ctx, irq, 0);
}

static int
mmio_uart_init(struct vmctx *ctx, struct mmio_devinst *pi, char *opts)
{
	struct uart_softc *sc;

	sc = uart_init(mmio_uart_intr_assert, mmio_uart_intr_deassert, ctx);
	if (uart_set_backend(sc, "stdio") != 0) {
		EPRINTLN("Unable to initialize backend '%s' for "
		    "mmio_uart", "stdio");
		return (-1);
	}

	pi->pi_arg = sc;
	sc->irqno = pi->di_lintr.irq;

	mmio_alloc_mem(pi);

	return (0);
}

static void
mmio_uart_write(struct vmctx *ctx, int vcpu, struct mmio_devinst *di,
		int baridx, uint64_t offset, int size, uint64_t value)
{
	struct uart_softc *sc = di->pi_arg;
	long reg = offset >> 2;

	uart_write(sc, reg, value);
}

uint64_t
mmio_uart_read(struct vmctx *ctx, int vcpu, struct mmio_devinst *di,
		int baridx, uint64_t offset, int size)
{
	struct uart_softc *sc = di->pi_arg;
	long reg = offset >> 2;

	return uart_read(sc, reg);
}

struct mmio_devemu mmio_uart = {
	.de_emu =	"mmio-uart",
	.de_init =	mmio_uart_init,
	.de_write =	mmio_uart_write,
	.de_read =	mmio_uart_read
};
MMIO_EMUL_SET(mmio_uart);

#
# $FreeBSD$
#

.PATH: ${BHYVE_SRCTOP}/mmio/
SRCS+=	\
	mmio/block_if.c	\
	mmio/mmio_uart.c	\
	mmio/mmio_virtio.c	\
	mmio/mmio_virtio_block.c	\
	mmio/mmio_virtio_console.c	\
	mmio/mmio_virtio_net.c		\
	mmio/mmio_virtio_rnd.c		\
	mmio/mmio_emul.c		\
	mmio/mmio_irq.c			\
	mmio/net_backends.c	\
	mmio/net_utils.c		\
	mmio/pl011.c	\
	mmio/uart_backend.c



CFLAGS+=	-I${BHYVE_SRCTOP}/mmio

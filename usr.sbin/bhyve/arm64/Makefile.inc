#
# $FreeBSD$
#
.PATH: ${BHYVE_SRCTOP}/arm64/
SRCS+=				\
	arm64/bhyverun.c 	\
	arm64/mem.c		\
	arm64/mmio_uart.c	\
	arm64/pl011.c	\
	arm64/reset.c	\
	arm64/uart_backend.c

.PATH:	${BHYVE_SYSDIR}/sys/${BHYVE_ARCH}/vmm

MK_MAN=no

BHYVE_BUS= mmio

CFLAGS+= 	-I${BHYVE_SYSDIR}/sys/dev/virtio/mmio

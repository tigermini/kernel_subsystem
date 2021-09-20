# ttimer Makefile

KERNELDIR := /usr/lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

obj-m := ttimer.o
ttimer-objs += main.o

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

.PHONY:all clean


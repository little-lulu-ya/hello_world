ifneq ($(KERNELRELEASE),)
	obj-m:=testmodule2.o
else
	PWD:=$(shell pwd)
	KDIR:=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
endif

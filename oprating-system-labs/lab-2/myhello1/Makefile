#Makefile 2.6

obj-m :=myhello.o
KERNAL :=/home/ubnutu/linux-4.19.152/
PWD :=$(shell pwd)
modules :
	$(MAKE) -C $(KERNAL) M=$(PWD) modules
.PHONEY:clean
clean :
	rm -rf *.o *.ko *.cmd Module.symvers modules.order *.mod.c .myhello* .tmp*
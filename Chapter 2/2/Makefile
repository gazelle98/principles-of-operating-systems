obj-m += os2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod os2.ko

test:
	cat /proc/seconds

remove:
	-sudo rmmod os2
	sudo dmesg -C

                       
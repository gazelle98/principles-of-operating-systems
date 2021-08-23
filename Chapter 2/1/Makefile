obj-m += os1.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	cat /proc/jiffies

remove:
	-sudo rmmod os1
	sudo dmesg -C

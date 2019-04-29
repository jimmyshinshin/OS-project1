#include <linux/linkage.h>
#include <linux/kernel.h>


asmlinkage void sys_my_printk(char msg[])
{
	printk(msg);
}

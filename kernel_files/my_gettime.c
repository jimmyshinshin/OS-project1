#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/ktime.h>


asmlinkage void sys_my_gettime(unsigned long* s, unsigned long* ns )
{
	struct timespec now;
	getnstimeofday(&now);
	*s = now.tv_sec;
	*ns = now.tv_nsec;
}

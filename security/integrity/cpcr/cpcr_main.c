//
// Created by sspku on 2021/7/7.
//
#include <linux/module.h>

static int __init init_cpcr(void)
{
	printk(KERN_ALERT "cPCR Module start test!");
	return 0;
}

late_initcall(init_cpcr);

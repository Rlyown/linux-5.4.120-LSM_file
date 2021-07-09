//file_sec_opt.c
//demo for file_security_operations test

#include <linux/lsm_hooks.h>
#include <linux/sysctl.h>

//static int demo_file_sec_opt (struct file *file, int mask)
static int demo_file_sec_opt (struct file *file, int mask)
{
	printk(KERN_INFO "[+ xiaolei_test] call file_permission hook!!!!!\n");
//	printk("[+ xiaolei_test] call task_alloc hook!!!!!\n");
	printk(KERN_INFO "[+ xiaolei_test] 'file_path' of the access file is:%s\n",file->f_path.dentry->d_iname);
	printk(KERN_INFO "[+ xiaolei_test] 'file_path' of the access file is:%s\n",file->f_path.dentry->d_name.name);
	printk(KERN_INFO "[+ xiaolei_test] 'mask' of the access file is:%d\n",mask);
	return 0;
}

static struct security_hook_list demo_file_sec_opt_hook[] = {
		LSM_HOOK_INIT(file_permission,demo_file_sec_opt),
};


void __init demo_add_file_hook(void)
{
	printk(KERN_INFO "[+ xiaolei_test_init]File_sec-opt_demo: becoming mindful.\n");
	security_add_hooks(demo_file_sec_opt_hook,ARRAY_SIZE(demo_file_sec_opt_hook),"file_sec_opt");
}

static __init int demo_file_opt_init(void){
	demo_add_file_hook();
	return 0;
}

//security_initcall(demo_file_opt_init);
DEFINE_LSM(file_sec_opt) = {
	.name = "file_security_operation",
	.init = demo_file_opt_init,
};


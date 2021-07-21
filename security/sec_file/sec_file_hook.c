#include <linux/lsm_hooks.h>
#include <linux/sysctl.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/export.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/pagemap.h>
#include <linux/fsnotify.h>
#include <linux/personality.h>
#include <linux/security.h>
#include <linux/ima.h>
#include <linux/syscalls.h>
#include <linux/mount.h>
#include <linux/audit.h>
#include <linux/capability.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/device_cgroup.h>
#include <linux/fs_struct.h>
#include <linux/posix_acl.h>
#include <linux/hash.h>
#include <linux/bitops.h>
#include <linux/init_task.h>
#include <linux/uaccess.h>
#include <linux/path.h>









// hook function
static int sec_file_file_permission(struct file *file, int mask)
{
	// only deal with the file_name which contain '.'
	if (strstr(file->f_path.dentry->d_iname, "."))
	{
		printk("[+xiaolei - %s - %s - %d] - catch the hook of file_permission!!!\n", __FILE__, __func__,__LINE__);
		printk("[+xiaolei - %s - %s - %d]-  call file_permission hook!!!!!\n", __FILE__, __func__,__LINE__);
		printk("[+xiaolei - %s - %s - %d]-  'file_name' of the access file is:%s\n",__FILE__, __func__,__LINE__, file->f_path.dentry->d_iname);
		printk("[+xiaolei - %s - %s - %d]-  'mask' of the access file is:%d\n", __FILE__, __func__,__LINE__, mask);
	}
	return 0;
}


static int sec_file_path_unlink(const struct path *dir, struct dentry *dentry)
{
	printk("[+xiaolei - %s - %s - %d] - catch the hook of 'path_unlink'!!!", __FILE__, __func__,__LINE__);
	//printk("[+xiaolei - %s - %s - %d] - \n", __FILE__, __func__,__LINE__);
	printk("[+xiaolei - %s - %s - %d] - the value of 'dir->dentry->d_name.name' is : %s", __FILE__, __func__,__LINE__, dir->dentry->d_name.name);
	printk("[+xiaolei - %s - %s - %d] - the value of 'dentry->d_name.name' is :%s", __FILE__, __func__,__LINE__, dentry->d_name.name);
	printk("[+xiaolei - %s - %s - %d] - the value of 'current->pid' is :%ld", __FILE__, __func__,__LINE__, current->pid);
	return 0;
}

static int sec_file_inode_unlink(struct inode *dir, struct dentry *dentry)
{
	printk("[+xiaolei - %s - %s - %d] - catch the hook of 'inode_unlink'!!!\n", __FILE__, __func__,__LINE__);
	//printk("[+xiaolei - %s - %s - %d] - File name is : %s, function name is : %s, line is %d\n", __FILE__, __func__,__LINE__);
	printk("[+xiaolei - %s - %s - %d] - the value of 'dir->i_ino' is : %d\n", __FILE__, __func__,__LINE__, dir->i_ino);
	printk("[+xiaolei - %s - %s - %d] - the value of 'dentry->d_name.name' is :%s\n", __FILE__, __func__,__LINE__, dentry->d_name.name);
	printk("[+xiaolei - %s - %s - %d] - the value of 'current->pid' is :%ld\n", __FILE__, __func__,__LINE__, current->pid);
	printk("[+xiaolei - %s - %s - %d] - the value of 'dentry->d_inode->i_ino' is :%d\n", __FILE__, __func__,__LINE__, dentry->d_inode->i_ino);
	return 0;
}

static struct security_hook_list sec_file_hooks[] __lsm_ro_after_init = {
		LSM_HOOK_INIT(file_permission,sec_file_file_permission),
		LSM_HOOK_INIT(path_unlink, sec_file_path_unlink),
		LSM_HOOK_INIT(inode_unlink, sec_file_inode_unlink),
};



static __init int sec_file_init(void)
{
	printk(KERN_ALERT "[+ xiaolei] sec_file: Initializing .!!!!!!]n");
	security_add_hooks(sec_file_hooks,ARRAY_SIZE(sec_file_hooks), "sec_file");
    return 0;
}


DEFINE_LSM(sec_file) = {
		.name = "sec_file",
		.init = sec_file_init,
};

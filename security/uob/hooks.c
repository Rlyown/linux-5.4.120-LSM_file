#include <linux/lsm_hooks.h>
#include <linux/sysctl.h>

static int uob_socket_create(int family, int type, int protocol, int kern)
{
    return 0;
}

static struct security_hook_list uob_hooks[] __lsm_ro_after_init = {
    LSM_HOOK_INIT(socket_create, uob_socket_create),
};

static int __init init_uob(void)
{
    printk("UoB hooks: Initializing.\n");
    security_add_hooks(uob_hooks, ARRAY_SIZE(uob_hooks), "uob");
    return 0;
}

DEFINE_LSM(uob) = {
    .name = "uob",
    .init = init_uob,
};



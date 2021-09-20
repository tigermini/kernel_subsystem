#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/jiffies.h>
#include <linux/version.h>

static struct timer_list ttimer;

/* 给timer的回调函数使用，索引计数 */
#define MAX_TINDEX 10
static int tindex;

void tfunc(struct timer_list *data)
{
    if (tindex < MAX_TINDEX) {
        printk("now index is %d\n", tindex);
    }

    tindex++;

    mod_timer(&ttimer, jiffies + tindex * HZ);
}

static int __init ttimer_init(void)
{
    printk("ttimer init\n");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,15,0)
    timer_setup(&ttimer, tfunc, 0);
#else
    init_timer(&ttimer);
    ttimer.data = 0;
    ttimer.function = tfunc;
#endif
    ttimer.expires = jiffies + HZ;

    add_timer(&ttimer);

    return 0;
}

static void __exit ttimer_exit(void)
{
    printk("ttimer exit\n");

    del_timer_sync(&ttimer);
}

module_init(ttimer_init);
module_exit(ttimer_exit);
MODULE_AUTHOR("tigermini@126.com");
MODULE_LICENSE("GPL");


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/current.h>
#include <asm/page.h>
#include <linux/sched.h>
#include <linux/mm_types.h>
#include <asm/types.h>
#include <asm/processor.h>
// #include <unistd.h>

MODULE_LICENSE ("GPL");

int init (void)
{
    printk ("hello\n");
    struct task_struct* task;
    struct mm_struct* mm;
    void* cr3_virt;
    unsigned long cr3_phys;
    int pid;
    pid = 2911;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL){
	printk("mark2\n");
        return 0;
}
    mm = task->mm;
    if (mm == NULL){
	printk("mark1\n");	
        return 0;
}
    cr3_virt = (void*) mm->pgd;
    cr3_phys = virt_to_phys(cr3_virt);
    printk ("cr3_phys: %lx\n", cr3_phys);
    return 0;
}

void clean (void)
{
    printk (KERN_INFO "Goodbye\n");
}

module_init (init);
module_exit (clean);

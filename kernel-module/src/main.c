#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module to list processes in active Docker containers");

static struct proc_dir_entry *proc_entry;

static void list_docker_processes(void) {
    struct task_struct *task;
    struct list_head *list;

    printk(KERN_INFO "Listing processes in active Docker containers:\n");

    for_each_process(task) {
        if (strstr(task->comm, "docker")) {
            printk(KERN_INFO "Docker Process: PID = %d, Name = %s\n", task->pid, task->comm);
            // You can add additional logic here to filter and list processes within specific containers
        }
    }
}

static int __init docker_process_list_init(void) {
    printk(KERN_INFO "Docker Process List Module Loaded\n");
    list_docker_processes();
    return 0;
}

static void __exit docker_process_list_exit(void) {
    printk(KERN_INFO "Docker Process List Module Unloaded\n");
}

module_init(docker_process_list_init);
module_exit(docker_process_list_exit);
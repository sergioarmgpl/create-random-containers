#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/cgroup.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module to list the full command line of running processes using cgroups");

#define PROC_FILENAME "process_cmdline"

static struct proc_dir_entry *proc_entry;

static int proc_show(struct seq_file *m, void *v) {
    struct task_struct *task;
    struct mm_struct *mm;
    char *buffer;
    char *cmdline;
    int res;

    for_each_process(task) {
        struct cgroup_subsys_state *css = task_css(task, cpu_cgrp_id);
        if (css) {
            struct cgroup *cgrp = css->cgroup;
            if (cgrp && strstr(cgrp->kn->name, "docker")) {
                mm = get_task_mm(task);
                if (!mm)
                    continue;

                buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
                if (!buffer) {
                    mmput(mm);
                    continue;
                }

                res = access_process_vm(task, mm->arg_start, buffer, PAGE_SIZE, 0);
                if (res > 0) {
                    buffer[res] = '\0';
                    cmdline = strnchr(buffer, res, '\0');
                    if (cmdline) {
                        seq_printf(m, "PID: %d, Command Line: %s\n", task->pid, buffer);
                    }
                }

                kfree(buffer);
                mmput(mm);
            }
        }
    }

    return 0;
}

static int proc_open(struct inode *inode, struct file *file) {
    return single_open(file, proc_show, NULL);
}

static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .open = proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init proc_init(void) {
    proc_entry = proc_create(PROC_FILENAME, 0, NULL, &proc_fops);
    if (!proc_entry) {
        return -ENOMEM;
    }
    printk(KERN_INFO "/proc/%s created\n", PROC_FILENAME);
    return 0;
}

static void __exit proc_exit(void) {
    proc_remove(proc_entry);
    printk(KERN_INFO "/proc/%s removed\n", PROC_FILENAME);
}

module_init(proc_init);
module_exit(proc_exit);

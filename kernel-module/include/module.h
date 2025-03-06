#ifndef MODULE_H
#define MODULE_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/uaccess.h>

struct docker_process {
    pid_t pid;
    char comm[TASK_COMM_LEN];
    struct list_head list;
};

void list_docker_processes(void);
void cleanup_docker_processes(void);

#endif // MODULE_H
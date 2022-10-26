#include <linux/kernel.h>
#include <asm/unistd.h>
#include <linux/linkage.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <asm/current.h>
#include <asm/errno.h>
#include <linux/syscalls.h>
#include <linux/string.h>

struct proc_info {
	pid_t pid;
	char name[16];
};

struct procinfos {
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

SYSCALL_DEFINE2 (get_proc_info, pid_t, pid, struct procinfos *,info) {
	struct task_struct *process;
    if (pid == -1) {
        process = current;
    } 
    else if (pid >= 0) {
        process = find_task_by_vpid(pid);
        if (process == NULL) 
            return EINVAL;
    }
    else return EINVAL;
    struct task_struct *parent_process;
    struct task_struct *oldest_child_process;
    struct list_head *children_list;
    struct procinfos fieldproc;
    memset(&fieldproc, 0, sizeof(struct procinfos));
    fieldproc.studentID = 2013375;
    (fieldproc.proc).pid = process->pid;
    get_task_comm((fieldproc.proc).name, process);
    parent_process = process->parent;
    if (parent_process) {
        (fieldproc.parent_proc).pid = parent_process->pid;
        get_task_comm((fieldproc.parent_proc).name, parent_process);
    }
    children_list = &process->children;
    if (list_empty(children_list)) {
        oldest_child_process = NULL;
    }
    else {
        oldest_child_process = list_first_entry(children_list, struct task_struct, sibling);
    }
    if (oldest_child_process) {
        (fieldproc.oldest_child_proc).pid = oldest_child_process->pid;
        get_task_comm((fieldproc.oldest_child_proc).name, oldest_child_process);
    }
    else (fieldproc.oldest_child_proc).pid = 0;
    copy_to_user(info, &fieldproc, sizeof(struct procinfos));
    return 0;
}

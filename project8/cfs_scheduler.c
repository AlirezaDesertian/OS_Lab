#include <stdio.h>
#include <stdlib.h>
#include "red_black_tree/rb.h"
#include "red_black_tree/rb_data.h"
#include "proc.h"

#define PROCESS_COUNT 3

void fill_process_array(process *process_array[PROCESS_COUNT]) {
    for (int i = 0; i < PROCESS_COUNT; i++) {
        process_array[i] = create_process(2000 + i, 100 + i, 3);
    }
}

void insert_one_process_to_rbtree(rbtree *rbt, process *proc) {
    mydata *data = makedata_with_object(proc->vruntime, proc);
    if (rb_insert(rbt, data) == NULL)
        fprintf(stderr, "insert %d: out of memory\n", proc->id);
}

void insert_processes_to_rbtree(rbtree *rbt, process *process_array[PROCESS_COUNT]) {
    for (int i = 0; i < PROCESS_COUNT; i++) {
        insert_one_process_to_rbtree(rbt, process_array[i]);
    }
}

process* process_of_node(rbnode *node) {
    process *proc = (process *)((mydata *)(node->data))->object;
    return proc;
}

int main() {
    process *processes[PROCESS_COUNT];
    fill_process_array(processes);
    printf("process array filled\n");

    rbtree *rbt;
    if ((rbt = rb_create(compare_func, destroy_func)) == NULL) {
        fprintf(stderr, "create red-black tree failed\n");
        return 1;
    }

    printf("tree created\n");
    insert_processes_to_rbtree(rbt, processes);
    printf("inserted processes to rbtree\n");

    rbnode *node;
    process *current_proc;
    int current_tick = 0;

    while ((node = RB_MINIMAL(rbt))) {
        printf("current_tick: %d\n", current_tick);
        current_tick++;
        current_proc = process_of_node(node);
        run_process_for_one_tick(current_proc);
        rb_delete(rbt, node, 0);

        if (!is_terminated(current_proc)) {
            insert_one_process_to_rbtree(rbt, current_proc);
        }
    }

    printf("All processes finished.\n");
    return 0;
}

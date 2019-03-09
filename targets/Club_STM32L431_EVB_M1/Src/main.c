/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>
#include "soc_init.h"

#define TASK1_STACKSIZE    256 //512*cpu_stack_t = 2048byte
#define TASK1_PRIORITY     20
static ktask_t task1_obj;
cpu_stack_t task1_buf[TASK1_STACKSIZE];

void task1(void *arg)
{
    int count = 0;
    char *data ="abcd";
    rhf76_init();
    printf("welcome to alios things!\r\n");  
    while (1)
    {
        rhf76_send(0,(const uint8_t *)data,strlen(data));
        printf("task 1  count %d\n", count++);
        //sleep 1 second
        krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND);
    };
}

int main(void)
{
    krhino_init();
    krhino_task_create(&task1_obj, "task1", 0,TASK1_PRIORITY, 
        50, task1_buf, TASK1_STACKSIZE, task1, 1);
    //uart init 

    stm32_soc_init(); 
    krhino_start();
    
    return 0;
}


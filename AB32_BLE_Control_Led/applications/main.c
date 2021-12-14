///*
// * Copyright (c) 2020-2021, Bluetrum Development Team
// *
// * SPDX-License-Identifier: Apache-2.0
// *
// * Change Logs:
// * Date           Author       Notes
// * 2020/12/14     greedyhao    The first version
// */
//
///**
// * Notice!
// * All functions or data that are called during an interrupt need to be in RAM.
// * You can do it the way exception_isr() does.
// */
//
#include <rtthread.h>
#include "board.h"
#include<string.h>
#include<stdlib.h>

#define uart_device_name2 "uart2"
#define uart_device_name1 "uart1"
static struct rt_semaphore rx_sem;
static rt_device_t serial;

static void serial_thread_entry(void *p);
static rt_err_t uart_input(rt_device_t dev, rt_size_t size);

static int uart(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char str[] = "led!\r\n";
    char receive_msg [8]; //receive 255 words
//    char uart_name[RT_NAME_MAX];
            // uart1 and uart2
    serial = rt_device_find(uart_device_name1);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_device_name1);
        return RT_ERROR;
    }
    else
    {
        rt_kprintf("success to find %s!\n", uart_device_name1);
    }
//    rt_kprintf("%s %s\n",argv[0],argv[1]);

    // get param
    if (argc == 2)
    {
        rt_strncpy(receive_msg, argv[1], RT_NAME_MAX);

    }
    else
    {
        rt_strncpy(receive_msg, str, RT_NAME_MAX);
    }
    rt_kprintf("message:%s\n", receive_msg);

    //init
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);    //先进先出模式
    // open device
    rt_device_open(serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);    //  读写模式  中断接收
    // callback function
    rt_device_set_rx_indicate(serial, uart_input);
    //send data
    rt_device_write(serial, 0, receive_msg, sizeof(receive_msg) - 1);

//    free(receive_msg); //清空
//    rt_free(receive_msg);
    //create thread
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread); //start up
    }
    else
    {
        ret = RT_EOK;
    }

    return ret;
}

/**
 * callback function
 * @param dev
 * @param size
 * @return
 */
static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);
    return RT_EOK;
}
/**
 * serial thread
 * @param p
 */
static void serial_thread_entry(void *p)
{
    char ch;
    while (1)
    {
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER); //获取信号量 阻塞数据
        }
        ch = ch + 1;
        rt_device_write(serial, 0, &ch, 1);
    }
}

MSH_CMD_EXPORT(uart, uart);

int main(void)
{
    uint8_t pin = rt_pin_get("PE.1");

    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_kprintf("Hello, world\n");

    while (1)
    {
        rt_pin_write(pin, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(pin, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}



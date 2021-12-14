# AB32_BLE_CONTROL_LED

#### 介绍
基于AB32开发板开发一个控制灯光的设备，即蓝牙控制灯光。然而实际上，AB32上面蓝牙模块，很难实现，目前还没有成熟，只能退而其次，串口通信，既是UART串口。我制作两个设备，一个是主设备，另一个从设备。主设备（AB32开发板）上开启uart串口，PA3和PA4引脚，连接到从设备。从设备可以是arduino开发板，也可以是STM32开发板，也可以是esp8266，等等，其中只要有uart串口功能。从主设备发送"uart 1"到从设备，当从设备检测到“uart 1”，则打开LED；发送“uart 0”,则关灯。
代码:https://gitee.com/rx-ted/ab32_ble_control_led/ 

设计作品思路如下图：
![输入图片说明](img%E4%BD%9C%E5%93%81.png)

#### 软件架构

软件中间使用了部分信号量和互斥量保证线程同步。跟uart_sample这个例子原理差不多。
![输入图片说明](img%E8%BD%AF%E4%BB%B6.png)

整体架构：

内核部分：使用了线程、信号量、互斥量、定时器 

硬件部分：AB32开发板、arduino wemos R1开发板、若干LED和电线 

软件包：

blueturm(蓝牙模块)等 

设备驱动：
GPIO/BLE/UART/I2C 等
![输入图片说明](img%E7%A1%AC%E4%BB%B6.png)



#### 安装教程

1.  RT-Thread
2.  download.exe
3.  vscode

#### 使用说明

开灯：uart 1 
关灯：uart 0


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)

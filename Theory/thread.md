# 线程

> 了解进程与线程的区别 <br>
> 描述线程的基本设计问题 <br>
> 掌握用户级线程和内核级线程的差异 <br>
> 掌握Linux中的线程管理功能

## 1. 进程和线程

之前的进程具有一下两个特点：

- **资源所有权**：包括存放进程映像的虚拟地址空间，对内存、I/O通道、I/O设备和文件等资源的控制权和所有权，以及提供预防进程间不发生不必要资源冲突的保护功能。
- **调度/执行**：进程执行时采用一个或多个程序的执行路径（轨迹），不同进程的执行过程会交替执行，是可以被OS调度和分派的实体。

现在把能分派的单位称为线程或轻量级进程（LWP），掌握资源所有权的单位称为进程或任务。

### 1.1 多线程

![multithread](images/multithread.png)

多线程是指OS在单个进程内支持多个并发执行路径的能力。在多进程环境中，与进程相关联的有：

- 容纳进程映像的虚拟地址空间。
- 对处理器、其他进程、文件和I/O资源的受保护访问。

与线程相关的有：

- 一个线程的执行状态。
- 未运行时保存的线程上下文。线程可视为在线程内运行的一个独立程序计数器。
- 一个执行栈。
- 每个线程用于局部变量的一些静态存储空间。
- 在线程内其他线程共享的内存和资源的访问。

单线程和多线程模型如下：

![threading](images/threading.png)

线程具有以下优点：

1. 创建线程的时间远小于创建一个进程的时间。
2. 终止线程要比终止进程所花的时间少。
3. 同一进程内线程间切换的时间小于进程间切换的时间。
4. 线程提高了不同执行程序间的通信效率。独立进程间的通信需要内核介入，以提供保护和通信机制，但同进程间的多线程共享内存和文件，因此无需调用内核就可互相通信。
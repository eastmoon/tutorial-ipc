# IPC ( Inter-Process Communication )

執行程序間通訊（IPC，Inter-Process Communication），指作業系統提供給至少兩個執行程序 ( Porcess ) 間傳送資料或訊號技術方式；在微服務與分散式系統內啟動的複數執行程序，便需要以此通訊方式來協調服務間的運作；倘若產品、專案橫向擴展服務時，亦可利用執行程序間通序來串聯運作，以此方式逐步增加服務的運用。

在單核 ( Monolithic kernel ) 與微核 ( Microkernel ) 的架構中，將單核的垂直結構改為橫向結構，其主要方式便是將驅動、服務轉為執行程序，透過執行程序間通訊來擴展，讓必要的服務互相運作，避免冗餘的服務占用系統資源。

![ipc-monolithic-kernel-and-Microkernel 圖示](./docs/img/ipc-monolithic-kernel-and-Microkernel.png)
> Reference : [Inter-Process Communication Mechanism in Monolithic Kernel and Microkernel]http://cdworkshop.eit.lth.se/fileadmin/eit/project/142/IPC_Report.pdf

依據文獻，目前執行程序間通訊（IPC，Inter-Process Communication）常見方式如下：

+ Shared files
+ Shared memory (with semaphores)
+ Pipes (named and unnamed)
+ Message queues
+ Sockets
+ Signals

## 文獻

+ [Inter-Process Communication - wiki](https://en.wikipedia.org/wiki/Inter-process_communication)
    - [Interprocess Communications - Microsoft](https://docs.microsoft.com/en-us/windows/win32/ipc/interprocess-communications)
    - [Inter-Process Communication - mtholyoke EDU](https://www.mtholyoke.edu/courses/dstrahma/cs322/ipc.htm)
    - [Inter Process Communication (IPC) - GeeksForgeeks](https://www.geeksforgeeks.org/inter-process-communication-ipc/)
    - [Inter-process communication in Linux: Shared storage](https://opensource.com/article/19/4/interprocess-communication-linux-storage)
    - [Inter-Process Communication (IPC) Introduction and Sample Code](https://www.codeproject.com/Articles/34073/Inter-Process-Communication-IPC-Introduction-and-S)
    - [Linux 下 IPC 的運作方式](https://jasonblog.github.io/note/linux_system/linux_xia_ipc_de_yun_zuo_fang_shi.html)
        + Socket 程序間通信 [（上）](https://jasonblog.github.io/note/linux_system/ji_yu_socket_de_jin_cheng_jian_tong_xin_ff08_shang.html)、 [（下）](https://jasonblog.github.io/note/linux_system/ji_yu_socket_de_jin_cheng_jian_tong_xin_ff08_xia_f.html)
        + 信號 [（上）](https://jasonblog.github.io/note/linux_system/xin_hao_ff08_shang_ff09.html)、[（下）](https://jasonblog.github.io/note/linux_system/xin_hao_ff08_xia_ff09.html)
        + [POSIX 共享內存](https://jasonblog.github.io/note/linux_system/posix_gong_xiang_nei_cun.html)
        + [POSIX 訊息柱列](https://jasonblog.github.io/note/linux_system/posixxiao_xi_dui_lie.html)
    - [IPC Examples](https://condor.depaul.edu/dmumaugh/readings/handouts/CSC343/examples/ipc.example.html)
+ [Unix Socket - Linux manual page](https://man7.org/linux/man-pages/man7/unix.7.html)
    - [Unix domain socket](https://en.wikipedia.org/wiki/Unix_domain_socket)
    - [Work Note-Unix domain socket](https://medium.com/@chinhung_liu/62b42f25ffc2)
    - [Unix Socket Tutorial](https://www.tutorialspoint.com/unix_sockets/index.htm)

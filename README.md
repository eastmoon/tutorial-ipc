# IPC ( Inter-Process Communication )

執行程序間通訊（ IPC，Inter-Process Communication ），指作業系統提供給至少兩個執行程序 ( Porcess ) 間傳送資料或訊號技術方式；在微服務與分散式系統內啟動的複數執行程序，便需要以此通訊方式來協調服務間的運作；倘若產品、專案橫向擴展服務時，亦可利用執行程序間通序來串聯運作，以此方式逐步增加服務的運用。

在單核 ( Monolithic kernel ) 與微核 ( Microkernel ) 的架構中，將單核的垂直結構改為橫向結構，其主要方式便是將驅動、服務轉為執行程序，透過執行程序間通訊來擴展，讓必要的服務互相運作，避免冗餘的服務占用系統資源。

![ipc-monolithic-kernel-and-Microkernel 圖示](./doc/img/ipc-monolithic-kernel-and-Microkernel.png)
> Reference : [Inter-Process Communication Mechanism in Monolithic Kernel and Microkernel](http://cdworkshop.eit.lth.se/fileadmin/eit/project/142/IPC_Report.pdf)

專案範例環境如下：

+ Operating System : Debian ( Docker Container )
+ Language : C++ / C#

## 通訊方式

依據作業系統的規範，每個軟體 ( Software ) 被執行後，會在作業系統視為一個執行程序 ( Process )，而每個執行程序擁有至少一個執行序 ( Thread )，以及屬於執行程序可管理的記憶體區塊 ( Memory )；因此，在執行程序中的執行序，可以透過記憶體區塊來共享資訊，甚至用於執行緒間通訊，然而這樣的通訊會因為執行緒的處理速度不同步，導致[併發衝突 ( Concurrency )](https://medium.com/mr-efacani-teatime/1b212a020e30)，對此，在執行緒共享記憶體時會要求遵循[執行緒安全 ( Thread Safe )](https://zh.wikipedia.org/zh-tw/%E7%BA%BF%E7%A8%8B%E5%AE%89%E5%85%A8) 法則，進而避免併發導致的[飢餓 ( Starvation )](https://en.wikipedia.org/wiki/Starvation_(computer_science)) 與[死結 ( Dadlock )](https://en.wikipedia.org/wiki/Deadlock) 狀態。

然而，在執行緒間存在的資源共享，在執行程序間並不被允許，考量各執行程序本是不同方式與來源的開發團隊，在安全性考量下，避免直接的記憶體共享亦是避免來源不明的資訊會入導致異常；但若執行程序屬於同個開發團隊設計，且基於服務性質而存在資訊共享的必要，則會使用執行程序間通訊（ Inter-Process Communication ) 並依循其通訊格式來傳遞資訊。

依據參考文獻，目前執行程序間通訊（IPC，Inter-Process Communication）常見方式如下：

+ [Shared files](#shared-files)
+ [Shared memory](#shared-memory)
+ [Pipes (named and anonymous)](#pipes)
+ [Message queue](#message-queue)
+ Sockets
+ Signals

並有兩個常見的執行程序啟動，方式如下：

+ 至少兩個執行於不同終端機 ( Terminal ) 下的執行程序
+ 由一個執行程序 ( Parent ) 通過系統函數 [fork](https://man7.org/linux/man-pages/man2/fork.2.html) 生成另一個執行程 ( Child )

其共通的通訊程序如下：

+ 執行程序中存在一個執行緒負責執行通訊函式
+ 通訊函式依據通訊格式存取內容
+ 若格式的內容未變更，無需觸發後續處理函數

### [Shared files](./src/shared-files)

共享檔案 ( Shared files ) 是個可運用於任何作業系統的簡易方式，其概念是透過檔案來傳遞資訊；然而這樣的方式很容易受到 I/O 影響執行效率且對檔案的快速寫入、讀取，會讓權管理異常使得資源無法獲得而進入飢餓 ( Starvation );
但若運用於低傳訊頻率的執行程序間，是個簡易且技術相依低的運用方案。

### [Shared memory](./src/shared-memory)

共享記憶體 ( Shared memory ) 可視為共享檔案的進階方式，為解決前面提到對檔案存取產生的問題，則是將資料讀寫進記憶體，並令執行程序共享一個用於通訊的記憶體區域；雖然記憶體存取改善了效率與權限異常的風險，但共享記憶體並非無限的空間，因此在設計上僅限用於訊息的傳遞，倘若有大量的資料共享，則需回歸到共享檔案的方式來解決。

### Pipes

詳閱文獻後，一般在執行程序間通訊的文獻中提到管線，就是指匿名管線，命名管線則是指使用先入先處 ( FIFO ) 方式的管線。

#### [Anonymous pipes](./src/pipes/anonymous)

匿名管線 ( Anonymous pipes ) 或稱為管線 ( Pipes )，是基於 Unix 系統指令 [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html) 的執行程序間通訊，這方式是透過管線在記憶體建立一個 "Virtual File"，並提供一個讀取 ( 0 )、寫入 ( 1 ) 的串流編號陣列，由於為串流資訊，因此可以透過 write、read 指令對其寫入內容。

就其運作原理，管線與共享記憶體的運作方式相似，差別是對於記憶體宣告與讀寫管理是由管線系統管理，並提供指定串流讓訊息進出，程式上對內容相對容易管理；其缺點是管線僅適用於前述第二種執行程序啟動方式，亦即執行程序透過 fork 產生的自身的多執行程序運作方式。

#### [Named pipes](./src/pipes/named)

命名管線  ( Named pipes ) 或稱為先入先出 ( FIFO、First-In-First-Out )，是基於 Unix 系統指令 [mknod](https://man7.org/linux/man-pages/man2/mknod.2.html) 的執行程序間通訊，這方式是透過 mknod 的 ```S_IFIFO``` 參數建立 FIFO 特殊檔案，在透過檔案讀寫機制來存取檔案內容。

就其運作原理，命名管線與共享檔案的運作方式相似，差別是 FIFO 檔案具有柱列效果，而若共享檔案則需自行設計讀寫機制來自行設計管線的效果；其缺點是 FIFO 是讀取後內容會清除，並不適合雙向溝通或對多執行程序的廣播，倘若要雙向則需建立各自的檔案或設計延遲機制等待回應，而若廣播則需改用共享檔案的原理來設計。

### [Message Queue](./src/message-queue)

訊息柱列 ( Message queue ) 可視為共享記憶體的進階方式，藉由柱列管理的方案，提取記憶體中的格式化內容；相比共享記憶體的，訊息柱列有以下特點：

+ 訊息僅能自柱列的單一頻道提取一次
+ 訊息可寫入柱列中的不同頻道
+ 柱列訊息為先進先出 ( FIFO )

由於訊息柱列的特性，使得共享記憶體適用於廣播的設計，而訊息柱列適用於單一服務的主動分頻道通訊。

### Sockets

## 通訊格式

## 文獻

+ [Inter-Process Communication - wiki](https://en.wikipedia.org/wiki/Inter-process_communication)
    - [Interprocess - Boost](https://www.boost.org/doc/libs/1_61_0/doc/html/interprocess/)
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
+ [fock - Linux manual page](https://man7.org/linux/man-pages/man2/fork.2.html)
    - [fork 觀念由淺入深](https://wenyuangg.github.io/posts/linux/fork-use.html)
    - [UNIX 作業系統 fork/exec 系統呼叫的前世今生](https://hackmd.io/@sysprog/unix-fork-exec)
    - [在 C++ 中用 Fork 建立程序](https://www.delftstack.com/zh-tw/howto/cpp/cpp-fork/)

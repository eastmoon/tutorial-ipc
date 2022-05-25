# Shared memory

本範例參考文獻內容如下：

+ [IPC using Message Queues - GeeksForGeeks](https://www.geeksforgeeks.org/ipc-using-message-queues/)
+ [IPC using Message Queues - TutorialSpoint](https://www.tutorialspoint.com/ipc-using-message-queues)
+ [Message queue example code](https://condor.depaul.edu/dmumaugh/readings/handouts/CSC343/examples/msg.c)

Message Queue 文獻：

+ [msgget](https://man7.org/linux/man-pages/man2/msgget.2.html)
+ [msgsnd](https://man7.org/linux/man-pages/man2/msgsnd.2.html)
+ [msgrcv](https://man7.org/linux/man-pages/man2/msgrcv.2.html)
+ [msgctl](https://man7.org/linux/man-pages/man2/msgctl.2.html)

## 執行方式

+ 啟動容器

```
dockerw start
```
> 本專案範設計執行於 Winodws 環境下的 Docker 服務中

+ 執行編譯腳本

```
bash run.sh message-queue
```

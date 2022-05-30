# Signals

本範例參考文獻內容如下：

+ [Inter Process Communication - Signals](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_signals.htm)
+ [IPC examples – signals and shared memory](https://blacksheephacks.pl/ipc-examples-signals-and-shared-memory/)
+ [Unix訊號](https://zh.wikipedia.org/zh-tw/Unix%E4%BF%A1%E5%8F%B7)
+ 自訂訊號結構
    - [Linux C/C++程式設計：sigaction](https://www.796t.com/article.php?id=225163)
    - [linux系統編程之信號（四）：信號的捕捉與sigaction函數](https://b8807053.pixnet.net/blog/post/120862346)
    - [信號處理和sigemptyset](https://tw.pays-tarusate.org/549525-signal-handling-and-sigemptyset-GWCOBG)

Signal 指令文獻：

+ [signal](https://man7.org/linux/man-pages/man7/signal.7.html)
+ [kill](https://man7.org/linux/man-pages/man2/kill.2.html)

## 執行方式

+ 啟動容器

```
dockerw start
```
> 本專案範設計執行於 Winodws 環境下的 Docker 服務中

+ 執行編譯腳本

```
bash run.sh signals
```

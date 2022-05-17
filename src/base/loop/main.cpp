/*
atomic：原子操作是『原子是最小的、不可分割的最小個體』的意義，它表示在多個執行緒訪問同一個全域資源的時候，能夠確保所有其他的執行緒都不在同一時間內訪問相同的資源。

Atomic 類別在建構時的初值方式依據使用的版本會有不同，在 C++ 11 不可使用建構值付值的方式。
Ref : https://en.cppreference.com/w/cpp/atomic/atomic/atomic

*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

// Base thread worker
template <typename C>
class Worker {
public:
    Worker(int _id, C* _count) : m_id(_id), m_count(_count) {};
    virtual void operator() () {
        std::cout << "ID : " << this->m_id << std::endl;
    }
protected:
    int m_id;
    C* m_count;
};

// Non lock thread counter.
template <typename C>
class NonLockWorker: public Worker<C> {
public:
    NonLockWorker(int _id, C* _count) : Worker<C>(_id, _count) {};
    void operator() () {
        for (int i = 0; i < 100000; i++) {
            *this->m_count += 1;
        }
    }
};

// Declare thread execute template function
template <typename T, typename C>
void run(C* _count) {
    // Record start time
    auto t1 = std::chrono::high_resolution_clock::now();
    // Create thread with worker
    int threadsSize = 100;
    std::thread threads[threadsSize];
    for (int i = 0; i != threadsSize; i++)
    {
        threads[i] = std::thread(T(i, _count));
    }
    // Ensure worker finish job
    for (auto &th : threads)
        th.join();
    // Record end time
    auto t2 = std::chrono::high_resolution_clock::now();
    // Show result and duration time
    std::chrono::duration<double, std::milli> elapsed = t2 - t1;
    std::cout << "result: " << *_count << std::endl;
    std::cout << "duration: " << elapsed.count() << " ms" << std::endl;
}

int main()
{
    std::cout << "Atomic thread :" << std::endl;
    std::atomic<long> acount(0);
    run<NonLockWorker<std::atomic<long>>, std::atomic<long>>(&acount);
    std::cout << std::endl;

    return 0;
}

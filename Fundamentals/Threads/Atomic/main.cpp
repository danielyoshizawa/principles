#include <iostream>
#include <atomic>

// Atomic
// Objects of atomic types contain a value of a particular type (T).

// The main characteristic of atomic objects is that access to this contained value from
// different threads cannot cause data races (i.e., doing that is well-defined behavior,
// with accesses properly sequenced). Generally, for all other objects, the possibility of
// causing a data race for accessing the same object concurrently qualifies the operation as
// undefined behavior.

// Additionally, atomic objects have the ability to synchronize access to other non-atomic
// objects in their threads by specifying different memory orders.

// Example from
// https://cplusplus.com/reference/atomic/atomic/atomic/
// constructing atomics
#include <iostream> // std::cout
#include <atomic>   // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>   // std::thread, std::this_thread::yield
#include <vector>   // std::vector

std::atomic<bool> ready(false);
std::atomic<bool> winnerExchange(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id)
{
    while (!ready)
    {
        std::this_thread::yield();
    } // wait for the ready signal
    for (int i = 0; i < 1000000; ++i)
    {
    } // go!, count to 1 million
    if (!winner.test_and_set())
    {
        std::cout << "thread #" << id << " won!\n";
    }
};

void count1mExchange(int id)
{
    while (!ready)
    {
        std::this_thread::yield();
    } // wait for the ready signal
    for (int i = 0; i < 1000000; ++i)
    {
    } // go!, count to 1 million
    if (!winnerExchange.exchange(true)) // Returns the previous value before setting the new one
    {
        std::cout << "thread #" << id << " won!\n";
    }
};

int main()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i)
    {
        threads.push_back(std::thread(count1m, i));
    }
    ready = true;
    for (auto &th : threads)
    {
        th.join();
    }

    // Reset Scenario
    threads.clear();
    ready = false;

    std::cout << "spawning 10 threads that count to 1 million using Exchange...\n";
    for (int i = 1; i <= 10; ++i)
    {
        threads.push_back(std::thread(count1mExchange, i));
    }
    ready = true;
    for (auto &th : threads)
    {
        th.join();
    }

    return 0;
}
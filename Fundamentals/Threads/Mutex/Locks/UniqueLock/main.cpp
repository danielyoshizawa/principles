// Unique Lock
// A unique lock is an object that manages a mutex object with unique ownership in both states:
// locked and unlocked.

// On construction (or by move-assigning to it), the object acquires a mutex object,
// for whose locking and unlocking operations becomes responsible.

// The object supports both states: locked and unlocked.

// This class guarantees an unlocked status on destruction (even if not called explicitly).
// Therefore it is especially useful as an object with automatic duration, as it guarantees
// the mutex object is properly unlocked in case an exception is thrown.

// Note though, that the unique_lock object does not manage the lifetime of the mutex object
// in any way: the duration of the mutex object shall extend at least until the destruction of
// the unique_lock that manages it.

// Example from
// https://cplusplus.com/reference/mutex/unique_lock/try_lock/

#include <iostream> // std::cout
#include <vector>   // std::vector
#include <thread>   // std::thread
#include <mutex>    // std::mutex, std::unique_lock, std::defer_lock

std::mutex mtx; // mutex for critical section

void print_star()
{
    std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
    // print '*' if successfully locked, 'x' otherwise:
    if (lck.try_lock())
        std::cout << '*';
    else
        std::cout << 'x';
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 500; ++i)
        threads.emplace_back(print_star);

    for (auto &x : threads)
        x.join();

    return 0;
}
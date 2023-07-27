// A timed mutex is a time lockable object that is designed to signal when critical sections
// of code need exclusive access, just like a regular mutex, but additionally supporting timed
// try-lock requests.

// As such, a timed_mutex has two additional members: try_lock_for and try_lock_until.

// It is guaranteed to be a standard-layout class.

// The calling thread locks the timed_mutex, blocking if necessary (it behaves exactly as in mutex):

// - If the timed_mutex isn't currently locked by any thread, the calling thread locks it
//   (from this point, and until its member unlock is called, the thread owns the timed_mutex).
// - If the timed_mutex is currently locked by another thread, execution of the calling thread
//   is blocked until unlocked by the other thread (other non-locked threads continue their execution).
// - If the timed_mutex is currently locked by the same thread calling this function, it produces
//   a deadlock (with undefined behavior). See recursive_timed_mutex for a timed mutex type that allows multiple locks from the same thread.

// All lock and unlock operations on the timed_mutex follow a single total order, with all visible
// effects synchronized between the lock operations and previous unlock operations on the same object.

// Note that the order in which different concurrent locks are scheduled to return is unspecified,
// and not necessarily related to the order in which they are locked (depending on the system and
// library implementation).

// Example from
// https://cplusplus.com/reference/mutex/timed_mutex/try_lock_for/

// timed_mutex::try_lock_for example
#include <iostream> // std::cout
#include <chrono>   // std::chrono::milliseconds
#include <thread>   // std::thread
#include <mutex>    // std::timed_mutex

std::timed_mutex mtx;

void fireworks()
{
    // waiting to get a lock: each thread prints "-" every 200ms:
    while (!mtx.try_lock_for(std::chrono::milliseconds(200)))
    {
        std::cout << "-";
    }
    // got a lock! - wait for 1s, then this thread prints "*"
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "*\n";
    mtx.unlock();
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(fireworks);

    for (auto &th : threads)
        th.join();

    return 0;
}
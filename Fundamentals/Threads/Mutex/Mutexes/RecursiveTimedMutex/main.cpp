// Resursive timed mutex
// A recursive timed mutex combines both the features of recursive_mutex and the features of 
// timed_mutex into a single class: it supports both acquiring multiple lock levels by a single 
// thread and also timed try-lock requests.

// It is guaranteed to be a standard-layout class.

// Try to lock for time span
// Attempts to lock the recursive_timed_mutex, blocking for rel_time at most:

// - If the recursive_timed_mutex isn't currently locked by any thread, the calling thread locks it 
//   (from this point, and until its member unlock is called, the thread owns the 
//   recursive_timed_mutex).
// - If the recursive_timed_mutex is currently locked by another thread, execution of the calling 
//   thread is blocked until unlocked or once rel_time has elapsed, whichever happens first 
//   (meanwhile, other non-locked threads continue their execution).
// - If the recursive_timed_mutex is currently locked by the same thread calling this function,
//   the thread acquires a new level of ownership over the recursive_timed_mutex. 
//   Unlocking the recursive_timed_mutex completely will require an additional call to member unlock.

// All lock and unlock operations on the recursive_timed_mutex follow a single total order, 
// with all visible effects synchronized between the lock operations and previous unlock operations 
// on the same object.

// Again, not a goog example, same as TimedMutex

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::recursive_timed_mutex mtx; // Using std::mutex will result in deadlock
int resource {200};

void recursion() {
    std::cout << resource << " ";
    // Base case
    if (resource < 1) {
        return;
    }
    // Change the resource
    --resource;
    mtx.try_lock_for(std::chrono::milliseconds(20)); // Lock is reaquired in every recursive call
    recursion();
    mtx.unlock();
};

int main()
{
    std::thread t1{recursion};
    
    t1.join();
    
    std::cout << std::endl;
    return 0;
}
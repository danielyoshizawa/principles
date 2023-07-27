// Recursive Mutex
// A recursive mutex is a lockable object, just like mutex, but allows the same thread to acquire 
// multiple levels of ownership over the mutex object.

// This allows to lock (or try-lock) the mutex object from a thread that is already locking it, 
// acquiring a new level of ownership over the mutex object: the mutex object will actually remain 
// locked owning the thread until its member unlock is called as many times as this level of 
// ownership.

// It is guaranteed to be a standard-layout class.

// Used to lock recursion.

// this is not a good example but let's do it anyway.

#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex mtx; // Using std::mutex will result in deadlock
int resource {200};

void recursion() {
    std::cout << resource << " ";
    // Base case
    if (resource < 1) {
        return;
    }
    // Change the resource
    --resource;
    mtx.lock(); // Lock is reaquired in every recursive call
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
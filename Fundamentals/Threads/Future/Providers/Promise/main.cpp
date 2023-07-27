// Promise
// A promise is an object that can store a value of type T to be retrieved by a future object
// (possibly in another thread), offering a synchronization point.

// On construction, promise objects are associated to a new shared state on which they can store
// either a value of type T or an exception derived from std::exception.

// This shared state can be associated to a future object by calling member get_future.
// After the call, both objects share the same shared state:
// - The promise object is the asynchronous provider and is expected to set a value for the
//   shared state at some point.
// - The future object is an asynchronous return object that can retrieve the value of the
//   shared state, waiting for it to be ready, if necessary.

// The lifetime of the shared state lasts at least until the last object with which it is associated
// releases it or is destroyed. Therefore it can survive the promise object that obtained it in the
// first place if associated also to a future.

// Example from
// https://cplusplus.com/reference/future/promise/

// promise example
#include <iostream>   // std::cout
#include <functional> // std::ref
#include <thread>     // std::thread
#include <future>     // std::promise, std::future

void print_int(std::future<int> &fut)
{
    int x = fut.get();
    std::cout << "value: " << x << '\n';
}

int main()
{
    std::promise<int> prom; // create promise

    std::future<int> fut = prom.get_future(); // engagement with future

    std::thread th1(print_int, std::ref(fut)); // send future to new thread
    
    prom.set_value(10); // fulfill promise
                        // (synchronizes with getting the future)
    th1.join();
    
    return 0;
}
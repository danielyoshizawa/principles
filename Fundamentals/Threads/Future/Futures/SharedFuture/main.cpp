// Shared Future
// A shared_future object behaves like a future object, except that it can be copied,
// and that more than one shared_future can share ownership over their end of a shared state.
// They also allow the value in the shared state to be retrieved multiple times once ready.

// shared_future objects can be implicitly converted from future objects (see its constructor),
// or explicitly obtained by calling future::share. In both cases, the future object from which
// it is obtained transfers its association with the shared state to the shared_future and becomes
// itself non-valid.

// The lifetime of the shared state lasts at least until the last object with which it is
// associated is destroyed. Retrieving the value from a shared_future (with member get)
// does not release its ownership over the shared state (unlike with futures). Therefore,
// if associated to shared_future objects, the shared state can survive the object from which
// it was obtained in the first place (if any).

// 2 threads that receive a future and print when the future is fulfilled
// using future will create a problem when the first thread gets, destroying
// the shared state. Using shared_future, should work. lets test it
// Also future is non-copyable, so this example wouldn't be possible

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>

std::mutex mtx;

int boringComputation(int n)
{
    int result{0};
    for (int i{0}; i < n; ++i)
    {
        // Lets sleep to simulate a long computation;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        result += n + i;
    }

    return result;
}

void execute(std::shared_future<int> fut, std::string const & id) {
    fut.wait();
    int x = fut.get();

    std::unique_lock<std::mutex> lock (mtx);
    std::cout << id << " : " << x << std::endl;
}

int main()
{
    std::shared_future<int> fut = std::async(boringComputation, 30);
    std::thread t1 {execute, fut, "Thread 01"};
    std::thread t2 {execute, fut, "Thread 02"};

    t1.join();
    t2.join();

    return 0;
}
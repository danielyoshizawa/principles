// Package Task
// A packaged_task wraps a callable element and allows its result to be retrieved asynchronously.

// It is similar to std::function, but transferring its result automatically to a future object.

// The object contains internally two elements:

// - A stored task, which is some callable object (such as a function pointer, pointer to member
//   or function object) whose call signature shall take arguments of the types in Args... and return a value of type Ret.
// - A shared state, which is able to store the results of calling the stored task (of type Ret)
//   and be accessed asynchronously through a future.

// The shared state is associated to a future object by calling member get_future.
// After the call, both objects share the same shared state:
// - The packaged_task object is the asynchronous provider and is expected to set the shared state
//   as ready at some point by calling the stored task.
// - The future object is an asynchronous return object that can retrieve the value of the shared
// state, waiting for it to be ready, if necessary.

// The lifetime of the shared state lasts at least until the last object with which it is associated
//  releases it or is destroyed. Therefore it can survive the packaged_task object that obtained it
// in the first place if associated also to a future.

#include <iostream>
#include <future>
#include <chrono>
#include <thread>

class LongProcess
{
public:
    int operator()(int delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        return delay;
    }
};

int main()
{
    // Functor Task
    LongProcess lp;
    // Packs a task to be executed later
    std::packaged_task<int(int)> tsk(lp);
    std::packaged_task<int(int)> tsk2(lp);
    
    std::future<int> fut = tsk.get_future();
    std::future<int> fut2 = tsk2.get_future();
    
    // The tasks will be executed on new threads
    std::thread th{std::move(tsk), 500};
    std::thread th2{std::move(tsk2), 1000};

    int ret = fut.get();
    int ret2 = fut2.get();

    std::cout << ret << " : " << ret2 << std::endl;

    th.join();
    th2.join();

    return 0;
}
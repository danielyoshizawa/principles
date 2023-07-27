// Mutex
// A mutex is a lockable object that is designed to signal when critical sections of code need
// exclusive access, preventing other threads with the same protection from executing concurrently
// and access the same memory locations.

// mutex objects provide exclusive ownership and do not support recursivity
// (i.e., a thread shall not lock a mutex it already owns) -- see recursive_mutex for an
// alternative class that does.

// It is guaranteed to be a standard-layout class.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;


void printWithoutMutex(int n, char c)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << c << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << std::endl;
}

void printWithMutex(int n, char c)
{
    mtx.lock();
    for (int i = 0; i < n; ++i)
    {
        std::cout << c << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << std::endl;
    mtx.unlock();
}

int main()
{
    std::cout << "Without Mutex" << std::endl;
    std::thread t11{printWithoutMutex, 20, '*'};
    std::thread t12{printWithoutMutex, 20, 'p'};
    std::thread t13{printWithoutMutex, 20, '|'};
    std::thread t14{printWithoutMutex, 20, '8'};
    std::thread t15{printWithoutMutex, 20, 'f'};
    std::thread t16{printWithoutMutex, 20, 'a'};

    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();

    std::cout << "-------------" << std::endl;
    std::cout << "With Mutex" << std::endl;
    std::thread t21{printWithMutex, 20, '*'};
    std::thread t22{printWithMutex, 20, 'p'};
    std::thread t23{printWithMutex, 20, '|'};
    std::thread t24{printWithMutex, 20, '8'};
    std::thread t25{printWithMutex, 20, 'f'};
    std::thread t26{printWithMutex, 20, 'a'};

    t21.join();
    t22.join();
    t23.join();
    t24.join();
    t25.join();
    t26.join();

    return 0;
}
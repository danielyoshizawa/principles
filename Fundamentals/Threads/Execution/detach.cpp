#include <iostream>
#include <chrono>
#include <thread>

void takeALongTimeToFinish() {
    std::cout << "Let's sleep a little" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Wow that was a good nap!" << std::endl;
}

int main() {
    std::thread t_(takeALongTimeToFinish);
    // Detachs the thread represented by the object from the calling thread,
    // allowing them to execute independently from each other.
    // Both threads continue without blocking nor synchronizing in any way.
    // Note that when either one ends execution, its resources are released.
    // After a call to this function, the thread object becomes non-joinable and
    // can be destroyed safely.
    t_.detach();
    std::cout << "Will probably execute before the thread finishes" << std::endl;
    return 0;
}
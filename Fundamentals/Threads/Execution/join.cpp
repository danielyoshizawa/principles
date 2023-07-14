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

    // This function returns when the thread execution has completed
    // This synchronizes the moment this function returns with the completion
    // of all the operation in the thread. This blocks the execution of the thread
    // that calls this function, until the function called on construction returns (if it hasn't yet)
    // After a call to this function, the thread object becomes non-joinable and can be
    // destroyed safely.
    t_.join(); // Waits for the thread to finish before returning the control to the main thread.
    std::cout << "Will only execute after the thread finishes" << std::endl;
    return 0;
}
#include <iostream>
#include <boost/asio.hpp>

int main()
{
    // First Create a Context
    boost::asio::io_context io;

    // Creates a timer that receives the context and time
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    std::cout << "Creating the timer" << std::endl;
    // Waiting the timer
    t.wait(); // If it's already finished by this time, it will return immediatelly
    std::cout << "Timer has ended" << std::endl;

    return 0;
}
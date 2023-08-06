// Using a Timer Asynchronosly

// Using asio's asynchronous functionality means supplying a completion token,
// which determines how the result will be delivered to a completion handler when an
// asynchronous operation completes. In this program we define a function called print
// to be called when the asynchronous wait finishes.

#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code & /*e*/)
{
    std::cout << "Hello, world!" << std::endl;
}

int main()
{
    boost::asio::io_context io;

    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

    // Next, instead of doing a blocking wait as in tutorial Timer.1, 
    // we call the steady_timer::async_wait() function to perform an asynchronous wait
    std::cout << "Before async_wait call" << std::endl;
    t.async_wait(&print);
    std::cout << "After async_wait call" << std::endl;

    // Finally, we must call the io_context::run() member function on the io_context object. 
    io.run();

    return 0;
}
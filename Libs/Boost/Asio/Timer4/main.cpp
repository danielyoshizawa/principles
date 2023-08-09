#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

// Timer with member function
class printer
{
private:
    boost::asio::steady_timer timer_;
    int count_;

public:
    printer(boost::asio::io_context &io)
        : timer_(io, boost::asio::chrono::seconds(1)),
          count_(0)
    {
        // The boost::bind() function works just as well with class member functions
        // as with free functions. Since all non-static class member functions have an
        // implicit this parameter, we need to bind this to the function.
        timer_.async_wait(boost::bind(&printer::print, this));
    }

    ~printer()
    {
        std::cout << "Final count is " << count_ << std::endl;
    }

    // Member function used as the completion handler
    void print()
    {
        if (count_ < 5)
        {
            std::cout << count_ << std::endl;
            ++count_;

            timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this));
        }
    }
};

int main()
{
    boost::asio::io_context io;
    printer p(io); // Passing the context to our object
    io.run();

    return 0;
}
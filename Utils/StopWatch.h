#include <chrono>
#include <type_traits>
#include <iostream>
#include <string>

template <typename Resolution = std::chrono::duration<double, std::milli>>
class StopWatch
{
    typedef std::chrono::steady_clock Clock;

private:
    std::chrono::time_point<Clock> last;
    std::string id;
public:
    void reset() noexcept
    {
        last = Clock::now();
    }
    StopWatch(std::string id) noexcept : id{id}
    {
        reset();
    }
    auto operator()() const noexcept // returns time in Resolution
    {
        return Resolution(Clock::now() - last).count();
    }
    ~StopWatch()
    {
        std::cout << id << " : " << (*this)() << " ms" << std::endl;
    }
};
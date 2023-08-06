#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

// This is just the example from the tutorial to test the boost intallation
// lambda is already in Modern C++, [](){}, and I don't think this lib will
// be of much help. I'll leave it here as a Hello World to boost example

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;
    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );

    return 0;
}
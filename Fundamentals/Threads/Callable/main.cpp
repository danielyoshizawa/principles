#include <iostream>
#include <thread>

// Function Pointer
void sumOfAll(int numbers)
{
    int sum{0};
    for (int i{0}; i <= numbers; ++i)
    {
        sum += i;
    }
    std::cout << "Function Pointer | The sum of all numbers is : " << sum << std::endl;
};
// Function Object (Functor)
class functor
{
public:
    void operator()(int numbers)
    {
        // Duplicated only to isolate the usage of callables
        int sum{0};
        for (int i{0}; i <= numbers; ++i)
        {
            sum += i;
        }
        std::cout << "Functor | The sum of all numbers is : " << sum << std::endl;
    }
};

// Lambda Expression

int main()
{
    // Using a Function Pointer as callable
    std::thread t_functionPointer(sumOfAll, 1000000);
    // Using a Functor as callable
    std::thread t_functor(functor(), 1000000);
    // Using a Lambda Function as callable
    auto lambdaFunction = [](int numbers)
    {
        // Duplicated only to isolate the usage of callables
        int sum{0};
        for (int i{0}; i <= numbers; ++i)
        {
            sum += i;
        }
        std::cout << "Lambda | The sum of all numbers is : " << sum << std::endl;
    };
    std::thread t_lambda(lambdaFunction, 1000000);

    // Not using a syncronization technique for this example
    // The output will probably be a mess, and that's the idea
    // to illustrate parallelism, the problem happens because
    // all the threads try to write to cout at the same time.
    t_lambda.join();
    t_functor.join();
    t_functionPointer.join();

    return 0;
}
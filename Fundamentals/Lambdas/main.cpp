#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

// Lambda Expressions (since C++11)
// Constructs a closure : an unname function object capable of capturing variables in scope

// Syntax :
// [](){}
// [captures](params) (optional) specs { body } | until C++ 23
// [captures] attr (params) (options) specs { body } | since C++ 23
// [captures] <tparams> requires (optional) (params) (optional) specs { body } | Since C++ 20 | Until C++ 23
// [captures] <tparams> requires (optional) attr (optional) (params)(opational) specs { body } | Since C++ 23

// Explanation
// captures - A comma-separated list of zero or more captures, optionally beginning with a capture-default
//          - A lambda expression can use a variable without capturing it if the variable:
//            - is a non-local variable or has static or thread local storage duration (in which case the
//              variable cannot be captured), or
//            - is a reference that has been initialized with a constant expression
//          - A lambda expression can read the value of a variable without capturing it if the variable:
//            - has const non-volatile integral or enumeration type and has been initialized witha a constant expressions, or
//            - is constexpr and has no mutable members
// tparams - A non-empty comma-separated list of template parameters, used to provide names to the
//           template parameters of a generic lambda (see ClosureType::operator() below)
// params - The list of parameters, as in named functions. If omitted, function takes no arguments,
//          as if the parameter list were ()
// specs - Consists of specifiers, exceptions, attr, trailing-return-type and requires in that order;
//         each of these components is optional
// specifiers - Optional sequence of specifiers. If not provided, the objects captured by copy are const in
//              the lambda body. The following specifiers are allowed at most once in each sequence:
//              - mutable : allows body to modify the objects captured by copy, and to call their non-const member functions
//              - constexpr : explicity specifies that the function call operator or any given operator template
//              (since C++17) specialization is a constexpr function. When this specifier is not present, the function
//                            call operator or any given operator template specialization will be constexpr anyway,
//                            if it happens to satisfy all constexpr function requirements.
//              - consteval: specifies that the function call operator or any given operator template specialization
//             (since C++20) is an immediate function. consteval and constexpr cannot be used at the same time.
//              - static : specifies that the function call operator or any given operator template specialization
//           (since C++23) is a static member function. mutable and static cannot be used at the same time, and captures
//                         must be empty if static is present.
// exception - Provides the dynamic exception specification or (until C++20) the noexcept specifier for operator() of the closure type
// attr - optional attribute specifier sequence
//        - (until C++23) An attribute specifier sequence applies to the type of the function call operator or
//                        operator template of the closure type. Any attribute so specified does not appertain
//                        the function call operator or operator template itself, but its type (For example, the [[noreturn]] attribute cannot be used)
//        - (since C++23) If an attribute specifier sequence appears before the parameter list, lambda specifiers, or
//                        noexcept specifier, it applies to the function call operator or operator template of the closure type
//                        (and thus the [[noreturn]] attribute can be used). Otherwise, it applies to the type of the function call operator or template operator
// trailing-return-type - -> ret, where ret specifies the return type. If trailing-return-type is not present, the return type of the closure's operator()
//                        is deduced from return statements as if for a function whose return type is declared auto.
// requires - (since C++20) adds constraints to operator() of the closure type
// body - Function body

// (since C++14) If auto is used as a type of a parameter or an explicit template parameter list is provided (since C++20),
//               the lambda is a generic lambda

// The lambda expression is a prvalue expression of unique unnamed non-union non-aggregate class type, known as
// closure type, which is declared (for the purpose of ADL) in the smallest block scope, class scope or namespace scope
// that contains the lambda expression. The closure type has the following members, they cannot be explicit instantiated,
// explicitly specialized, or (since C++14) named in a friend declaration:
// For more info on ClosureType https://en.cppreference.com/w/cpp/language/lambda

// (until C++20) Lambda-expressions are not allowed in unevaluated expressions, templates arguments, alias declarations,
//               typedef declarations, and anywhere is a function (or function template) declaration except the function
//               body and the function's default arguments.

// Lambda capture
// The captures is a comma-separated list of zero or more captures, optionally beginning with the capture-default.
// The capture list defines the outside variables that are accessible from within the lambda function body.
// The only capture default are:
//   - & (implicitly capture the used automatic variables by reference) and
//   - = (implicitly capture the used automatic variables by copy)
// The current object (*this) can be implicitly captured if either capture default is present.
// If implicitly captured, it is always captured by reference, even if the capture default is =.
// The implicit capture of *this when the capture default is = is deprecated (since C++20)

// The syntax of an individual capture in captures is:
// - identifier                                 | simple by-copy capture
// - identifier ...                             | simple by-copy capture that is a pack expansion
// - identifier initializer (since C++14)       | by-copy capture with an initializer
// - & identifier                               | simple by-reference capture
// - & identifier ...                           | simple by-reference capture that is a pack expansion
// - & identifier initializer (since C++14)     | by-reference capture with an initializer
// - this                                       | simple by-reference capture of the current object
// - *this (since C++17)                        | simple by-copy capture of the current object
// - ... identifier initializer (since C++20)   | by-copy capture with an initializer that is a pack extension
// - & ... identifier initializer (since C++20) | by-reference capture with an initializer that is a pack expansion

// If the capture-default is &, subsequent simple captures must not begin with &
struct S1
{
    void f(int i);
};
void S1::f(int i)
{
    [&] {};    // OK : by-reference capture default
    [&, i] {}; // OK: by-reference capture, except i is captured by copy
    // [&, &i] {}; // Error: by-reference capture when by-reference is the default
    [&, this] {};    // OK, equivalent to [&]
    [&, this, i] {}; // OK, equivalent to [&, i]
}

// If the capture-default is =, subsequent simple captures must begin with & or be *this (since C++17) or this (since C++20)
struct S2
{
    void f(int i);
};
void S2::f(int i)
{
    [=] {};        // OK : by-copy capture default
    [=, &i] {};    // OK : by-copy capture, except i is capture by reference
    [=, *this] {}; // until C++17 : Error : invalid syntax
                   // since C++17 : OK : captures the enclosing S2 by copy
    [=, this] {};  // until C++20 : Error : this when = is the default
                   // since C++20 : OK, same as [=]
}

// Any capture may appear only once, and its name must be different from any parameters name
struct S3
{
    void f(int i);
};
void S3::f(int i)
{
    // [i, i] {}; // Error: i repeated
    // [this, *this] {}; // Error : "this" repeated (C++17)
    // [i] (int i) {}; // Error : parameter and capture have the same name
}

int main()
{
    std::cout << "Lambdas" << std::endl;

    int x = 4;
    // &r capture x by reference
    // x = x + 1, in this case x is a variable of
    auto y = [&r = x, x = x + 1]() -> int
    {
        r += 2; // updates ::x to 6
        std::cout << "Value of x inside the lambda    : " << x << std::endl;
        return x * x; // Return 25
    }();

    std::cout << "Value of x after calling lambda : " << x << std::endl;
    std::cout << "Value of y returned by lambda   : " << y << std::endl;

    //  Members of anonymous unions mambers cannot be captured. Bit-fields can only be captured by copy.
    //  If a nested lambda m2 captures something that is also captured by the immediately enclosing lambda m1,
    //  then m2's capture is transformed as follows:
    //    - If the enclosing lambda m1 captures by copy, m2 is capturing the non-static member of m1's
    //      closure type, not the original variable or *this; if m1 is not mutable, the non-static data
    //      member is considered to be const-qualified.
    //    - If the enclosing lambda m1 captures by reference, m2 is capturing the original variable or *this.

    int a = 1, b = 1, c = 1;

    // a captured by copy, b and c by reference
    auto m1 = [a, &b, &c]() mutable // if not mutable, the non-static data member is considered to be const-qualified.
    {
        // a and b captured by copy, c by reference
        // a is a copy in m1, so when m2 captures a its not getting the original variable,
        // but the m1's closure type (first rule)
        // b is a ref in m1, so when captured by m2 it will follow the second rule,
        // in this case b in m2 will be the original variable, since it's capturing a copy
        // m2 will have a copy of the &b from m1, resulting in changes made inside m2 to not
        // affect the original variable.
        // here c still a reference of the firts variable, outside of m1
        // when m2 is called, after this declaration, c is set to 3,
        // so it will print 3 and change c to 4, which will change the first variable.
        auto m2 = [a, b, &c]() mutable
        {
            std::cout << a << b << c << std::endl;
            a = 4;
            b = 4;
            c = 4;
        };
        a = 3;
        b = 3;
        c = 3;
        m2();
    };
    a = 2;
    b = 2;
    c = 2;
    m1();                                  // Calls m2() and prints 123
    std::cout << a << b << c << std::endl; // prints 234

    // The type of a closure cannot be named, but can be inferred with auto
    // since c++14, lambda could own default arguments
    auto f1 = [](int i = 6) -> int
    { return i + 4; };
    std::cout << "f1 : " << f1() << std::endl;

    // Like all callable objects, closures can be captured in std::function
    // (this may incur unnecessary overhead)
    std::function<int(int)> f2 = [](int i) -> int
    { return i + 4; };
    std::cout << "f2 : " << f2(6) << std::endl;

    // Different examples of recursion from cppreference.com
    // Using fibonacci's with std::function in a nested lambda way
    constexpr int fib_max{8}; // constexpr - specifies that the value of a variable or function can appear in constant expressions
    std::cout << "Fibonacci with std::function" << std::endl;
    auto nth_fibonacci = [](int n) -> int
    {
        std::function<int(int, int, int)> fib = [&](int n, int a, int b) -> int
        {
            return n ? fib(n - 1, a + b, a) : b;
        };
        return fib(n, 0, 1);
    };

    // Calling function where n=1
    // n = 1, a = 0, b = 1
    // n = 1 -> fib (0, 1, 0)
    // n = 0 -> b -> 0
    // Calling function where n=2
    // n = 2, a = 0, b = 1
    // n = 2 -> fib (1, 1, 0)
    // n = 1, a = 1, b = 1
    // n = 1 -> fib (0, 1, 1)
    // n = 0 -> b -> 1
    // Calling function where n=3
    // n = 3, a = 0, b = 1
    // n = 3 -> fib (2, 1, 0)
    // n = 2, a = 1, b = 0
    // n = 2 -> fib (1, 1, 0)
    // n = 1, a = 1, b = 0
    // n = 2 -> fib (0, 1, 1)
    // n = 0, a = 1, b = 1
    // n = 1 -> b -> 1
    // Calling function where n=4
    // n = 4, a = 0, b = 1
    // n = 4 -> fib(3, 1, 0)
    // n = 3, a = 1, b = 0
    // n = 3 -> fib(2, 1, 1)
    // n = 2, a = 1, b = 1
    // n = 2 -> fib(1, 2, 1)
    // n = 1, a = 2, b = 1
    // n = 1 -> fib(0, 3, 2)
    // n = 0 -> b -> 2
    // Calling function where n=5
    // n = 5, a = 0, b = 1
    // n = 5 -> fib(4, 1, 0)
    // n = 4, a = 1, b = 0
    // n = 4 -> fib(3, 1, 1)
    // n = 3, a = 1, b = 1
    // n = 3 -> fib(2, 2, 1)
    // n = 2, a = 2, b = 1
    // n = 2 -> fib(1, 3, 2)
    // n = 1, a = 3, b = 2
    // n = 1 -> fib(0, 5, 3)
    // n = 0 -> b -> 3

    for (int i{1}; i <= fib_max; ++i)
    {
        std::cout << nth_fibonacci(i) << (i < fib_max ? ", " : "\n");
    }

    // Lambda using self
    std::cout << "Fibonacci with self" << std::endl;
    // The first arg (auto self) is the recursion, we need to pass the lambda to itself
    auto nth_fibonacci2 = [](auto self, int n, int a = 0, int b = 1) -> int
    {
        return n ? self(self, n - 1, a + b, a) : b;
    };

    for (int i{1}; i <= fib_max; ++i)
    {
        std::cout << nth_fibonacci2(nth_fibonacci2, i) << (i < fib_max ? ", " : "\n");
    }

    // C++23 approach - P0847
    // This feature is not implemented in GCC, and as I read, they don't have plans to do it.
    // Clang is working on it (Issue 59619), and they may release it on CLang 18.
    // For now I don't have a way to test it, but I'll keep it here as it is something at least curious
    // Currently I'm using GCC 12.2.0.
    // We can define this as the first argument, this way we don't need to pass the lambda
    // on function call, same as python or js
#ifdef __cpp_explicit_this_parameter
    std::cout << "C++ approach to lambda recursion " << std::endl;
    auto nth_fibonacci3 = [](this auto self, int n, int a = 0, int b = 1) -> int
    {
        return n ? self(self, n - 1, a + b, a) : b;
    };

    for (int i{1}; i <= fib_max; ++i)
    {
        std::cout << nth_fibonacci3(i) << (i < fib_max ? ", " : "\n");
    }
#endif

    // Here we will use lambdas on the STL, since its largely used on the algorithms
    // it's probably the most used application for lambdas.
    std::vector<int> letsSort = {9, 6, 1, 3, 12, 0, 4};
    auto printVec = [&letsSort]()
    {
        for (auto a : letsSort)
            std::cout << a << " ";
        std::cout << std::endl;
    };
    // C++20
    // template<class RandomIt, class Compare>
    // constexpr void sort(RandomIt first, RandomIt last, Compare comp);
    std::cout << "Original vector" << std::endl;
    printVec();
    std::sort(std::begin(letsSort), std::end(letsSort));
    std::cout << "Default sort (ASC)" << std::endl;
    printVec();
    // This is just an usage example, it is the same as passing
    // std::greater<int> as comp
    std::cout << "Lambda Comparassion function (DESC)" << std::endl;
    auto desc = [](int a, int b) -> bool {
        return b < a;
    };
    std::sort(std::begin(letsSort), std::end(letsSort), desc);
    printVec();
    // Sorting ASC again
    std::sort(std::begin(letsSort), std::end(letsSort));
    std::cout << "Using std::greater (same result as the last example)" << std::endl;
    std::sort(std::begin(letsSort), std::end(letsSort), std::greater<int>());
    printVec();
    
    return 0;
}
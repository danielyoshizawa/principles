#include <iostream>
#include <vector>
#include <string>
// Variadic template is a template, which can take an arbitrary number of template
// arguments of any type. Both the classes and functions can be variadic.
//
template <typename... Arguments>
class VariadicTemplate
{
};

// Any of the following ways to create an instance of this class template is valid:
VariadicTemplate<double, float> instance;
VariadicTemplate<bool, unsigned short int, long> instance_;
VariadicTemplate<char, std::vector<int>, std::string, std::string, std::vector<long long>> instance__;

// The number of variadic template arguments can also be zero
// VariadicTemplate<> instance;

// However, if you create a template like this
template <typename T, typename... Arguments>
class VariadicTemplate2
{
};

// This will be invalid
// VariadicTemplate2<> instance;

// You must set at least one type as a template argument (for typename T), unless default type has
// been initialized, like in the following declaration
//
template <typename T = int, typename... Arguments>
class VariadicTemplate3
{
};

VariadicTemplate3<> instance3;

// The ellipsis operator (...)
// The ellipsis operator (...) is an operator used in different contexts in C++. It's name comes
// from an ellipsis mechnism in C. In this mechanism programmer can create a function taking
// variable number of parameters. Probably the most famous function in both C and C++
// to take advantage of this mechanism is printf function in C standard library:

int printf(const char *, ...);

// Ellipsis mechanism can also be used with preprocessor in a form of a macro. A macro taking
// a variable number of parameters is called a variadic macro

#define VARIADIC_MACRO(...)

// In C++, this elipsis operator got a new meaning in different context called exception handling.
// The operator is used in catch blocks after try blocks:

void exceptionHandling()
{
    try
    {
        // Do something
    }
    catch (...)
    {
        // Catch any exception
    }
};

// Here, the ellipsis operator indicates that the catch block takes in any exception thrown from
// the try block as it's parameter, no matter the type.

// In C++ 11, variadic templates brought yet another meaning for this operator. The operator
// works somewhat like in ellipsis mechanism as already stated, but it's a bit more complex:

template <typename... Arguments>
void SampleFunction(Arguments... parameters);

// Here's a function template. The contents of the variadic template arguments are called parameter packs.
// These packs will then be unpacked inside the function parameters. For example, if you create a function
// call to the previous variadic function template...

// SampleFunction<int, int>(16, 24);

// ... an equivalent function template would be like this:

template <typename T, typename U>
void SampleFunction(T param1, T param2);

// Sizeof... operator
// Another operator used with variadic templates is the sizeof... - operator. Unlike the sizeof operator,
// which can be used to determine the size of a type (for example sizeof(int) or sizeof(double)),
// sizeof... operator can be used to determine the amount of types given into a variadic template.
// This can be achieved like this:

template <typename... Arguments>
class VariadicTemplate4
{
private:
    static const unsigned short int size = sizeof...(Arguments);
};

// Two ellipsis operators together (......)
// In some circumstances, there can be two ellipsis operators put together (......).
// These two operators can also be separated (written as ... ...)
// Probably the most clear way, however, is to separate these twoo operator with a comma (...,...).
// Both ways with a comman or without a comma are acceptable
// This kink of syntax can appear with variadic function templates using ellipsis mechanism:

template <typename... Arguments>
void SampleFunction2(Arguments..., ...){

};

// TODO : Write examples using this syntax, so far it doesn't make any sense to me

// Inheritance and initialization lists
// When it comes to classes, variadic templates can be used with inheritance and initialization lists.
// Inheritance taking advantage of variadic templates can be accomplished like this:

template <typename... BaseClasses>
class VariadicTemplate5 : public BaseClasses... // Inheritance
{
public:
    // Constructor with initialization list
    // Create a constructor inside this class using initialization list to call
    // the constructors of all the given base classes as template arguments.
    VariadicTemplate5(BaseClasses &&...base_classes) : BaseClasses(base_classes)...
    {
    }
};

// As you can see there's a new operator introduced in C++11 in the constructor's parameter list
// an rvalue operator (&&), which allows rvalue references.

// Variadic class template specialization
// Like class templates, variadic class templates can also be specialized. With templates,
// the specialization happens like this

template <typename T>
class Template
{
public:
    void SampleFunction(T param)
    {
    }
};

template <>
class Template<int>
{
public:
    void SampleFunction(int param)
    {
    }
};

// But with variadic templates it's like the following

template <typename... Arguments>
class VariadicTemplate6
{
public:
    void SampleFunction(Arguments... params)
    {
    }
};

template <>
class VariadicTemplate6<double, int, long>
{
public:
    void SampleFunction(double param1, int param2, long param3)
    {
    }
};

// Caution : Some compilers may not support variadic class template specialization yet,
//           or their implementation may be somewhat incomplete.

// Conclusion:
// Tempaltes have been a powerful feature in C++. Now, after the introduction of variadic templates,
// templates have proven themselves even more powerful. Variadic tamplates are a trustworthy solution
// to implement delegates and tuples. And, instead of C-Style ellipsis mechanism, variadic templates
// can offer a typesafer solution to replace them.

// Here is my personal take on Variadic Templates
template <class... Arguments>
class VariadicTemplatesExample
{
public:
    VariadicTemplatesExample(Arguments &&...params)
    {
        // Fold Expressions (C++17)
        ([&]
         { std::cout << params << " - "; }(),
         ...);

        std::cout << std::endl;
    }
};

// Can I have types after the parameter pack?
// I can't, but I can have arguments in a function after a pack.
template <class T, class... Arguments>
class VariadicTemplatesExample2
{
public:
    void MultipleTypes(Arguments &&...params, T &total)
    {
        T sum = 0;
        ([&]
         { sum += params; }(),
         ...);
        std::cout << sum << std::endl;
        total = sum;
    }
};

int main()
{
    VariadicTemplatesExample<int, double, int, float, short> vTemplate{1, 2.0, 3, 4.34f, short(5)};
    VariadicTemplatesExample<double, std::string, int, short> vTemplate2{1.11, "Hey not a number", 3, short(4)};

    VariadicTemplatesExample2<int, int, int, int> vTemplateE1;
    int total = 0;
    vTemplateE1.MultipleTypes(1, 2, 3, total);
    std::cout << "Total after function call : " << total << std::endl;

    VariadicTemplatesExample2<double, double, double, double, double> vTemplateE2;
    double total2 = 0.0;
    vTemplateE2.MultipleTypes(1.12, 2.23, 3.34, 4.45, total2);
    std::cout << "Total after function call : " << total2 << std::endl;

    return 0;
}
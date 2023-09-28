#include <utility>
#include <iostream>
#include <memory>

struct A
{
    A(int &&n)
    {
        std::cout << "Calling A RValue constructor" << std::endl;
    }
    A(int &n)
    {
        std::cout << "Calling A LValue constructor" << std::endl;
    }
};

struct B
{
    B(int &&i, double&& d, std::string&& s)
    {
        std::cout << "Calling B RValue constructor" << std::endl;
    }
    B(int &i, double& d, std::string& s)
    {
        std::cout << "Calling B LValue constructor" << std::endl;
    }
};

auto make_obj_a(auto && ... args) // C++ 20
{
    // Without Perfect Forwarding all calls to A will be of LValue Types
    // return A((args)...);
    return A(std::forward<decltype(args)>(args)...);
};

template<class T>
auto make_obj(auto && ... args) // C++ 20
{
    // Without Perfect Forwarding all calls will be of LValue Types
    // return T((args)...);
    return T(std::forward<decltype(args)>(args)...);
};

// Before C++ 20
template<class T, class... U>
T make_obj_old(U && ... u)
{
    return T(std::forward<U>(u)...);
};

int main()
{
    // Passing RValue
    A a1 = A(5);
    // Passing LValue
    int arg = 5;
    A a2 = A(arg);
    // Calling make_obj_a usign RValue
    A a3 = make_obj_a(5);
    // Calling make_obj_a using LValue
    A a4 = make_obj_a(arg);
    // Using templates on make_obj with RValue
    A a5 = make_obj<A>(5);
    // Using templates on make_obj with LValue
    A a6 = make_obj<A>(arg);
    // Calling make_obj using type B RValue
    B b1 = make_obj<B>(4, 2.0, std::string("Hello"));
    // Calling make_obj using type B LValue
    double d = 2.0;
    std::string str = "Hello";
    B b2 = make_obj<B>(arg, d, str);
    // Calling make_obj_old with RValue
    B b3 = make_obj_old<B>(4, 2.0, std::string("Hello"));
    // Calling make_obj_old with LValue
    B b4 = make_obj_old<B>(arg, d, str);

    return 0;
}
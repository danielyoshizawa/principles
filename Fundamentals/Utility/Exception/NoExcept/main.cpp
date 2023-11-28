// noexcept specifier - since C++11
// Specifies whether a function could throw exceptions.
//
// Syntax
// noexcept              (1)
// noexcept(expression)  (2)
// throw()               (3) // Deprecated in C++17 | Removed C++20
//
// 1. Same as noexcept(true)
// 2. If expression evaluates to true, the function is declared not to throw any exceptions.
//    A "(" following noexcept is always a part of this form (it can never start an initializer).
// 3. Same as noexcept(true) (see dynamic exception specification for its semantics before C++17)
//
// expression - contextually converted constant expression of type bool.
//
// Explanation
// The noexcept-specification is not a part of the function type (just like dynamic exception specifications)
// and can only appear as part of a lambda declarator or a top-level function declarator when declaring
// functions, variables, non-static data members of type function, pointer to function, reference to
// function, or pointer to member function, and also when declaring a parameter or a return type in
// one of those declarations that in turn happens to be a pointer or reference to functon.
// It cannot appear in a typedef or type alias declaration.
//
// Until C++17
// void f() noexcept; // the function f() does not throw
// void (*fp)() noexcept(false); // fp points to a function that may throw
// void g(void pfa() noexcept); // g takes a pointer to function that doesn't throw
// typedef int(*pf)() noexcept; // error
//
// Since C++20
// The noexcept-specification is a part of the function type and may appear
// as part of any function declarator
//
// Every function in C++ is either non-throwing or potentially throwing:
// - potentially-throwing functions are:
//   - functions declared with a non-empty dynamic exception specification // until C++17
//   - functions declared with noexcept specifier whose expression evaluates to false
//   - functions declared without noexcept specifier except for
//     - destructors unless the destructor of any potentially-constructed base or member is
//       potentially-throwing (see below).
//     - default constructors, copy constructors, move constructors that are implicitly-declared
//       or defaulted on their first declaration unless
//       - a constructor for a base member that implicit definition of the constructor would call
//         is potentially-throwing (see below)
//       - a subexpression of such an initialization, such as a default argument expression, is
//         potentially-throwing (see below)
//     - copy assignment operators, move assignment operators that are implicitly-decalred or
//       defaulted on their first declaration unless the invocation of any assignment operator in
//       the implicit definition is potentially-throwing (see below)
//     - comparison operators that are defaulted on their first declaration unless the invocation
//       of any comparison operator in the implicit definition is potentially-throwing (see below) // Since C++20
//     - deallocation functions
// - non-throwing functions are all others (those with noexcept speficier whose expression evaluates
//   to true as well as destructors, defaulted special member functions, and deallocation functions)
//
// Explicit instantiations may yse the noexcept specifier, but it is not required. If used, the exception
// specification must be the same as for all other declarations. A diagnostic is required only if the exception
// specification are not the same within a single translation unit.
//
// Functions differing only in their exception specification cannot be overloaded (just like the
// return type, exception specification is part of function type, but not part of the function signature) // Since C++17
//
// void f() noexcept;
// void f(); // error : different exception specification
// void g() noexcept(false);
// void g(); // ok, both declarations for g are potentially-throwing
//
// Pointers (including pointers to member function) to non-throwing functions can be asssigned to or
// used to initialize (until C++17) are implicitly convertible to (since C++17) pointers to
// potentially-throwing functions, but not the other way around.
//
// void ft(); // potentially-throwing
// void (*fn)() noexcept = ft; // error
//
// If a virtual function is non-throwing, all declarations, including the definition, of every overrider
// must be non-throwing as well, unless the overrider is defined as deleted:
//
struct B
{
    virtual void f() noexcept;
    virtual void g();
    virtual void h() noexcept = delete;
};

struct D : B
{
    // void f(); // ill-formed: D::f is potentially-throwing, B::f is non-throwing
    void f() noexcept;
    void g() noexcept; // OK
    // void h() = delete; // ill-formed : looser exception specification on overriding virtual function
    void h() noexcept = delete; // OK
};

// Non-throwing functions are permitted to call potentially-throwing functions. Whenever an exception
// is thrown and the search for a handler encounters the outermost block of a non-throwing function,
// the function std::terminate is called:

// extern void f(); // potentially-throwing

// void g() noexcept
// {
//     f();      // valid, even if f throws
//     throw 42; // valid (warning), effectively a call to std::terminate
//     // warning: throw’ will always call ‘terminate’
// };
//
// The exception specification of a function template specialization is not instantiated along with
// the function declaration; it is instantiated only when needed (as defined below).
//
// The exception-specificaiton of an implicitly-declared special member function is also evaluated
// only when needed (in particular, implicit declaration of a member function of a derived class
// does not require the exception-specification of a base member function to be instantiated).
//
// When the noexcept-specification of a function template specialization is needed, but hasn't yet
// been instantiated, the dependent names are lookd up and any templates used in the expression are
// instantiated as if for the declaration of the specialization.
//
// A noexcept-speciation of a function is considered to be needed in the following contexts:
// - in a expression, where the function is selected by overload resolution
// - the function is odr-used (One Definition Rule)
// - the function would be odr-used but appears in an unevaluated operand
//
//   template<class T>
//   T f() noexcept(sizeof(T) < 4);
//
//   int main()
//   {
//      decltype(f<void>()) *p; // f unevaluated, but noexcept-spec is needed
//                              // error because instantiation of the noexcept specification
//                              // calculates sizeof(void)
//   }
//
//   - the specification is needed to compare to another function declaration (e.g. on a virtual
//     function overridder or on an explicit specialization of a function template)
//   - in a function definition
//   - the specification is needed because a defaulted special member function needs to check it
//     in order to decide its own exception specificaion (this takes place only when the specification
//     of the defaulted special member function is, itself, needed).
//
// Formal definition of potentially-throwing expression (used to determine the default exception
// specification of destructors, constructors, and assignment operators as described above):
//
// An expression e is potentially-throwing if:
// - e is a function call to a function, pointer to function, or pointer to member function which is
//   potentially-throwing, unless e is a core constant expression (until C++17)
// - e makes an implicit call to a potentially-throwing function (such as an overloaded operator, an
//   allocation function in a new-expression, a constructor for a function argument, or a destructor
//   if e is a full-expression)
// - e is a throw-expression
// - e is a dynamic_cast that casts a polymorphic reference type
// - e is a typeid expression applied to a dereferenced pointer to a polymorphic type
// - e has an immediate subexpression that is potentially-throwing
//
//   struct A
//   {
//      A(int = (A(5), 0)) noexcept;
//      A(const A&) noexcept;
//      A(A&&) noexcept;
//      ~A();
//   };
//
//   struct B
//   {
//      B() throw();
//      B(const B&) = default; // implicit exception specification is noexcept(true)
//      B(B&&, int = (throw Y(), 0)) no except;
//      ~B() noexcept(false);
//   };
//
//   int n = 7;
//   struct D: public A, public B
//   {
//      int *p = new int[n];
//      // D::D() // potentially-throwing because of the new operator
//      // D::D(const D&) non-throwing
//      // D::D(D&&) potentially-throwing: the default argument for B's constructor may throw
//      // D::~D() potentially-throwing
//
//      // note: if A::~A() were virtual, this program would be ill-formed because an overrider
//      //       of a non-throwing virtual cannot be potentially-throwing
//   }
//
// Notes
// One of the uses of the constant expression is (along with the noexcept operator) to define function
// templates that declare noexcept for some type but not others.
//
// Note that a noexcept specification on a function is not a compile-time check; it is merely a method
// for a programmer to inform the compiler wheter or not a function should throw exceptions. The compiler
// can use this information to enable certain optimizations on non-throwing functions as well as enable
// the noexcept operator, which can check at compile time if a particular expression is declared to
// throw any exceptions. For example, containers such as std::vector will move their elements if the
// elements move constructor is noexcept, and copy otherwise (unless the copy constructor is not
// accessible, but a potentially throwing move contructor is, in which case the strong exception
// guarantee is waived).
//
// Deprecates
// noexcept is an improved version of throw(), which is depreacated in C++11. Unlike pre-C++17 throw(),
// noexcept will not call std::unexpected, may or may not unwind the stack, and will call std::terminate,
// which potentially allows the compiler to implement noexcept without the runtime overhead of throw().
// As of C++17, throw() is redefined to be an exact equivalent of noexcept(true).
//
// Feature-test macro           || Value   || Std   || Feature
// __cpp_noexcept_function_type || 201510L || C++17 || Make exception specifications be part of the type system

#include <iostream>

// whether foo is declared noexcept depends on if the expression T() will throw any exceptions
template <class T>
void foo() noexcept(noexcept(T())) {}

void bar() noexcept(true) {}
void baz() noexcept { throw 42; } // noexcept is the same as noexcept(true)
// warning: ‘throw’ will always call ‘terminate’

int main()
{
    foo<int>(); // noexcept(noexcept(int())) => noexcept(true), so this is fine

    bar(); // fine
    baz(); // compiles, but at runtime this calls std::terminate

    return 0;
}

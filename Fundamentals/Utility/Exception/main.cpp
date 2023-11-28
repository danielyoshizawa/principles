// Exceptions
//
// Exceptions provide a way to react to exceptional circusmstances (like runtime errorrs)
// in programs by transfering control to special functions called handlers.
//
// To catch exceptions, a portion of code is placed under exception inspection.
// This is done by enclosing that portion of code in a try-catch. When an exceptional
// circumstance arises within that block, an exception is thrown that transfers the controle
// to the exception handler. If no exception is thrown, the code continues normally and all
// handlers are ignored.
//
// An exception is thrown by using the throw keyword from inside the try block.
// Exception handlers are declare with the keyword catch, which must be placed immediately
// after the try block:

#include <iostream>

inline void basic_exception()
{
    try
    {
        throw 20;
    }
    catch (int e)
    {
        std::cout << "An exception occurred. Exception Nr. " << e << std::endl;
    }
};

// The code under exception handling is enclosed in a try bloc. In this example this code
// simply throws an exception
//
// throw 20;
//
// A throw expression accepts one parameter (in this case the integer value 20), which is passed
// as an argument to the exception handler.
//
// The exception handler is declared with the catch keyword immediately after the closing brace of
// the try block. The syntax for catch is similar to a regular function with one parameter. The
// type of this parameter is very important, since the type of the argument passed by the throw
// expression is checked against it, and only in the case they match, the exception is caught
// by that handler.
//
// Multiple handlers (i.e. catch expressions) can be chained; each one with a different parameter
// type. Only the handler whose argument type matches the type of the exception specified in the
// throw statement is executed.
//
// If an ellipsis (...) is used as the parameter of catch, that handler will catch any exception
// no matter what the type of the exception thrown. This can be used as a default handler that
// catches all exceptions not caught by other handlers:

#include <exception>

inline void multiple_handlers()
{
    try
    {
        throw std::bad_cast();
    }
    catch (int param)
    {
        std::cout << "Int exception" << std::endl;
    }
    catch (char param)
    {
        std::cout << "Char exception" << std::endl;
    }
    catch (...)
    {
        std::cout << "Default exception" << std::endl;
    }
}

// In this case, the last handler would catch any exception thrown of a type that is neither int
// nor char.
//
// After an exception has been handles the program, execution resumes after the try-catch block,
// not after the throw statement.
//
// It is also possible to nest try-catch blocks within more external try blocks. In these cases,
// we have the possibility that an internal catch block forwards the exception to its external level.
// This is done with the expression throw; with no arguments.

inline void nested_handlers()
{
    try
    {
        try
        {
            throw "Something";
        }
        catch (...)
        {
            throw;
            std::cout << "Shouldn't call me" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "Nested handlers" << std::endl;
    }
}

// Exception Specification
//
// Older code may contain dynamic exception specifications. They are now deprecated in C++, but
// still supported. A dynamic exception specification follows the declaration of a function,
// appending a throw specifier to it.For example:
//
// double my_function (char param) throw (int);
//
// This declares a function called my_function, which takes one argument of type char and returns a
// value of type double. If this function throws an exception of some type other than int, the
// function calls std::unexpected instead of looking for a handler or calling std::terminate.
//
// If this throw specifier is left empty with no type, this means that std::unexpected is called
// for any exception. Functions with no throw specifier (regular functions) never call std::unexpected,
// but follow the normal path of looking for their exceptions handler.
//
// int my_function(int param) throw(); // all exeptions call unexpected
// int my_function(int param);         // normal exception handling
//
// Standard exceptions
//
// The C++ Standard library provides a base class specifically designed to declare objects to be
// thrown as exceptions. It is called std::exception and is defined in the <exception> header.
// This class has a virtual member function called what that returns a null-terminated character
// sequence (of type char *) and that can be overwritten in derived classes to contain some sort
// of description of the exception.

#include <iostream>
#include <exception>

class myexception : public std::exception
{
    virtual const char *what() const throw() // Deprecated C++17 | Removed C++20
    {
        return "My exception happened";
    }
} myex;

inline void custom_exception()
{
    try
    {
        throw myex;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

// We have places a handler that catches exception objects by reference (notice the ampersand & after
// the type), therefore this catches also classes derived from exception, like our myex object of type
// myexception
//
// All exceptions thrown by components of the C++ Standard library throw exceptions derived from
// this std::exception class. These are:
//
// Exception         || Description
// bad_alloc         || thrown by new on allocation failure
// bad_cast          || thrown by dynamic_cast when it fails in a dynamic cast
// bad_exception     || thrown by certain dynamic exception specifiers
// bad_typeid        || thrown by typeid
// bad_function_call || thrown by empty function objects
// bad_weak_ptr      || thrown by shared_ptr when passed a bad weak_ptr
//
// Also deriving from exception, header <exception> defines two generic exception types that can be
// inherited by custom exceptions to report errors:
//
// Execption     || Description
// logic_error   || error related to the internal logic of the program
// runtime_error || error detected during runtime
//
// A typical excample where standard exceptions need to be checked for is on memory allocation:
//
inline void bad_alloc_exception()
{
    try
    {
        int *myarray = new int[1000]; // it will work, it's just for ilustration
    }
    catch (std::exception &e)
    {
        std::cout << "Standard exception : " << e.what() << std::endl;
    }
}

// The exception that may be caught by the exception handler in this example is bad_alloc.
// Because bad_alloc is derived from the standard base class exception, it can be caught
// (capturing by reference, captures all related classes).

int main()
{
    basic_exception();
    multiple_handlers();
    nested_handlers();
    custom_exception();
    bad_alloc_exception();

    return 0;
}
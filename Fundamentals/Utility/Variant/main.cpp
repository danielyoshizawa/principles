// Variant
// Defined in header <variant>
//
// Since c++17
// template <class... Types>
// class variant;
//
// The class template std::variant represents a type-safe union.
// An instance of std::variant at any given time either holds a value
// of one of its alternative types, or in the case of error - no value
// (this state is hard to achieve, see valueless_by_exception).
//
// As with unions, if a variant holds a value of some object type T,
// the object representation of T is allocated directly within the object
// representation of the variant itself. Variant is not allowed to allocate
// additional (dynamic) memory.
//
// A variant is not permitted to hold references, arrays, or the type void.
// Empty variants are also ill-formed (std::variant<std::monostate>
// can be used instead).
//
// A variant is permitted to hold the same type more than once, and to hold
// differently cv-qualified versions of the same type.
//
// Consistent with the behavior of unions during aggregate initialization,
// a default-constructed variant holds a value of its first alternative,
// unless that alternative is not default-constructible (in which case the
// variant is not default-constructible either). The helper class std::monostate
// can be used to make such variants default-constructible.
//
// Template parameters
// Types - The types that may be stored in this variant. All types must meet
//         the Destructible requirements (in particular, array types and
//         non-object types are not allowed).
//

#include <iostream>
#include <variant>
#include <string>
#include <cassert>

int main()
{
    std::cout << "Variant" << std::endl;

    // std::variant<Types...>::index
    // constexpr std::size_t index() const noexcept; (since c++17)
    //
    // Returns the zero-based index of the alternative that is currently
    // help by the variant. If the variant is valueless_by_exception,
    // returns variant_npos (-1).
    std::variant<bool, int> v;
    v = true;
    std::cout << "Current index (v = true) : " << v.index() << std::endl;
    v = 42;
    std::cout << "Current index (v = 42) : " << v.index() << std::endl;

    // std::holds_alternative (since C++17)
    // template<class T, class... Type>
    // constexpr bool holds_alternative( const std::variant<Type...> &v) noexcept;
    //
    // Checks if the variant v holds the alternative T. The call is ill-formed if T
    // does not appear exactly once in Types...
    //
    // Parameters
    // v - variant to examine
    //
    // Return value
    // true if the variant currently holds the alternative T, false otherwise.

    std::cout << std::boolalpha << "Variant holds int ? : "
              << std::holds_alternative<int>(v) << std::endl;
    std::cout << std::boolalpha << "Variant holds bool ? : "
              << std::holds_alternative<bool>(v) << std::endl;
    // Compile error : static assertion failed - T must occur exactly
    //                 once in alternatives
    // std::cout << std::boolalpha << "Variant holds string ? : "
    //           << std::holds_alternative<std::string>(v) << std::endl;

    v = true;
    std::cout << "Changing to bool and asking again" << std::endl;
    std::cout << std::boolalpha << "Variant holds int ? : "
              << std::holds_alternative<int>(v) << std::endl;
    std::cout << std::boolalpha << "Variant holds bool ? : "
              << std::holds_alternative<bool>(v) << std::endl;

    // std::get (std::variant)
    auto w = std::get<bool>(v);
    std::cout << std::boolalpha << "Using get worked ? " << w << std::endl;
    v = 42;
    auto z = std::get<1>(v);
    std::cout << "Changing to int and using get by id : " << z << std::endl;

    // std::monostate (since c++17)
    // struct monostate { };
    //
    // Unit type intended for use as a well-behaved empty alternative in
    // std::variant. In particular, a variant of non-default-constructible
    // types may list std::monostate as its firts alternative: this makes
    // the variant itself default-constuctible.

    // Non-default-constructible type
    struct S
    {
        S(int i) : i(i) {}
        int i;
    };

    // std::variant<S> var; // will not compile, non-default-constructible type
    std::variant<std::monostate, S> var;
    assert(var.index() == 0);

    try
    {
        std::get<S>(var); // throws! We need to assign a value
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    var = 42;
    std::cout << "std::get: " << std::get<S>(var).i << std::endl;
    std::cout << "std::hash: " << std::hex << std::showbase
              << std::hash<std::monostate>{}(std::monostate{}) << std::endl;

    return 0;
}
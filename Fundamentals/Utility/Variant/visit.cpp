// std::visit
// Defined in header <variant>
//
// 1) template<class Visitor, class... Variants>
//    constexpr /* see below ? */ visit( Visitor && vis, Variants&&... vars); (since c++17)
// 2) template<class R, class Visitor, class... Variants>
//    constexpr R visit( Visitor&& vis, Variants&&... vars); (since c++20)
// 3) template<class... Ts>
//    auto&& as-variant(std::variant<Ts...>& var); (exposition only)
// 4) template<class... Ts>
//    auto&& as-variant( const std::variant<Ts..>& var); (exposition only)
// 5) template<class... Ts>
//    auto&& as-variant(std::variant<Ts...>&& var); (exposition only)
// 6) template<class... Ts>
//    auto&& as-variant(const std::variant<Ts...> && var); (exposition only)
//
// Applies the visitor vis (a Callable that can be called with any
// combination of types from variants) to the variants vars.
// Given VariantBases as deltype (as-variant(std::forward<Variants>(vars))...
// (a pack of sizeof...(Variants) types):
// 1) Invokes vis as if by
//    INVOKE(std::forward<Visitor>(vis),
//           std::get<indices>(std::forward<VariantBases>(vars))...)
//    where indices is as-variant(vars).index()...
// 2) Invokes vis as if by
//    INVOKE<R>(std::forward<Visitor>(vis),
//              std::get<indices>(std::forward<VariantBases>(vars))...)
//    where indices is as-variant(vars).index()...
//
// These overloads participate in overload resolution only if every type in
// VariantBases is a valid type. If the expression denoted by INVOKE or INVOKE<R>
// (since c++20) is invalid, or the results of INVOKE or INVOKE<r> have different
// types or value categories for different indices, the program is ill-formed.
//
// 3-6) The exposition-only as-variant function template accpet a value whose
//      type can be deduced for std::variant<Ts...>(i.e. either std::variant<Ts...>
//      or a type derived from std::variant<Ts...>), and return the std::variant
//      value with the same const-qualification and value category.
// 3,4) Returns var
// 5,6) Returns std::move(var)
//
// Parameters
// vis - a Callable that accepts every possible alternative from every variant
// vars - list of variants to pass to the visitor
//
// Return value
// 1) The result of the INVOKE operation. The return type is the type obtained
//    from applying decltype to the result.
// 2) Nothing if R is (possibly cv-qualified) void; otherwise the result of the
//    INVOKE<R> operation.
// 3-6) A std::variant value converted from var.
//
// Exceptions
// Throws std::bad_variant_access if as-variant(vars_i).valueless_by_exception()
// is true for any variant vars_i in vars.

#include <iostream>
#include <iomanip>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>

// the variant to visit
using var_t = std::variant<int, long, double, std::string>;

// helper constant for the visitor #3
template <class>
inline constexpr bool always_false_v = false;

// helper type for the visitor #4
template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
// explicit deduction guide (not needed as of c++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

int main()
{
    std::vector<var_t> vec = {10, 15l, 1.5, "hello"};

    for (auto &v : vec)
    {
        // 1. void visitor, only called for side-effects (here, for I/O)
        std::visit([](auto &&arg)
                   { std::cout << arg << std::endl; },
                   v);

        // 2. value-returning visitor, demonstrates the idiom
        //    of returning another variant
        var_t w = std::visit([](auto &&arg) -> var_t
                             { return arg + arg; },
                             v);
        // 3. type-matching visitor: a lambda that handles each
        //    type differently
        std::cout << ". After doubling, variant holds ";
        std::visit([](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int with value " << arg << std::endl;
            else if constexpr (std::is_same_v<T, long>)
                std::cout << "long with value " << arg << std::endl;
            else if constexpr (std::is_same_v<T, double>)
                std::cout << "double with value " << arg << std::endl;
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "std::string with value " << std::quoted(arg) << std::endl;
            else
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }, w);
    }

    for (auto& v: vec)
    {
        // 4. another type-matching visitor: a class with 3 overloaded operator()'s
        // Note: The `(auto arg)` template operator() will bind to `int` and `long`
        //       in this case, but in its absence the `(double arg)` operator()
        //       *will also* bind to `int` and `long` because both are implicitly
        //       convertible to double. When using this form, care has to be taken
        //       that implicit conversions are handled correctly.
        std::visit(overloaded{
            [](auto arg) { std::cout << arg << " "; },
            [](double arg) { std::cout << std::fixed << arg << " "; },
            [](const std::string &arg){ std::cout << std::quoted(arg) << " ";}
        }, v);
    }
    std::cout << std::endl;
    return 0;
}
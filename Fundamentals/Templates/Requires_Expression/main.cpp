// Requires expressions
// Yields a prvalue expression type bool that describes the constraints.

// Syntax
// requires { requirement-seq }
// requires (parameter-list (optional)) { requirement-seq }
//
// parameter-list - a comma-separated list of parameters like in a function declaration,
//                  except that default arguments are not allowed and it cannot end with an
//                  ellipsis (other than one signifying a pack expansion). There parameters have
//                  no storage, linkage or lifetime, and are only used to assist in specifying
//                  requirements. There parameters are in scope until the closing } of the
//                  requirement-seq.
// requirement-seq - sequence of requirements, each requirement is one of the following:
//                   - simple requirement
//                   - type requirements
//                   - compound requirements
//                   - nested requirements
//
// Explanation
// Requirements may refet to the template parameters that are in scope, to the local parameters
// introduced in the parameter-list, and to any other declarations that are visible from the
// enclosing context.
// The substitution of template arguments into a requires-expression used in a declaration of
// a templated entity may result in the formation of invalid types or expressions in its requirements,
// or the violation of semantic constraints of those requirements. In such cases, the requires-expressions
// evaluates to false and does not cause the program to be ill-formed. The substitution and semantic constraint
// checking proceeds in lexical order and stops when a condition that determines the result of the
// requires-expression is encountered. If substitution (if any) and semantic constraint checking
// succeed, the requires-expression evalueates to true.
// If a substitution failure would occur in a requires-expression for every possible template argument,
// the program is ill-formed, no diagnostic required:
template <class T>
concept C = requires {
    new int[-(int)sizeof(T)]; // invalid for every T: ill-formed, no diagnostic required
};
// If a requires-expression contains invalid types or expressions in its requirements, and it does
// not appear within the declaration of a templated entity, then the program is ill-formed.
//
// Simple requirements
// A simple requirement is an arbitrary expression statement that does not start with the keyword
// requires. It asserts that the expression is valid. The expression is an unevaluated operand;
// only language correctness is checked.
template <typename T>
concept Addable2 = requires(T a, T b) {
    a + b; // "the expression a+b is a valid expression that will compile"
};

#include <utility>

template <class T, class U = T>
concept Swappable = requires(T &&t, U &&u) {
    std::swap(std::forward<T>(t), std::forward<U>(u));
    std::swap(std::forward<U>(u), std::forward<T>(t));
};

// A requirement that starts with the keyword requires is always interpreted as a nested requirement.
// Thus a simple requirement cannot start with an unparenthesized requires-expression.
//
// Type requirements
// A type requirement is the keyword typenmae followed by a type name, optionally qualified.
// The requirement is that the named type is valid: this can be used to verify that a certain
// named nested type exists, or that a class template specialization names a type, or that an
// alias template specialization names a type. A type requirement naming a class template
// specialization does not require the type to be complete.
template <typename T>
using Ref = T &;

template <typename T>
struct S
{
};

template <typename T>
concept B = requires {
    typename T::inner; // required nested member name
    typename S<T>;     // required class template specialization
    typename Ref<T>;   // required alias template substitution
};

template <class T, class U>
using CommonType = std::common_type_t<T, U>;

template <class T, class U>
concept Common = requires(T &&t, U &&u) {
    typename CommonType<T, U>; // CommonType<T,U> is valid and names a type
    {
        CommonType<T, U>{std::forward<T>(t)}
    };
    {
        CommonType<T, U>{std::forward<U>(u)}
    };
};

// Compund requirements
// A compound requirement has the form :
// { expression } noexcept (optional) return-type-requirement (optional);
// return-type-requirement - -> type-constraint
//
// and asserts properties of the named expression. Substitution and semantic constraint checking
// proceeds in the following order:
// - Template arguments (if any) are substituted into expressions
// - If noexcept is used, expression must not be potentially throwing
// - If return-type-requirement is present, then:
//   - Template arguments are substituted into the return-type-requirement
//   - decltype((expression)) must satisfy the constraint imposed by the type-constraint.
//     Otherwise, the enclosing requires-expression is false.
template <typename T>
concept D = requires(T x) {
    // the expression *x must be valid
    // AND the type T::inner must be valid
    // AND the result of *x must be convertible to T::inner
    {
        *x
    } -> std::convertible_to<typename T::inner>;

    // the expression x + 1 must be valid
    // AND std::same_as<decltype((x+1)), int> must be satisfied
    // i.e., (x+1) must be a prvalue of type int
    {
        x + 1
    } -> std::same_as<int>;

    // the expression x * 1 must be valid
    // AND its result must be convertible to T
    {
        x * 1
    } -> std::convertible_to<T>;
};
//
// Nested requirements
// A nested requirement has the form
// requires constraint-expression;
//
// It can be used to specify additional constraints in terms of local parameters.
// The constraint-expression must be satisfied by the substituted template arguments, if any.
// Substitution of template arguments into a nested requirement causes substitution into the
// constraint-expression only to the extent needed to determine whether the constraint-expression
// is satisfied.
// template<class T>
// concept Semiregular = DefaultConstructible<T> &&
//     CopyConstructable<T> && CopyAssignable<T> && Destructible<T> &&
// requires(T a, std::size_t n)
// {
//     requires Same<T*, decltype(&a)>; // nested : "Same<...> evaluates to true"
//     {a.~T()} noexcept; // compound: "a.~T()" is valid expression that doesn't throw
//     requires Same<T*, decltype(new T)>; // nested: "Same<...> evaluates to true"
//     requires Same<T*, decltype<new T[n]>; // nested
//     { delete new T }; // compound
//     { delete new T[n]}; // compound
// };
//
// Note
// The keyword requires is also used to introduce requires clauses
template <typename T>
concept Addable = requires(T x) { x + x; }; // requires-expression

template <typename T>
    requires Addable<T> // requires-clause, not requires-expression
T add(T a, T b)
{
    return a + b;
}

template <typename T>
    requires requires(T x) { x + x; } // ad-hoc constraint, not keyword used twice
T add(T a, T b)
{
    return a + b;
}

int main()
{
    return 0;
}
// Constraints and concepts
// Class templates, function templates, and non-template functions (typically members
// of class templates) may be associated with a constraing, which specifies the requirements
// on template arguments, which can be used to select the most appropriate function overloads
// and template specializations.
// Named set of such requirements are called concepts. Each concept is a predicate, evaluated
// at compile time, and become a part of the interface of a template where it is used as a constraint

// Violations of constraints are detected at compile time, early in the template instantiation
// process, which leads to easy to follow error messages

// std::list<int> l = {3, -1, 10};
// std::sort(l.begin(), l.end());
// Typical compiler diagnostic without concepts:
// invalid operands to binary expressions ('std::_List_iterator<int>' and
// 'std::_List_iterator<int>')
//                           std::__lg(__last - __firts) * 2);
// ... 50 lines of output ...
//
// Typical compiler diagnostic with concepts:
// error : cannot call std::sort with std::_List_iterator<int>
// note : concept RandomAccessIterator<std::_List_iterator<int>> was not satisfied

// The intent of concepts is to model semantic categories (Number, Range, RegularFunction)
// rather than syntactic restrictions (HasPlus, Array). According to ISO C++ core guideline T.20,
// "The ability to specify meaninful semantics is a defining characteristic of a true concept,
// as opposed to a syntactic constraint".

// Concepts
// A concept is a named set of requirements. The definition of a concept must appear at namespace
// scope. The definition of a concept has the form :
//
// - template < template-parameter-list>
// - concept concept-name attr (optional) = constraint-expression;
// - attr - sequence of any number of attriutes

#include <type_traits>

template <class T, class U>
concept Derived = std::is_base_of<U, T>::value;

// Concepts cannot recursively refer to themselves and cannot be constrained:

// template<typename T>
// concept V = V<T*>; // error : recursive concept

// template<class T>
// concept C1 = true;
// template<C1 T>
// concept Error1 = true // Error : C1 T attempts to constrain a concept definition
// template<class T> requires C1<T>
// concept Error2 = true; // Error : the requires-clause attempts to constrain a concept

// Explicit instantiations, explicit specializations, or partial specializations of concepts are
// not allowed (the meaning of the original definition of a constraint cannot be changed)
// Concepts can be named in an id-expression. The value of the id-expression is true if the
// constraint expression is satisfied, and false otherwise.
//
// Concepts can also be named in a type-constraint, as part of
// - type template parameter declaration
// - placeholder type specifier
// - compound requirement
//
// In a type-constraint, a concept takes one less template argument than its parameter list demands,
// because the contextually deduced type is implicitly used as the first argument of the concept.

// TODO : Revisit this example, I didn't undestood what Base means
// template<class T, class U>
// concept Derived2 = std::is_base_of<U,T>::value;

// template<Derived2<Base> T>
// void f(T); // T is constrained by Derived<T, Base>

// Constraints
// A constraint is a sequence of logical operations and operands that specifies requirements
// on template arguments. They can appear within requires expressions or directly as bodies
// of concepts.
//
// There are three types of constraints:
// - conjunctions
// - disjunctions
// - atomic constraints
//
// The constraint associated with a declaration are determined by normalizing a logical AND
// expression whose operands are in the following order:
// - the constraint expression introduced for each constrained type template parameter or
//   non-type template paramter declared with a constrained placeholder type, in order of appearance
// - the constraint expression in the requires clause after the template parameter list
// - the constraint expression introduced for each parameter with constrained placeholder type in
//   an abbreviated function template declaration
// - the constraint expression in the trailing requires clause
//
// This order determines the order in which constraints are instantiated when checking for satisfaction.

// Redeclarations
// A constrained declaration may only be redeclared using the same syntactic form.
// No diagnostic is required:
// These first two declaration of f are fine
// template<Incrementable T>
// void f(T) requires Decrementable<T>;

// template<Incrementable T>
// void f(T) requires Decrementable<T>; // OK, redeclaration

// // Inclusion of this third, logically-equivalent-but-syntactically-different
// // declaration of f is ill-formed, no diagnostic required
// template<typename T>
//     requires Incrementable<T> && Decrementable<T>
// void f(T);

// // The following two declarations have different constraints:
// // the first declaration has In<crementable<T> && Decrementable<T>
// // the second declaration has Decrementable<T> && Incrementable<T>
// // Even though they are logically equivalent.
// template<Incrementable T>
// void g(T) requires Decrementable<T>;

// template<Decrementable T>
// void g(T) requires Incrementable<T>; // ill-formed, no diagnostic required

// Conjunctions
// The conjunction of two constraints is formed by using the && operator in the constraint expression:
template <class T>
concept Integral = std::is_integral<T>::value;
template <class T>
concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
template <class T>
concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

// A conjuction of two constraint is satisfied only if both constraints are satisfied.
// Conjunctions are evaluated left to right and short-circuited (if the left constraint
// is not satisfied, template argument substitution into the right constraint is not
// attempted: this prevents failures due to substitution outside of immediate context).
//
// template<typename T>
// constexpr bool get_value() { return T::value; }

// template<typename T>
//     requires (sizeof(T) > 1 && get_value<T>())
// void f(T); // #1

// void f(int); // #2

// void g()
// {
//     f('A'); // OK, calls #2. When checking the constraints of #1,
//             // 'sizeof(char) > 1' is not satisfied, so get_value<T>() is not checked
// }

// Disjunctions
// The disjunction of two constraints is formed by using the || operator in the constraint expression
// A disjunction of two constraints is satisfied if either constraint is satisfied. Disjunctions are
// evaluated left to right and short-circuited (if the left constraint is satisfied, template argument
// substitution into the right constraint is not attempeted).
//
// template<class T = void>
//     requires EqualityComparable<T> || Same<T, void>
// struct equal_to;

// Atomic constraints
// An atomic constraint consists of an expression E and a mapping from the template parameters that
// appear within E to template arguments involving the template parameters of the constrained entity,
// called is parameter mapping.
// Atomic constraints are formed during constraint normalization. E is never a logical AND or logical OR
// expression (those form conjunctions and disjunctions, respectively).
// Satisfaction of an atomic constraint is checked by substituting the parameter mapping and template
// arguments into the expression E. If the substitution results in a invalid type or expression,
// the constraint is not satisfied. Otherwise, E, after any lvalue-to-rvalue conversion, shall be a
// prvalue constant expression of type bool, and the constraint is satisfied if and only if it
// evaluates to true.
// The type of E after substitution must be exactly bool. No conversion is permitted:
//
// template<typename T>
// struct S
// {
//     constexpr operator bool() const {return true; }
// };

// template<typename T>
//     requires (S<T>{})
// void f(T); // #1

// void f(int);

// void g()
// {
//     f(0); // error S<int>{} does not have type bool when checking #1,
//           // even though #2 is a better match
// }
//
// Two atomic constraints are considered identical if they are formed from the same expression
// at the source level and their parameter mappings are equivalent.
//
// template<class T>
// constexpr bool is_meowable = true;

// template<class T>
// constexpr bool is_cat = true;

// template<class T>
// concept Meowable = is_meowable<T>;

// template<class T>
// concept BadMeowableCat = is_meowable<T> && is_cat<T>;

// template<class T>
// concept GoodMeowableCat = Meowable<T> && is_cat<T>;

// template<Meowable T>
// void f1(T); // #1

// template<BadMeowableCat T>
// void f1(T); // #2

// template<Meowable T>
// void f2(T); // #3

// template<GoodMeowableCat T>
// void f2(T); // #4

// void g()
// {
//     f1(0);  // error, ambiguous:
//             // the is_meowable<T> in Meowable and BadMeowableCat forms distincti atomic
//             // constraints that are not identical (and so do not subsume each other).
//     f2(0);  // OK, calls #4, more constrained than #3
//             // GoodMeowableCat got its is_meowable<T> from Meowable
// }
//
// Constraint normalization
// Constraint normalization is the process that transforms a constraint expression into a sequence
// of conjunctions and disjunctions of atomic constraints. The normal form of an expression is
// defined as follows:
// - The normal form of an expression (E) is the normal form of E
// - The normal form of an expression E1 && E2 is the conjunction of the normal forms of E1 and E2
// - The normal form of an expression E1 || E2 is the disjunction of the normal forms of E1 and E2
// - The normal form of an expression C<A1, A2, ..., AN>, where C names a concept, is the normal form
//   of the constraint expression of C, after substituting A1, A2, ... , AN for C's respective
//   template parameters in the parameter mappings of each atomic constraint of C. if any such
//   substitution into the paramter mappings results in an invalid type or expression, the program
//   is ill-formed, no diagnostic required.
//
template <typename T>
concept A = T::value || true;

template <typename U>
concept B = A<U *>; // OK : normalized to the disjunction of
                    // - T::value (with mapping T -> U*) and
                    // - true (with an empty mapping).
                    // No invalid type in mapping even though
                    // T::value is ill-formed for all pointer types
template <typename V>
concept C = B<V &>; // Normalizes to the disjunction of
                    // - T::value (with mapping T -> V&*) and
                    // - true (with an empty mapping).
                    // Invalid type V&* formed in mapping => ill-formed NDR
//
// - The normal form of any other expression E is the atomic constraint whose expression is E
//   and whose parameters mapping is the identity mapping. This includes all fold expressions,
//   even those folding over the && or || operators.
// User-defined overloads of && or || have no effect on constraint normalization.
//
// Requires clauses
// The keyword requires is used to introduce a requires-clause, which specifies constraints
// on template arguments or on a function declaration.
//
// template<typename T>
// void f(T&&) requires Eq<T>; // can appear as the last element of a function declarator

// template<typename T> requires Addable<T> // or right after a template parameter list
// T add(T a, T b) {return a + b; }
//
// In this case, the keyword requires must be followed by some constant expression (so it's possible
// to write requires true), but the intent is that a named concept (as in the example above) or a
// conjunction/disjunction of named concepts or a requires expression is used.
// The expression must have one of the following forms:
// - a primary expression, eg. Swappable<T>, std::is_integral<T>::value, (std::is_object_v<Args> && ...),
//   or any paranthesized expression.
// - a sequence of primary expressions joined with the operator &&
// - a sequence of aforementioned expressions joined with the operator ||
template <class T>
constexpr bool is_meowable = true;

template <class T>
constexpr bool is_purrable() { return true; }

template <class T>
void fa(T)
    requires is_meowable<T>; // OK

// template<class T>
// void g(T) requires is_purrable<T>(); // error, is_purrable<T>() is not a primary expression

template <class T>
void h(T)
    requires(is_purrable<T>()); // OK, paranthezied expression.
//
// Partial ordering of constraints
// Before any further analysis, constraints are normalized by substituting the body of every
// named concept and every requires expression until what is left is a sequence of conjunctions
// and disjunctions on atomic constraints.
// A constraint P is said to subsume constraint Q if it can be proven that P implies Q up to the
// identity of atomic constraints in P and Q. (Types and expressions are not analyzed for equivalnece:
// N > 0 does not subsume N >= 0).
// Specfically, first P is converted to disjunctive normal form and Q is converted to conjunctive normal form.
// P subsumes Q if and only if:
// - every disjunctive clause is the disjunctive normal form of P subsumes every conjunctive clause in the
//   conjunctive normal form of Q, where
// - a disjunctive clause subsumes a conjunctive clause if and only if there is an atomic constraint
//   U in the disjunctive clause and an atomic constraint V in the conjunctive clause such that
//   U subsumes V;
// - an atomic constraint A subsumes an atomic constraint B if and only if they are identical using
//   the rules described above.
//
// Subsumption relationship defines partial order of constraints, which is used to determine:
// - the best viable candidate for a non-template function in overload resolution
// - the address of a non-template function in an overload set
// - the best match for a template argument
// - partial ordering of class template specializations
// - partial ordering of function templates
//
// If declarations D1 and D2 are constrained and D1's associated constraints subsume D2's
// associated constraint (or if D2 is unconstrained), then D1 is said to be at least
// as constrained as D2, and D2 is not at least as constrained as D1, then D1 is more
// constrained than D2.

// template<typename T>
// concept Decrementable = requires(T t) { --t; };
// template<typename T>
// concept RevIterator = Decrementable<T> && requires(T t) { *t; };
// // RevIterator subsumes Decrementable, but not the other way around

// template<Decrementable T>
// void f(T); // #1

// template<RevIterator T>
// void f(T); // #2, mor constrained than #1

// f(0); // int only satisfies Decrementable, selects #1
// f((int *)0); // int* satisfies both constraints, select #2 as more constrained

// template<class T>
// void g(T); // #3 (unconstrained)

// template<Decrementable T>
// void g(T); // #4

// g(true); // bool does not satisfy Decrementable, selects #3
// g(0); // int satisfies Decrementable, selects #4 because it is more constrained

// template<typename T>
// concept RevIterator2 = requires(T t) { --t; *t; };

// template<Decrementable T>
// void h(T); // #5

// template<RevIterator2 T>
// void h(T); // #6

// h((int *)0); // ambiguous, Satisfies Decremental (pointer arithmetics) and --t; *t,
//              // the problem here is that since we don't have precedents the compiler would not
//              // know which one to choose.

// Working Example
#include <string>
#include <cstddef>
#include <concepts>
#include <iostream>

template <typename T>
concept Hashable = requires(T a) {
    {
        std::hash<T>{}(a)
    } -> std::convertible_to<std::size_t>;
};

struct meow
{
};

// template<Hashable T>
// void f(T) {
//     std::cout << "Calling f(T)" << std::endl;
// };

// Alternative ways to apply the same constraint:
// template<typename T>
//    requires Hashable<T>
// void f(T) {}
//
// template<typename T>
// void f(T) requires Hashable<T> {}
//
// void f(Hashable auto /*parameterName*/) {}

void f(Hashable auto a)
{
    std::cout << "Calling f(T)" << std::endl;
};

// Testing if type is arithmetic
template <typename T>
concept Is_Number = std::is_arithmetic<T>::value;

void addTen(Is_Number auto a)
{
    a += 10;
    std::cout << "Adding 10 : " << a << std::endl;
};
// or alternative require usage
template <Is_Number T>
void addTen2(T a)
{
    a += 10;
    std::cout << "Adding 10 function 2 : " << a << std::endl;
};

struct non_arithmetical
{
};

struct fakeMath
{
    fakeMath &operator+(int i)
    {
        std::cout << "I'm a liar, I have no idea what I'm doing!" << std::endl;
        std::cout << "Here is what you are adding anyway : " << i << std::endl;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &, fakeMath &);
};

std::ostream &operator<<(std::ostream &os, fakeMath &f)
{
    os << "I can do math";
    return os;
}

// This is a terrible example, however it illustrates how requires works,
// it doesn't evaluate the result, only if the expression is valid.
template<typename T>
concept Can_Add = requires (T t) {
    t + 1;
};

void doSomeMath(Can_Add auto a, Can_Add auto b) {
    a + b;
};

int main()
{
    using std::operator""s;

    f("abc"s); // OK, std::string satisfies Hashable
    // f(meow{}); // Error, meow does not satisfy Hashable

    addTen(2);
    addTen('a'); // Ok, char is arithmetic, 'a' + 10 = 'k'

    // Error, non_arithmetic is not arithmetic
    // note: constraints not satisfied
    // addTen(non_arithmetical());

    // addTen((int*)0); // pointers arithmetic is not valid here, see std::is_arithmetic

    doSomeMath(fakeMath(),7);
    doSomeMath(10, 2);

    // doSomeMath(non_arithmetical()); // Error, can't do math

    addTen2(3);

    return 0;
}
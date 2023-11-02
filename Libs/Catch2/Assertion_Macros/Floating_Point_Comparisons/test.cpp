// Comparing floating point number with Catch2
//
// If you are not deeply familiar with them, floating point numbers can be unintuitive.
// This also applies to comparing floating point numbers for (in)equality.
//
// Floating point matchers
//
// #include <catch2/matchers/catch_matchers_floating_point.hpp>
//
// Matchers are the preferred way of comparing floating point numbers in Catch2.
// We provide 3 of them:
// - WithinAbs(double target, double margin)
// - WithinRel(FloatingPoint target, FloatingPoint eps)
// - WithinULP(FloatingPoint target, uint64_t maxUlpDiff)
//
// As with all matchers, you can combine multiple floating point matchers in a single assertion.
// For example, to check that some computation matches a known good value within 0.1% or is
// close enough (no different to 5 decimal places) to zero, we would write this assertion:
//
// REQUIRE_THAT(  computation(input),
//                Catch::Matchers::WithinRel(expected, 0.001)
//             || Catch::Matchers::WithinAbs(0, 0.000001) );
//
// WithinAbs
// WithinAbs creates a matcher that accepts floating point numbers whose difference with target
// is less-or-equal to the margin. Since float can be converted to double without losing precision,
// only double overload exists.
//
// REQUIRE_THAT(1.0, WithinAbs(1.2, 0.2));
// REQUIRE_THAT(0.f, !WithAbs(1.0, 0.5));
// // Notice that infinity == infinity for WithinAbs
// REQUIRE_THAT(INFINITY, WithinAbs(INFINITY, 0));
//
// WithinRel
// WithinRel creates a matcher that accepts floating point numbers that are approximately equal
// to the target with a tolerance of eps.
// Specifically, it matches if |arg - target| <= eps * max(|arg|, |target|) holds. If you do not
// specify eps, std::numeric_limits<FloatingPoint>::epsilon * 100 is used as the default
//
// // Notice that WithinRel comparison is symmetric, unlike Approx's
// REQUIRE_THAT(1.0, WithinRel(1.1, 0.1));
// REQUIRE_THAT(1.1, WithinRel(1.0, 0.1));
// // Notice that infinity == infinity for WithinRel
// REQUIRE_THAT(INFINITY, WithinRel(INFINITY));
//
// WithinULP
// WithinUlp creates a matcher that accepts floating point numbers that are no more than maxUlpDiff
// ULPs away from the target value. The short version of what this means is that there is no more
// than maxUlpDiff - 1 representable floating point numbers between the argument for matchin and
// the target value.
//
// Whenn using ULP matcher in Catch2, it is important to keep in mind that Catch2 interprets ULP
// distance slightly differently than e.g. std::nextafter does.
//
// Catch2's ULP calculation obeys these relations:
// - ulpDistance(-x, x) == 2 * ulpDistance(x,0)
// - ulpDistance(-0, 0) == 0 (due to the above)
// - ulpDistance(DBL_MAX, INFINITY) == 1
// - ulpDistance(NaN, x) == infinity
//
// Important: The WithinULP matcher requires the platform to use the IEEE-754 representation for
//            floating point numbers.
//
// REQUIRE_THAT(-0.f, WithinULP( 0.f, 0));
//
// ULP definition
//  Unit in the last place or unit of least precision (ulp) is the spacing between two consecuitives
// floating point numbers, i.e. the value the least significant digit (rightmost digit) represents
// if it is 1.
//
// Approx
//
// #include <catch2/catch_approx.hpp>
//
// We strongly recommend against using Approx when writting new code. You should be using floating
// point matchers instead.
//
// Catch2 provides one more way to handle floating point comparisons. It is Approx, a special type
// with overloaded comparison operators, that can be used in standard assertions, e.g.
//
// REQUIRE(0.999999 == Catch::Approx(1));
//
// Approx supports four comparisons operators, ==, !=, <=, >=, and can also be used with strong
// typedefs over doubles. It can be used for both relative and margin comparisons by using its
// three customization points. Note that the semantics of this is always that of an or, so if
// either the relative or absolute margin comparison passes, then the whole comparison passes.
//
// The downside to Approx is that it has a couple of issues that we cannot fix without breaking
// backward compatibility. Because Catch2 also provides complete set of matchers that implement
// different floating point comparison methods, Approx is left as-is, is considered deprecated,
// ans should not be used in new code.
//
// The issues are
// - All internal computation is done in doubles, leading to slightly different results if the
//   inputs were floats.
// - Approx's relative margin comparison is not symmetrical. This means that
//   Approx(10).epsilon(0.1) != 1.1 but Approx(11.1).epsilon(0.1) == 10.
// - By default, Approx only uses relative margin comparison. This means that
//   Approx(0) == X only passes for X == 0.

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Floating Point Comparison - WithinAbs", "[FloatingPoint]")
{
    // WithinAbs(1.2, 0.2) -> 1.0 <= target <= 1.4
    REQUIRE_THAT(1.0, Catch::Matchers::WithinAbs(1.2, 0.2));
    // WithinAbs(1.0, 0.5) -> 0.5 <= target <= 1.5
    REQUIRE_THAT(0.f, !Catch::Matchers::WithinAbs(1.0, 0.5));
    // WithinAbs(1.0, 0.01) -> 0.99 <= target <= 1.01
    REQUIRE_THAT(0.99f, Catch::Matchers::WithinAbs(1.0, 0.01));
    REQUIRE_THAT(1.01f, Catch::Matchers::WithinAbs(1.0, 0.01));
    REQUIRE_THAT(1.02f, !Catch::Matchers::WithinAbs(1.0, 0.01));
};

TEST_CASE("Floating Point Comparison - WithinRel", "[FloatingPoint]")
{
    // |arg - target| <= eps * mac(|arg|, |target|)
    // WithinRel(1.1, 0.1) ->
    // |1.1 - 1.0| <= 0.1 * max(|1.1|, |1.0|)
    //  0.1 <= 0.1 * 1.1
    // 0.1 <= 0.11 ==> true
    REQUIRE_THAT(1.0, Catch::Matchers::WithinRel(1.1, 0.1));
    // |1.0 - 1.1| <= 0.1 * max(|1.0|, |1.1|)
    // 0.1 <= 0.1 * 1.1
    // 0.1 <= 0.11 ==> true
    REQUIRE_THAT(1.1, Catch::Matchers::WithinRel(1.0, 0.1));
    // |1.0 - 1.2| <= 0.1 * max(|1.0|, |1,2|)
    // 0.2 <= 0.1 * 1.2
    // 0.2 <= 0.12 ==> false
    REQUIRE_THAT(1.2, !Catch::Matchers::WithinRel(1.0, 0.1));
};

// TODO : I couldn't understand how WithinULP works, I understand ULP and a little bit
//        of how it's calculated, but couldn't apply here.
//        Leaving this here for the future.
TEST_CASE("Floating Point Comparison - WithinULP", "[FloatingPoint]")
{
    REQUIRE_THAT(-0.f, Catch::Matchers::WithinULP(0.f, 0));
};

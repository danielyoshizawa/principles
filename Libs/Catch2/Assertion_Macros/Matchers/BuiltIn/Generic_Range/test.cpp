// Generic Range Matchers
//
// Generic range matchers were introduced in Catch2 3.0.1
//
// Catch2 also provides some matchers that use the new style matchers definitions to handle generic
// range-like types. These are:
// - IsEmpty()
// - SizeIs(size_t target_size)
// - SizeIs(Matcher size_matcher)
// - Contains(T && target_element, Comparator = std::equal_to<>)
// - Contains(Matcher element_matcher)
// - AllMatch(Matcher element_matcher)
// - AnyMatch(Matcher element_matcher)
// - NoneMatch(Matcher element_matcher)
// - AllTrue(), AnyTrue(), NoneTrue()
// - RangeEquals(TargetRangeLike&&, Comparator = std::equal_to<>)
// - UnorderedRangeEquals(TargetRangeLike&&, Comparator = std::equal_to<>)
//
// IsEmpty, SizeIs, Contains were introduced in Catch2 3.0.1
// All/Any/NoneMatch were introduced in Catch2 3.0.1
// All/Any/NoneTrue were introduced in Catch2 3.1.0
// RangeEquals and UnorderedRangeEquals matchers were introduced in Catch 3.3.0
//
// IsEmpty should be self-explanatory. It successfully matches objects that are empty according
// to either std::empty, or ADL-found empty free function.
//
// The IsEmpty matcher lives in catch2/matchers/catch_matchers_container_properties.hpp
//
// SizeIs checks range's size. If constructed with size_t arg, the matchers accpets ranges whose
// size is exactly equal to the arg. If constructed from another matcher, then the resulting matcher
// accepts ranges whose size is accepted by the provided matcher.
//
// The SizeIs matcher lives in catch2/matchers/catch_matchers_container_properties.hpp
//
// Contains accepts ranges that contain specific element. There are again two variants, one that
// accepts the desired element directly, in which case a range is accepted if any of its elements
// is equal to the target element. The other variant is contructed from a matcher, in which case a
// range is accepted if any of its elements is accepted by the provided matcher.
//
// The Contains matcher lives in catch2/matchers/catch_matchers_contains.hpp
//
// AllMatch, NoneMatch, and AnyMatch match ranges for which either all, none or any of the contained
// elements matches the given matcher, respectively
//
// AllTrue, NoneTrue, and AnyTrue match ranges from which either all, none, or any of the contained
// elements are true, respectively. It works for ranges of bools and ranges of elements (explicitly)
// convertible to bool
//
// The All/None/Any Match and True matchers lives in catch2/matchers/catch_matchers_quantifiers.hpp
//
// RangeEquals compares the range that the matcher is constructed with (the "target range") against
// the range to be tested, element-wise. The match succeeds if all elements from the two ranges
// compare equal(using operator== by default).The range do not need to be the same type, and the
// element types do not need to be the same, as long as they are comparable. (e.g. you may compare
// std::vector<int> to std::array<char>).
//
// UnorderedRangeEquals is similar to RangeEquals, but the order does not matter. For example
// "1,2,3" would match "3,2,1", but not "1,1,2,3" as with RangeEquals, UnorderedRangeEquals
// compares the individual elements using operator=== by default.
//
// Both RangeEquals and UnorderedRangeEquals optionally accept a predicate which can be used to
// compare the containers element-wise.
//
// To check a container elementwise agains a given matcher, use AllMatch
//
// The RangeEquals and UnorderdRangeEquals matchers lives in
// catch2/matchers/catch_matchers_container_range_equals.hpp

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp> // IsEmpty, SizeIs
#include <catch2/matchers/catch_matchers_contains.hpp>             // Contains
#include <catch2/matchers/catch_matchers_quantifiers.hpp>          // All/None/Any Match | True
#include <catch2/matchers/catch_matchers_range_equals.hpp>         // RangeEquals, UnorderedRangeEquals
#include <catch2/matchers/catch_matchers_string.hpp>               // String matchers - Not Generic, it will be used as matcher combinator
#include <vector>
#include <string>

TEST_CASE("Container Properties - IsEmpty | SizeIs", "[GenericRange]")
{
    std::vector<int> vEmpty{};
    std::vector<int> vSize{1, 2, 3};

    SECTION("IsEmpty")
    {
        REQUIRE_THAT(vEmpty, Catch::Matchers::IsEmpty());
    }

    SECTION("SizeIs")
    {
        std::size_t expectedSize{3};
        REQUIRE_THAT(vSize, Catch::Matchers::SizeIs(expectedSize));
    }
};

TEST_CASE("Contains", "[GenericRange]")
{
    std::vector<std::string> vContains{"alpha", "beta", "gamma", "omega"};

    SECTION("Contains")
    {
        REQUIRE_THAT(vContains, Catch::Matchers::Contains("beta")); // Default comparator
    }

    SECTION("Contains Matcher")
    {
        REQUIRE_THAT(vContains, Catch::Matchers::Contains(
                                    Catch::Matchers::StartsWith("om") &&
                                    Catch::Matchers::EndsWith("ga")));
    }
};
TEST_CASE("Quantifiers - All|None|Any Match|True", "[GenericRange]")
{
    std::vector<std::string> vQuantifiers{"alpha", "beta", "gamma", "omega"};
    SECTION("All|None|Any Match")
    {
        REQUIRE_THAT(vQuantifiers, Catch::Matchers::AllMatch(
                                       Catch::Matchers::ContainsSubstring("a")));
        REQUIRE_THAT(vQuantifiers, Catch::Matchers::NoneMatch(
                                       Catch::Matchers::StartsWith("del")));
        REQUIRE_THAT(vQuantifiers, Catch::Matchers::AnyMatch(
                                       Catch::Matchers::EndsWith("mma")));
    }

    std::vector<bool> vAllTrue{true, true};
    std::vector<bool> vNoneTrue{false, false, false};
    std::vector<bool> vBooleans{false, true, false, false};
    SECTION("All|None|Any True")
    {
        REQUIRE_THAT(vAllTrue, Catch::Matchers::AllTrue());
        REQUIRE_THAT(vNoneTrue, Catch::Matchers::NoneTrue());
        REQUIRE_THAT(vBooleans, Catch::Matchers::AnyTrue());
    }
};
TEST_CASE("Range - RangeEquals | UnorderedRangeEquals", "[GenericRange]")
{
    std::vector<std::string> vRange{"alpha", "beta", "gamma", "omega"};
    SECTION("RangeEquals")
    {
        REQUIRE_THAT(vRange,
                     Catch::Matchers::RangeEquals(
                         std::vector<std::string>{"alpha", "beta", "gamma", "omega"}));
        REQUIRE_THAT(vRange,
                     !Catch::Matchers::RangeEquals(
                         std::vector<std::string>{"alpha", "alpha", "beta", "gamma", "omega"}));
    }

    SECTION("UnorderedRangeEquals")
    {
        REQUIRE_THAT(vRange,
                     Catch::Matchers::UnorderedRangeEquals(
                         std::vector<std::string>{"beta", "alpha", "omega", "gamma"}));
        REQUIRE_THAT(vRange,
                     !Catch::Matchers::UnorderedRangeEquals(
                         std::vector<std::string>{"beta", "alpha", "omega", "gamma", "alpha"}));
    }
};
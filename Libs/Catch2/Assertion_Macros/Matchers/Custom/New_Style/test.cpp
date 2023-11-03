// Writting custom matchers (new style)
//
// New style matcher were introduced in Catch2 3.0.1
//
// To create a new-style matcher, you have to create your own type that derives from
// Catch::Matchers::MatcherGenericBase. Your type has to also provide two methods,
// bool match(...) const and overridden std::string describe() const.
//
// Unlike with old-style matchers, there are no requirements on how to match member
// function takes its arguments.This means that the argument can be taken by value or
// by mutating reference, but also that the matcher's match member function can be templated.
//
// This allows you to write more complex matcher, such as a matcher that can compare on range-like
// (something that responds to begin and end) object to another, like in the following example:

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include <array>
#include <vector>
#include <list>

template <typename Range>
struct EqualsRangeMatcher : Catch::Matchers::MatcherGenericBase
{
    EqualsRangeMatcher(Range const &range) : range{range} {}

    template <typename OtherRange>
    bool match(OtherRange const &other) const
    {
        using std::begin;
        using std::end;

        return std::equal(begin(range), end(range), begin(other), end(other));
    }

    std::string describe() const override
    {
        return "Equals: " + Catch::rangeToString(range);
    }

private:
    Range const &range;
};

template <typename Range>
auto EqualsRange(const Range &range) -> EqualsRangeMatcher<Range>
{
    return {range};
};

TEST_CASE("Combining templated matchers", "[matchers][templated]")
{
    std::array<int, 3> container{{
        1,
        2,
        3,
    }};
    std::array<int, 3> a{{1, 2, 3}};
    std::vector<int> b{0, 1, 2};
    std::list<int> c{4, 5, 6};

    REQUIRE_THAT(container, EqualsRange(a) || EqualsRange(b) || EqualsRange(c));
}

// Do note that while you can rewrite any matcher from the old style to a new style matcher,
// combining new style matchers in more expensive in terms of compilation time.
// Also note that you can combine old style and new style matchers arbitrarily.
//
// MatcherGenericBase lives in catch2/matchers/catch_matchers_templated.hpp
// Writing custom matchers (old style)
// The old style of writing matchers has been introduced back in Catch Classic.
// To create an old-style matcher, you have to create your ouw type that derives
// from Catch::Matchers::MatcherBase<ArgT>, where ArgT is the type your matcher
// works for. Your type has to override two methods, bool match(ArgT const&),
// and std::string describe() const.
//
// As the name suggests, match decides whether the provided argument is matched (accepted)
// by the matcher. describe then provides a human-oriented description og what that macher does.
//
// We also recommend that you create factory function, just like Catch2 does, but that is
// mostly useful for template argument deduction for templated matchers (assuming you do not
// have CTAD available).
//
// To combine these into an example, let's say that you want to write a matcher that decides
// whether the provided argument is a number within certain range.
// We will call it IsBetweenMatchers<T>:
//
// Example from Catch2 documentation, I'll not put much effort on it since this style is not
// used anymore.
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <sstream>
#include <string>

template <typename T>
class IsBetweenMatcher : public Catch::Matchers::MatcherBase<T>
{
    T m_begin, m_end;

public:
    IsBetweenMatcher(T begin, T end) : m_begin(begin), m_end(end) {}

    bool match(T const &in) const override
    {
        return in >= m_begin && in <= m_end;
    }

    std::string describe() const override
    {
        std::ostringstream ss;
        ss << "is between " << m_begin << " and " << m_end;
        return ss.str();
    }
};

template <typename T>
IsBetweenMatcher<T> IsBetween(T begin, T end)
{
    return {begin, end};
}

TEST_CASE("Numbers are within range")
{
    // infers `double` for the argument type of the matcher
    CHECK_THAT(3., IsBetween(1., 10.));
    // infers `int` for the argument type of the matcher
    CHECK_THAT(100, IsBetween(1, 100));
}

// Obviously, the code above can be improved somewhat, for example you might want to static_assert
// over the fact that T is an arithmetic type... or generalize the matcher to cover any type for
// which the user can provide a comparison function object.
//
// Note that while any matcher written using the old style can also be written using the new style,
// combining old style matchers should generally compile faster. Also note that you can combine
// old and new style matchers arbitrarily.
//
// MatcherBase lives in catch2/matchers/catch_matchers.hpp

// Vector Matchers (DEPRECATED)
// Vector matchers have been deprecated in favour of the generic range
// matchers with the same functionality.
//
// Catch2 provides 5 built-in matchers that work on std::vector
// These are:
// - Contains : which checks whether a specified vector is present in the result
// - VectorContains : which checks whether a specified element is present in the result
// - Equals : which checks whether the result is exactly equal (order matters) to a specific vector
// - UnorderedEquals : which checks whether the result is equal to a specific vector under a permutation
// - Approx : which checks whether the result is "approx-equal" (order matters, but comparison is done
//            via Approx) to a specific vector
//
// An example usage:
// std::vector<int> some_vec{1 ,2 ,3};
// REQUIRE_THAT(some_vec, Catch::Matchers::UnorderedEquals(std::vector<int>{ 3, 2, 1}));
//
// This assertions will pass, because the elements given to the matchers are a permutation of the
// ones in some_vec.
//
// Vector matchers live in catch2/matchers/catch_matchers_vector.hpp
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

TEST_CASE("This on is deprecated so I will not extend it much", "[vector]") {
    std::vector<int> some_vec{1 ,2 ,3};
    REQUIRE_THAT(some_vec, Catch::Matchers::UnorderedEquals(std::vector<int>{ 3, 2, 1}));
};
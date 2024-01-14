// Problem : Check Permutation
// Description : Given two strings, write a method to decide if one is a permutation
//               of the other.
//
// Walking through a problem
// 1 - Listen - Pay very close attention to any information in the problem description.
//              You probably need it all for an optimal algorithm
// 2 - Example - Most examples are too small or are special cases, Debug your example.
//               Is there any way it's a special case? Is it big enough?
// 3 - Brute Force - Get a brute force solution as soon as possible. Don't worry about
//                   developing an efficient algorithm yet. State a naive algorithm and
//                   its runtime, then optimize from there. Don't code yet though!
// 4 - Optimize - Walk through your brute force with BUD Optimization or try some of these ideas:
//                - Look for any unused info. You usually need all the information in a problem.
//                - Solve it manually on an example, then reverse engineer your thought process.
//                  How did you solve it?
//                - Solve it "incorrectly" and then think about why the algorithm fails. Can you
//                  fix those issues?
//                - Make a time vs. space tradeoff. Hash tables are especially usefull!
// 5 - Walk Through - Now that you have an optimal solution, walk through your approach in details.
//                    Make sure you understand each detail before you start coding.
// 6 - Implement - Your goal is to write beautiful code. Modularize your code from the beginning
//                 and refactor to clean up anything that isn't beautiful.
// 7 - Test - Test in this order:
//            - Conceptual test. Walk through your code like you you would for a detailed code review.
//            - Unusual or non-standard code.
//            - Hot spots, like arithmetic and null nodes.
//            - Small test cases. It's much faster than a big test case and just as effective.
//            - Special cases and edge cases.
//            And when you find bugs, fix them carefully!
//
// BUD Optimization
// Bottlenecks
// Unnecessary Work
// Duplicated Work
//
// Walking
// 1- Reading the problem statement, we need to check if all characters of the second set
//    are contained in the first, this means, that both strings must have the same size.
//
// 2 - "tornado" -> "randoto" => true
//     "the cake is a lie" -> "the lie is a cake" => true
//     "Playing with fire" -> "along the line" => false
//     "We don't know about the bird" -> "we don't know about" => false
//
// 3 - Brute force algorithm
//     1. Check if second.length == first.length
//     1.1 If not, return false, they don't have the same size and cant be a permutation
//     2. Get the first character of first
//     3. Compare to all others in second
//     4. If not found any equivalent, return false
//     4.1 If found, remove from second and continue
//     5. Get n+1 character in first
//     6. Return to step 3
//     7. Return true, all elements were matched
//
//     Brute force using "tornado" and "randoto"
//     1. "tornado".length == "randoto".lentgh -> 7 == 7 -> true
//     2. letter : t
//     3. t != r | t != a | t != n | t != d | t != o | t == t
//     4.1 second : "randoo"
//     5. letter : o
//     3. o != r | o != a | o != n | o != d | o == o
//     4.1 second : "rando"
//     5. letter : r
//     3. r == r
//     4.1 second : "ando"
//     5. letter : n
//     3. n != a | n == n
//     4.1 second : "ado"
//     5. letter : a
//     3. a == a
//     4.1 second : "do"
//     5. letter : d
//     3. d == d
//     4.1 second : "o"
//     5. letter : o
//     3. o == o
//     4.1 second : ""
//     7. Return true, all elements were matched.
//
//     Complexity : O(n^2)
//
// 4 - As a possible optimization I'd trade time to space, set a map of <char, int>
//     and increment if the letter is present in the firts word and decrement
//     if the letter is in the second, this way, in the end if the sum of all values
//     is zero, we know that we have a permutation. This method will not allow to
//     break before the end of the loop, but I believe that it's not possible anyway.
//     The complexity in this case would be O(N) + O(N), or O(2N), deducing the smallest
//     will leave us with O(N)
//
//     Optimized algorithm:
//     1. Check if they have the same size
//     1.1 If not, return false
//     2. Loop through first
//     3. Get the n letter of first
//     4. Get the n letter of second
//     5. Add 1 to the value of the map using the first letter as the key
//     6. Subtract 1 to the value of the map using the second letter as the key
//     7. Check if any value in the map is different of zero
//     7.1 If so, return false
//     7.2 If not, return true
//
//     Testing using "tornado" and "randoto"
//     1. "tornado".lenght == 7 && "randoto".lenght == 7
//     3. letter_first : t
//     4. letter_second : r
//     5. map : {t, 1}
//     6. map : {t, 1} , {r, -1}
//     3. letter_first : o
//     4. letter_second : a
//     5. map : {t, 1} , {r, -1} , {o, 1}
//     6. map : {t, 1} , {r, -1} , {o, 1} , {a, -1}
//     3. letter_first : r
//     4. letter_second : n
//     5. map : {t, 1} , {r, 0} , {o, 1} , {a, -1}
//     6. map : {t, 1} , {r, 0} , {o, 1} , {a, -1} , {n, -1}
//     3. letter_first : n
//     4. letter_second : d
//     5. map : {t, 1} , {r, 0} , {o, 1} , {a, -1} , {n, 0}
//     6. map : {t, 1} , {r, 0} , {o, 1} , {a, -1} , {n, 0} , {d, -1}
//     3. letter_first : a
//     4. letter_second : o
//     5. map : {t, 1} , {r, 0} , {o, 1} , {a, 0} , {n, 0} , {d, -1}
//     6. map : {t, 1} , {r, 0} , {o, 0} , {a, 0} , {n, 0} , {d, -1}
//     3. letter_first : d
//     4. letter_second : t
//     5. map : {t, 1} , {r, 0} , {o, 0} , {a, 0} , {n, 0} , {d, 0}
//     6. map : {t, 0} , {r, 0} , {o, 0} , {a, 0} , {n, 0} , {d, 0}
//     3. letter_first : o
//     4. letter_second : o
//     5. map : {t, 0} , {r, 0} , {o, 1} , {a, 0} , {n, 0} , {d, 0}
//     6. map : {t, 0} , {r, 0} , {o, 0} , {a, 0} , {n, 0} , {d, 0}
//     7. Check if any is different of zero {t, 0} , {r, 0} , {o, 0} , {a, 0} , {n, 0} , {d, 0}
//     8. Return true
//
//     5 - I think that this is a good solution, O(N) time complexity, not worried about space
//         at this moment, the steps are clear and I can't see any problems with it.
//
//     6 - Implementation below
//
//     7 - Conceptual test.
//         Looks fine
//       - Unusual or non-standard code.
//         Nothing out of the ordinary
//       - Hot spots, like arithmetic and null nodes.
//         Shouldn't have any problems
//       - Small test cases.
//         Done
//       - Special cases and edge cases.
//         Empty strings, one and two, whitespaces, covered

#include <iostream>
#include <string>
#include <map>
#include <numeric>
#include <vector>

bool is_permutation(const std::string &first, const std::string &second)
{
    if (first.length() != second.length())
    {
        return false;
    }

    std::map<char, int> occurrency;
    for (int i = 0; i < first.length(); ++i)
    {
        occurrency[first[i]]++;
        occurrency[second[i]]--;
    }

    for (auto o : occurrency)
    {
        if (o.second != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::vector<std::string> firsts {"tornado", "the cake is a lie", "Playing with fire", "We don't know about the bird", "testingsamelenght", "", "a", "a", "ab"};
    std::vector<std::string> seconds {"randoto", "the lie is a cake", "along the line", "we don't know about", "notthesamewordsyy", "", "a" , "b", "ba"};

    for (int i = 0; i < firsts.size(); ++i) {
        std::cout << "Is \"" << seconds[i] << "\" a permutation of \"" << firsts[i] << "\" ? " << std::boolalpha << is_permutation(firsts[i], seconds[i]) << std::endl;
    }
    return 0;
}

// Problem : One way
// Description : There are three types of edits that can be performed on strings: insert,
//               a character, remove a character, or replace a character. Given two strings,
//               write a function to check if they are one edit (or zero edits) away.
//
// Example:
//  pale, ple -> true
//  pales, pale -> true
//  pale, bale -> true
//  pale, bake -> false
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
// 1 - The exercise states that are 3 types of edits, which will leave us with 4 acceptable
//     scenarions, add, remove, replace and nothing, add and remove would be the same but in the
//     opposite direction, meaning, if we have two strings a and b, if we add one character to b
//     is the same as if we had removed one from a, e.g. "abc" -> "abcd", equals to, "abcd" -> "abc".
//     We can use it in our favor, to figure out the solution, the case of replacement, how can
//     we express it in the same terms, we could say that a replace is an removal followed by and
//     addition, e.g. "abc" -> "ac" -> "adc", that would be 2 operations, which might be a problem.
//     We may need to figure out a different approach, we can count the differences between both,
//     if we have 1 character difference, we have an addition or removal, if we have 2, one per side
//     we have a replacement, how can we enforce this?
//
// 2 - pale, ple -> true
//   - pales, pale -> true
//   - pale, pales -> true
//   - pale, palle -> true
//   - pale, bale -> true
//   - pale, bake -> false
//   - pale, pale -> true
//   - pale, ble -> false
//   - pale, bales -> false
//
// Test the biggest among the 2 words, this way we remove the removal case,
// Use the concept of hit or miss, we can have max 1 miss
// Need to use 2 carries, one for each word, they may not have the same size
// If the size changes, it must have an addition or removal,
// so in this case, if we already have a miss, we sure have more than one
//
// 3 - Brute force algorithm
//     1. Define the bigger and smaller words
//     2. Check if the sizes matches
//     2.1 If so, we must check for replacement
//     2.1.1 Compare elements
//     2.1.1.1 If doesnt match, check if miss is true
//     2.1.1.1.1 If miss is already set, return false
//     2.1.1.1.2 If not set miss true
//     2.2 If not, check if sizes are at most 1 in difference, addition
//     2.2.1 Compare elements
//     2.2.1.1 If doesn't match
//     2.2.1.1.1 check if miss is true
//     2.2.1.1.1.1 if miss is already set, return false
//     2.2.1.1.1.2 if not, set miss to true
//     2.2.1.1.2 If it matches and m < smaller.size() - 1
//     2.2.1.1.2.1 m++
//     2.2.1.1.2.2 If m >= smaller.size() - 1 (2.2.1.1.2 Else)
//     2.2.1.1.2.2.1 Check miss
//     2.2.1.1.2.2.1.1 if so, return false
//     2.2.1.1.2.2.1.2 if not, return true
//     2.3 If not, Return false (2.2 Else)
//     3. Return True
//
//     Complexity O(N)
//
//     Here we have 2 loops, however only one will run per input, optimizations
//     will be done in the next step.
//
//     Testing algorithm with pales -> pale
//     1. bigger : pales | smaller : pale
//     2. pales.size() > smaller.size()
//     2.2 pales.size() == smaller.size() + 1
//     2.2.1 p == p
//     2.2.1.1.2 m : 1
//     2.2.1 a == a
//     2.2.1.1.2 m : 2
//     2.2.1 a == l
//     2.2.1.1.2 m : 3
//     2.2.1 a == l
//     2.2.1.1.2 m >= smaller.size() - 1
//     2.2.1.1.2.2.1.2 if not, return true
//
//     Testing algorithm with pal -> al
//     1. bigger : pal | smaller : al
//     2. pal.size() > smaller.size()
//     2.2 pla.size() == smaller.size() + 1
//     2.2.1 p != a
//     2.2.1.1.1.2 miss == false | miss = true
//     2.2.1 a != a
//     2.2.1.1.2.1 m++ | m : 1
//     2.2.1 l != l
//     3. return true
//      
// 4 - Got to a brute force kind of solution, with a lot of redundance and complexity
//     Let's see if we can improve it.
//
//     Breaking it down
//     1. Define the bigger and smaller words
//     2. Check if the sizes matches (Does it really matter?)
//     - Argument on 2, if I check if m == smaller.size() - 1 and miss == false at the
//       begining of the loop I can return false if miss was already set, because
//       in this case, the last character will always be an insertion
//
//     2.1 If so, we must check for replacement (Can be eliminated)
//
//     2.1.1 Compare elements (Repeated 2.2.1)
//     2.1.1.1 If doesnt match, check if miss is true (Repeated)
//     2.1.1.1.1 If miss is already set, return false (Repeated)
//     2.1.1.1.2 If not set miss true (Repeated)
//
//     2.2 If not, check if sizes are at most 1 in difference, addition (Move to the begin)
//
//     2.2.1 Compare elements (Repeated 2.1.1)
//     2.2.1.1 If doesn't match (Repeated)
//     2.2.1.1.1 check if miss is true (Repeated)
//     2.2.1.1.1.1 if miss is already set, return false (Repeated)
//     2.2.1.1.1.2 if not, set miss to true (Repeated)
//
//     2.2.1.1.2 If it matches and m < smaller.size() - 1 (This is for any case)
//     2.2.1.1.2.1 m++
//     2.2.1.1.2.2 If m >= smaller.size() - 1 (2.2.1.1.2 Else) (Move this to the begin of loop)
//
//     2.2.1.1.2.2.1 Check miss (Repeated again)
//     2.2.1.1.2.2.1.1 if so, return false
//     2.2.1.1.2.2.1.2 if not, return true (Irrelevant, it will return in the end anyway)
//
//     2.3 If not, Return false (2.2 Else)
//     3. Return True
//
//     Improvement
//     1. Define the bigger and smaller words
//     2. Check if bigger.size() >= smaller.size() + 2, if so, return false
//     3. Loop through the bigger word (bigger position : n, smaller position : m)
//     4. Check if m <= smaller.size() - 1
//     4.1 If not, check for miss
//     4.1.1 if miss is already set, return false
//     5. Compare elements
//     5.1 if doesn't match, check for miss
//     5.1.1 if miss is already set, return false
//     5.1.2 else miss = true
//     5.1.2.1 if bigger.size() != smaller.size(), --m (will not move smaller now)
//     6. n++,m++, return to 4
//     7. return true
//
//     Let test with bake -> cake
//     3. n : 0, m : 0
//     4. 0 <= 3 -> true
//     5. b != c
//     5.1.2 miss = true, m : -1
//     6. n : 1, m: 1
//     4. 1 <= 3 -> true
//     5. a == a
//     6. n : 2, m : 2
//     4. 2 <= 3 -> true
//     5. k == k
//     6. n : 3, m : 3
//     4. 3 <= 3 -> true
//     5. e == e
//     6. n : 4, m :4
//     7. return true
//
//     Let test with baker -> bake
//     3. n : 0, m : 0
//     4. 0 <= 3 -> true
//     5. b == b
//     6. n : 1, m : 1
//     ...
//     6. n : 4, m : 4
//     7. return true
//
//     Let test with bkr -> bc
//     ... n : 2, m : 1
//     4. 2 <= 1
//     4.1.1 return false
//
// 5 - The algorithm looks fine now. It is simple enough and covers all the cases.
//     
// 6 - Let's do it
//
// 7 - Conceptual test.
//     Looks fine
//   - Unusual or non-standard code.
//     Nothing out of the ordinary
//   - Hot spots, like arithmetic and null nodes.
//     Thought about that where an empty string at 0 would break, but it is not the case,
//     since the string exists, it will return empty
//   - Small test cases. It's much faster than a big test case and just as effective.
//     0,1, and 2 characters for all cases
//   - Special cases and edge cases.
//     Empty strings, size differences
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>

bool IsOneWay(const std::string & first, const std::string & second)
{
    bool miss {false};
    //     1. Define the bigger and smaller words
    std::string bigger = [&]() -> std::string { 
        if (second.length() > first.length()) return second;
        return first;
    }();
    std::string smaller = [&]() -> std::string { 
        if (first.length() < second.length()) return first;
        return second;
    }();

    //     2. Check if bigger.size() >= smaller.size() + 2, if so, return false
    if (bigger.length() >= smaller.length() + 2)
    {
        return false;
    }

    //     3. Loop through the bigger word (bigger position : n, smaller position : m)
    for (int n = 0, m = 0; n < bigger.length(); ++n, ++m)
    {
        //     4. Check if m <= smaller.size() - 1
        if (m > smaller.length() - 1)
        {
            //     4.1 If not, check for miss
            if (miss) {
                //     4.1.1 if miss is already set, return false
                return false;
            }
        } 
        //     5. Compare elements
        if (bigger[n] != smaller[m]) {
            //     5.1 if doesn't match, check for miss
            if (miss) {
                //     5.1.1 if miss is already set, return false
                return false;
            }
            //     5.1.2 else miss = true
            miss = true;

            //     5.1.2.1 if bigger.size() != smaller.size(), --m (will not move smaller now)
            if (bigger.length() != smaller.length())
            {
                --m;
            }
        }
    }
    //     7. return true
    return true;
}

int main()
{
    std::vector<std::pair<std::string,std::string>> cases
    {
        {"pale", "bale"},
        {"ple", "pale"},
        {"a", ""},
        {"b", "b"},
        {"aa", "a"},
        {"bb", "a"},
        {"bb", "ba"},
        {"bbb", "b"},
        {"The cake is a lie", "The cake is a lie"},
        {"The cake is a lie", "Thy cake is b lie"}
    };

    for (auto c : cases)
    {
        std::cout << "Is \"" << c.first << "\" and \""<< c.second << "\" ,at most, only one edit away ? " << std::boolalpha << IsOneWay(c.first,c.second) << std::endl;
    }

    return 0;
}

// Problem : Palindrome Permutation
// Description : Given a string, write a function to check if it is a permutation of a
//               palindrome. A palindrome is a word or phases that is the same forward and
//               backwards. A permutation is a rearrangement of letters. The palindrome
//               does not need to be limited to just dictonary words.
//
// Example:
//  Input  : Tact Coa
//  Output : True (permutations: "taco cat", "atco cta", etc.)
//
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
// 1 - This exercise looks very challenging, but in fact the permutation part makes it easier.
//     What defines a palindrome is that the word is the same reading forward or backward, and that
//     implies order, when permutation is add to the equation it makes the order irrelevant.
//     Looking at the description we can take, create a function that receives a string as input
//     and outputs true or false, and the condition is if the string has at least one possible
//     palindrome.
//     In my mind this problem is about counting occurrency of characters and evaluating if
//     the word can be rearranged to form a palindrome or not.
//     One thing that I have to add to this analysis is that looking at the example of the book
//     the comparison is case insensitive. Also, looking the example, spaces are ignored.
//
// 2 - abccab => true {abccba}
//     testing a testing => true {testingagintest}
//     have no idea what => false
//
// 3 - Brute force
//     To be honest, a brute force solution here will not guide me to the right direction
//     I'll create one just for the sake of the exercise, and then I'll redirect it to a
//     simple algorithm that is more direct towards the solution.
//
//     Raw brute force algorithm
//     1. Generate all permutations -> O(N^2)
//     2. Check if any is a palindrome -> O(N^2) -> probably, I will not verify
//
//     Complexity : O(N^2)
//
//     Alternative algorithm
//     1. Sort the string
//     2. Count how many odd occurrencies of characters it have
//     2.1 If 0 or 1, return true
//     2.2 If more than 1, return false
//
//     Complexity : O(N Log(N))
//
//     The one that I'll go with
//     1. Create a map to store characters occurrency
//     2. Loop through the string
//     2.1 Get the char
//     2.1.1 Ignore whitespaces (continue)
//     2.2 Use it as the key to our map, and add 1 to the value
//     3. Loop through the map
//     3.1 Count how many odd values it have
//     4. If we have more than 1 odd value, return false
//     5. If we have 0 or 1, return true.
//
//     Complexity : O(2N)
//
//     Note: Using a map will increase space usage, however, considering that we have a limit
//           number of possible characters and that this exercise is case insensitive, this
//           algorithm will have an atenuation, possible of O(1), if you consider the charset
//           to be ASCII and case insensitive, we will endup if most 128 entries, in case fof
//           Unicode, we can have almost 150.000 entries to our map, which still not a big deal.
//           For the complexity, the second loop will always be N or smaller than, so we can
//           consider the worst case to be O(N).
//
// 4 - One possible optimization would be to remove the second loop and count the occurency of
//     odds during insertion. (Removing unnecessary work)
//
//     1. Create a map to store characters occurrency
//     1.1 Create a variable to keep record of number of odds
//     2. Loop through the string
//     2.1 Get the char
//     2.1.1 Ignore whitespaces (continue)
//     2.2 Use it as the key to our map, and add 1 to the value
//     2.3 If value is odd, add one to the record of odds
//     2.4 If value is even, remove one from the record of odds
//     3. Check it the record of odds is less than 2,
//     3.1 if so, return true [0,1]
//     3.2 if not, return false.
//
//     Complexity : O(N) -> Single loop without input modifications
//
//     Testing with "Tact Coa" (Case insensitive)
//     2.1 char : "T"
//     2.2. map : ["T", 1]
//     2.3. odds : 1
//     2.1 char : "a"
//     2.2 map : ["T", 1], ["a", 1]
//     2.3 odds : 2
//     2.1 char : "c"
//     2.2 map : ["T", 1], ["a", 1], ["c", 1]
//     2.3 odds : 3
//     2.1 char : "t" (Case insensitivy)
//     2.2 map : ["T", 2], ["a", 1], ["c", 1]
//     2.3 odds : 2
//     2.1 char : " "
//     2.1.1 continue
//     2.1 char : "C" (Case insensitivy)
//     2.2 map : ["T", 2], ["a", 1], ["c", 2]
//     2.3 odds : 1
//     2.1 char : "o"
//     2.2 map : ["T", 2], ["a", 1], ["c", 2], ["o", 1]
//     2.3 odds : 2
//     2.1 char : "a"
//     2.2 map : ["T", 2], ["a", 2], ["c", 2], ["o", 1]
//     2.3 odds : 1
//     3. odds < 2 -> 1 < 2 == true
//     3.1 Return True
//
// 5 - The solution uses 2 auxiliary structures, a map and an integer, a loop and some if statements.
//     Things to remember would be, lowercase the characters, or the whole input before comparing,
//     scape whitespaces, we don't need indexes, so using some loop that uses iterator would be
//     more performatic.
//
// 6 - Below
//
// 7 - Conceptual test
//     The concepts checks, line by line analysis. 
//   - Unusual or non-standard code.
//     I could keep a ref to the map entry, which I'm accessing twice, however it's not a big deal
//   - Hot spots, like arithmetic and null nodes.
//     No problem, operator[] covers it
//   - Small test cases. It's much faster than a big test case and just as effective.
//     Couple of 2,3 char test cases.
//   - Special cases and edge cases.
//     Empty string, special characters, even and odd chars

#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <vector>

bool IsPalindromePermutation(const std::string &word)
{
    std::map<char, int> occurrencies;
    int odds_count{0};
    for (auto a : word)
    {
        if (a == ' ')
        {
            continue;
        }
        occurrencies[std::tolower(a)] += 1;
        if (occurrencies[std::tolower(a)] % 2 != 0)
        {
            ++odds_count;
        }
        else
        {
            --odds_count;
        }
    }
    return odds_count < 2;
}

int main()
{
    std::vector<std::string> inputs{
        "Tact Coa",
        "abccab",
        "testing a testing",
        "have no idea what",
        "",
        "a",
        "aba",
        "bba",
        "aaa",
        "abcd",
        " aa a a a",
        "^%%$^"
    };

    for (auto word : inputs)
    {
        std::cout << "Is \"" << word << "\" a Palindrome Permutation ? " << std::boolalpha << IsPalindromePermutation(word) << std::endl;
    }
    return 0;
}

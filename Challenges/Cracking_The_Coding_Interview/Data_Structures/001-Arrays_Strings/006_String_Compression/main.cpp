// Problem : String Compressions
// Description : Implement a method to perform basic string compression using the counts
//               of repeated characters. For example, the string aabcccccaaaa would become
//               a2b1c5a3. If the "compressed" string would not become smaller than the original
//               string, your method should return the original string. You can assume the string
//               has only uppercase and lowercase letters (a-z).
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
// 1 - Key points are, only letters (a-zA-Z), doesn't mention anything about whitespaces, 
//     I'll consider that those are not used, other point is that the output can't be longer
//     than the input. The format should be <letter><frequency>, e.g., a2 | b6.
//
// 2 - aaabbbccc -> a3b3c3
//     abc -> a1b1c1 -> abc (output is longer than the input)
//     AAAbbBBCccc -> A3b2B2C1c3
//     abbbbb -> a1b5
//
//     input : "aab"
//     let : "a" 
//     prev : ""
//     prev != let
//     out = ""
//     prev = "a"
//     count : 1
//     let : "a"
//     prev == let
//     count : 2
//     let : b
//     prev != let
//     out = "a2"
//     prev = "b"
//     count : 1
//     out = "a2b1" -> outside the loop
//     "aab".size() < "a2b1"
//     return "aab" 
//   
// 3 - Brute force solution
//     1. Loop throug the string
//     2. Get the n-th letter
//     3. Compare with previous letter
//     4. If different, 
//     4.1 Add previous letter and count to output string (if not empty)
//     4.2 Set count to zero
//     4.3 Set previous to current letter
//     5. Count++
//     6. After the loop
//     7. Add previous letter and count to output string
//     8. Compare input and output sizes
//     9. Return the smaller
//
//     Complexity : O(N)
//
//     Note: To be honest, the previous step shouldn't be called brute force solution, I'd call it
//     first thing that comes to mind, because it could not be the best solution yet but doesn't
//     mean it will be through brute force, I think I need to read this part of the book again
//     to understand why they say to think in a brute force algorithm first.
//     Getting back to the optimization!
//
// 4 - Well, nothing comes to mind
//
// 5 - Pretty straight forward.
//
// 6 - Let's go!
//
// 7 - Conceptual test.
//     Looks good to me
//   - Unusual or non-standard code.
//     Nothing out of the ordinary
//   - Hot spots, like arithmetic and null nodes.
//     Not in this case, simple loop over an array, no manipulations
//   - Small test cases. It's much faster than a big test case and just as effective.
//     Done
//   - Special cases and edge cases.
//     0,1,2 characters, bigger ones, lower and uppercase letters, empty string
//
#include <iostream>
#include <string>
#include <vector>

std::string Compress(const std::string & word)
{
    int count {0};
    char previous {};
    std::string out {};

    // 1. Loop throug the string
    // 2. Get the n-th letter
    for (auto w : word)
    {
        // 3. Compare with previous letter
        // 4. If different,
        if (w != previous)
        {
            // 4.1 Add previous letter and count to output string (if not empty)
            out += count ? std::string((previous + std::to_string(count))) : "";
            // 4.2 Set count to zero
            count = 0;
            // 4.3 Set previous to current letter
            previous = w;
        }
        // 5. Count++
        ++count;
    }
    // 6. After the loop
    // 7. Add previous letter and count to output string
    out += count ? std::string((previous + std::to_string(count))) : "";
    // 8. Compare input and output sizes
    // 9. Return the smaller
    return (out.length() <= word.length() ? out : word);
}

int main()
{
    std::vector<std::string> words {"aaabbbccc", "abc", "AAAbbBBCccc", "abbbbb", "", "a", "ab", "aa", "aaa", "abcdefghij", "aaaaaaaaaaaaaaaaaaaaaaaaaaaa"};

    for (auto word : words)
    {
        std::cout << "The compression of \"" << word << "\" is \"" << Compress(word) << "\"" << std::endl;
    }

    return 0;
}
// Problem : URLify
// Description : Write a method to replace all spaces in a string with '%20'.
//               You may assume that the string has sufficient space at the end to hold the
//               additional characters, and that you are given the "true" length of the string.
//               (Note: If implementing in Java, please use a character array so that you can
//                perform this operation in place.)
// Example:
//  Input  : "Mr John Smith    ", 13
//  Output : "Mr%20John%20Smith"
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
// 1 - Ok, replacing whitespaces by %20 in place, to do this the exercise states that we have
//     enough space already reserved to the string, counting 2 extra characters to every space.
//     The description say that the true size of the string will be given, so I can deduce that
//     the function will accept 2 parameters, string and length, also that I don't need realocation.
//     The description also have a note, to use character array to be able to perform this operation
//     in place, it mentions Java, but the same applies to C++.
//
// 2 - 
//     Input  : "This is an example      ", 18 (array length 24)
//     Output : "This%20is%20an%20example", (array length 24)
//     
// 3 - Brute force algorithm (Dummy)
//     1. Loop through the array
//     2. Find the next whitespace
//     3. Replace the whitespace with %20
//     4. Move the rest to the right
//     5. Continue
//
//     More realistic approach (Brute force)
//     1. Walk through the array
//     2. If the character is a whitespace, (move all next character 2 spaces)
//     2.1 Replace the whitespace by %
//     2.2 Copy the n+1 and n+2 (after the whitespace)
//     2.3 Replace n+2 by n+1
//     2.4 Replace n+1 by 2
//     2.5 Copy n+3
//     2.6 Replace n+3 by n+2
//     2.7 Replace n+2 by 0
//     3. Continue until the end
//
//     Complexity : O(N^2)
//
//     NOTE. I'm following the books methodology to be more precise during interviews, however,
//           in most cases I have to downgrade my initial thought to find a brute force way to
//           solve the problem. In a real interview I need to keep in mind that this is a general
//           approach and if I see a solution outside of this standard I need to consider if
//           it is worth the risk.
//
// 4 - Not exactly an optimization, but what I initially thought to solve this one is, 
//     do a reverse walk putting the chars to the other end, if a whitespace is found
//     add 02% and keep pushing until all array is transversed.
//     
//     Optimized algorithm
//     1. Loop through the array in reverse order (starting by its end)
//     1.1 Set 2 variables, n and replacement_pos
//     1.1.2 n is the real position in the array in reverse order (array.size)
//     1.1.2 replacemnt_pos is the position where the characters are being evaluated
//     2. Check if char[replacement_pos] is a whitespace
//     2.1 If not, replace char[n] by char[replacement_pos]
//     2.2 If so, replace char[n] by 0, char[n-1] by 2 and char[n-2] by %
//     2.2.1 n -= 2
//     2.3 replacement_pos -= 1
//     2.4 n -=1
//     3. Loop while, n >= replacement_pos
//
//     Complexity : O(N)
//
//     Testing with "Mr John Smith    ", 13
//     1. n = 16, rp = 12 (index 0)
//     2. char[rp] == h
//     2.1 char[16] = h | "Mr John Smith   h"
//     2.3 rp = 11
//     2.4 n = 15
//     2. char[rp] == t
//     2.1 char[15] = t  | "Mr John Smith  th"
//     2.3 rp = 10
//     2.4 n = 14
//     2. char[rp] == i
//     2.1 char[14] = i | "Mr John Smith ith"
//     2.3 rp = 9
//     2.4 n = 13
//     2. char[rp] == m
//     2.1 char[13] = m | "Mr John Smithmith"
//     2.3 rp = 8
//     2.4 n = 12
//     2. char[rp] == S
//     2.1 char[n] = S | "Mr John SmitSmith"
//     2.3 rp = 7
//     2.4 n = 11
//     2. char[rp] == ' ' (whitespace)
//     2.1 char[n] = 0   | "Mr John Smi0Smith"
//     2.1 char[n-1] = 2 | "Mr John Sm20Smith"
//     2.1 char[n-2] = % | "Mr John S%20Smith"
//     2.2.1 n = 9
//     2.3 rp = 6
//     2.4 n = 8
//     2. char[rp] == n
//     2.1 char[n] = n | "Mr John n%20Smith"
//     2.3 rp = 5
//     2.4 n = 7
//     2. char[rp] == h
//     2.1 char[n] = h | "Mr Johnhn%20Smith"
//     2.3 rp = 4
//     2.4 n = 6
//     2. char[rp] == o
//     2.1 char[n] = o | "Mr Johohn%20Smith"
//     2.3 rp = 3
//     2.4 n = 5
//     2. char[rp] == J
//     2.1 char[n] = J | "Mr JoJohn%20Smith"
//     2.3 rp = 2
//     2.4 n = 4
//     2. char[rp] == ' ' (whitespace)
//     2.1 char[n] = 0   | "Mr J0John%20Smith"
//     2.1 char[n-1] = 2 | "Mr 20John%20Smith"
//     2.1 char[n-2] = % | "Mr%20John%20Smith"
//     2.2.1 n = 2
//     2.3 rp = 1
//     2.4 n = 1
//     3. Exit loop, n >= replacement_pos is no longer valid
//
// 5 - The proposed solution will use 2 carriers to keep track of where to look inside the array
//     the idea is to look at 2 different points in the array at the same time, and do the proper
//     operations accordingly, it will end when you are looking and replacing at the same position,
//     or if for some reason (can think of any case where this could happen)
//     the positions got inverted.
//
// 6 - Let's do this!
//
// 7 - Conceptual test.
//     Found a problem, while comparison can't be >=, it may be a problem
//     in some edge cases, empty strings not terminated in \0 for example.
//   - Unusual or non-standard code.
//     Nothing out of the ordinary
//   - Hot spots, like arithmetic and null nodes.
//     We could have a problem if the string doesn't have enough space,
//     however, the exercise description assures us that it will.
//   - Small test cases.
//     Done
//   - Special cases and edge cases.
//     Empty, starting with space, ending with space, single space
// 

#include <iostream>
// In c++ there is no guarantees about the length of a string using char *
// strlen will only work if the char * is \0 terminated, that being said
// I'll receive the lengths through parameters, 
// which is a common practice in the C-Style programming.
char * urilify(char * word, const int&& arr_length, const int&& word_lenght)
{
    int n = arr_length - 1;
    int rp = word_lenght - 1;
    while(n > rp)
    {
        if (word[rp] == ' ')
        {
            word[n] = '0';
            word[n-1] = '2';
            word[n-2] = '%';
            n -= 2;
        } else {
            word[n] = word[rp];
        }
        --rp;
        --n;
    }

    return word;
}

int main()
{
    char word[] = {"Mr John Smith    "};
    std::cout << urilify(word, 17, 13) << std::endl;
    char word2[] = {""};
    std::cout << urilify(word2, 0, 0) << std::endl;
    char word3[] = {"Tes T  "};
    std::cout << urilify(word3, 7, 5) << std::endl;
    char word4[] = " First Space    ";
    std::cout << urilify(word4, 16, 12) << std::endl;
    char word5[] = "   "; // Single space, it's odd but should work
    std::cout << urilify(word5, 3, 1) << std::endl;
    char word6[] = "Last Space     ";
    std::cout << urilify(word6, 15, 11) << std::endl;

    return 0;
}

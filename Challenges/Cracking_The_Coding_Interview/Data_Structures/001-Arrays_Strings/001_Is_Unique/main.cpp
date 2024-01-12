// Problem : Is Unique
// Descriptions : Implement an algorithm to determine if a string has all unique characters. (1)
//                What if you cannot use additional data structures? (2)
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
// 1 - The problem is asking to check if a given string has all unique characters,
//     from my point-of-view it means that "abcd" is a valid string and "abcc" is not.
//     Also, the problem don't mention anything about empty strings, I'll assume that
//     in this case there are no repetitions since we don't have what to repeat.
//     Also it doesn't mention anything about whitespaces, I'll assume those are unique characters.
//
// 2 - "doug has five pt", "doughasfivept" , "yhasbashsabdko", "keyboardcaps", "abcdefghijklm"
//
// 3 - 1 . Get first letter
//     2 . Compare to all others
//     3 . if any repetition is found, return false
//     4 . if reaches the end of the string without founding any repetition, then,
//     5 . Check if has a next letter
//     6 . If so, get the next letter and return to step 2.
//     7 . If not, return true.
//
//     Brute force using the first example - "doug has five pt"
//     1 . letter : d
//     2 . d != o -> d != u -> d != g -> d !=  -> d != h -> ... -> d != t
//     3 . No repetition found
//     4 . End reached
//     5 . It has a next letter
//     6 . letter : o
//     2 . d != u -> d != g -> d !=  -> d != h -> ... -> d != t
//     3 . No repetition found
//     4 . End reached
//     5 . It has a next letter
//     6 . letter : u
//     2 . d != g -> d !=  -> d != h -> ... -> d != t
//     3 . No repetition found
//     4 . End reached
//     5 . It has a next letter
//     6 . letter : g
//     2 . d !=  -> d != h -> ... -> d != t
//     3 . No repetition found
//     4 . End reached
//     5 . It has a next letter
//     6 . letter :  (whitespace)
//     2 . d != h -> d != a -> d != s -> d == -> ... -> d != t
//     3 . Repetition found -> Returning False
//
//     Defining the runtime - Worst Case
//     O(n-1) + O(n - 2) + O(n-3) + ... + O(n - (n - 1)) or O(1)
//     O(n^2 - (n(n+1)/2))
//     O(n^2 - ((n^2 + n)/2))
//     O(n^2 - (n^2)/2 - n/2)
//     O(n^2/2 - n/2)
//     O((n^2 - n) / 2)
//     We can consider O(n^2) for this case.
//
// 4 - Optimization, for this step I see 2 possible optimizations, one is to use a set or map
//     to keep track of visit characters, and stop if the letter was previously set, in
//     the worst case the complexity will be O(N).
//     A second option that will not require any other auxiliary data structure, would be to
//     sort the string using any algorithm with O(n log(n)) complexity, like, merge sort, then
//     transverse the string to check if any consecutive characters are equal, this will take
//     the complexity to O(n log(n)) + O(n), or O (n (log(n) + 1)), so we can consider it
//     to be O(n log(n)), the second case is less performatic than the first but reduces the
//     memory used.
//
//     Algorithm for the first option:
//     1. Get first character
//     2. Check if it is already set
//     3. If so, return false
//     4. If not, set it
//     5. Check if next character exists
//     6. If so, Move to next Character
//     7. Return to step 2
//     8. If not, return true
//
//     Testing algorithm on "doug has five pt"
//     1. char : d
//     2. set : [], d is not set
//     4. set : [d]
//     5. char[n+1] : o
//     6. char : o
//     2. set : [d], o is not set
//     4. set : [d, o]
//     5. char[n+1] : u
//     6. char : u
//     2. ... <Continue to the second whitespace>
//     6. char :  <whitespace>
//     2. set : [d,o,u,g, ,h,a,s] : <whitespace> is set
//     3. return false
//
//     Complexity : O(N)
//
//     Algorithm for the second option:
//     1. Sort the string (Using Merge Sort)
//     2. Get the first character
//     3. Check if it has a next char
//     4. If so, compare both
//     4.1 If equal, return false
//     4.2 If not, get n+1 character
//     4.2.1 return to step 3
//     5. return true (no more characters)
//
//     obs. We are not describing the algorithm for merge sort here, this will be covered in a
//          future challenge.
//
//     Testing algorithm on "doug has five pt"
//     1. sort : "  adefghiopstuv"
//     2. char : " "
//     3. char[n+1] : exist
//     4. char[n] == char[n+1], true, return false
//
//     Complexity : O(nLog(n))
//
//     In this example, we reached the the result on the firts iteration, considering
//     whitespaces to be lower than other characters (ASCII for space is 32, for `a` is 97)
//
//     One possible optimization would be to do the comparison inside the merge sort, another is
//     to use a different sorting algorithm, but we will keep this for now, this is not the goal
//     of this exercise.
//
// 5 - I'll implement both solutions, since the exercice asks for, and we may have a problem here
//     merge sort will use additional data structures.
//     To solve it we would need to use a in-place sorting algorithm, like Heap Sort.
//     Since this is not the main goal of this exercise, and we will not implement the sorting
//     algorithm, I'll leave this annotation here.
//
// 6 - The implementations are below
//
// 7 - Tests
//     - Conceptual test.
//       - Seens ok to me
//     - Unusual or non-standard code.
//       - Nothing out of the ordinary
//     - Hot spots, like arithmetic and null nodes.
//       - Looks fine
//     - Small test cases. It's much faster than a big test case and just as effective.
//       - Using 12 strings as test case
//     - Special cases and edge cases.
//       - Empty string, last character equality, even, odd, long sequence, single character
//
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

// 1 - Using additional data structures

//     1. Get first character
//     2. Check if it is already set
//     3. If so, return false
//     4. If not, set it
//     5. Check if next character exists
//     6. If so, Move to next Character
//     7. Return to step 2
//     8. If not, return true
bool is_unique(const std::string &word)
{
    std::set<char> visited;

    for (char c : word) // 1.
    {
        if (visited.contains(c)) // 2. // C++ 20
        {
            return false; // 3.
        }
        visited.insert(c); // 4.
        // 5. and 6. will be the natural order of the for loop
    } // 7.

    return true; // 8.
}

// 2 - Not using additional data structures
//     1. Sort the string (Using Merge Sort)
//     2. Get the first character
//     3. Check if it has a next char
//     4. If so, compare both
//     4.1 If equal, return false
//     4.2 If not, get n+1 character
//     4.2.1 return to step 3
//     5. return true (no more characters)
bool is_unique_no_additional_data_structures(std::string word)
{
    std::sort(std::begin(word), std::end(word)); // 1. // std::sort complexity O(n log(n))

    for (auto it = std::begin(word); it != std::end(word); ++it)
    { // 2.
        if ((it + 1) != std::end(word))
        { // 3.
            if (*it == (*(it + 1)))
            { // 4. // char == char
                return false;
            }
        } // 4.2 // Natural order of the for loop
    }
    return true; // 5.
}

int main()
{
    std::vector<std::string> test_strings{
        "",
        "a",
        "aa",
        "aaa",
        "ab",
        "abc",
        "doug has five pt",
        "doughasfivept",
        "yhasbashsabdko",
        "keyboardcaps",
        "abcdefghijklmnopqrstuvxywz",
        "abcdefga"};

    for (std::string ts : test_strings)
    {
        std::cout << "1 - Is \"" << ts << "\" unique : " << std::boolalpha << is_unique(ts) << std::endl;
        std::cout << "2 - Is \"" << ts << "\" unique (no add struct) : " << std::boolalpha << is_unique_no_additional_data_structures(ts) << std::endl;
        std::cout << "---------------------------------------------------------------" << std::endl;
    }

    return 0;
}
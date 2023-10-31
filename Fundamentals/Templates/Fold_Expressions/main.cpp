#include <iostream>

// Fold Expressions (C++17)
// Fold expressions in C++17 are a powerful feature that allows you to reduce or "fold" a
// parameter pack over a binary operator. They were introduced to simplify code that operates
// on variadic templates and make it more concise and readable.

// Syntax
// (pack op ...)
// (... op pack)
// (pack op ... op init)
// (init op .. op pack)

// Here, op is any binary operator, pack is an expression containing an unexpanded parameter pack,
// and init is an expression without an unexpanded paramter pack.

// - Operator (op) : This refers to any 32 different mathematical symbols or signs used for operations
//                   like addition (+), subtraction (-), multiplication (*), division (/), and so on.
//                   In the context you've given, both operands (the things that these ooperators
//                   operate on) foldExpressionsWithLambda(1, 1.3, "This is a string", 5.8f);must use the same operator.
// - Parameter Pack (pack) : Think of a parameter pack as a collection or a list of items, but there's
//                           a special condition here. It's a list that contains variables or expressions
//                           that have not been fully determinded or expanded yet. It's like having a
//                           placeholder for some values that will be filled in later.
// - Expression without
//   parameter pack (init) : This refers to an expression or a statement that doesn't involve any placeholder
//                           values or incomplete parts. It's a complete and fully defined piece of code
//                           or mathematical operation.
//
// Note: The opening and closing parantheses are a required part of the fold expression
// Note : The initial value is useful in cases to avoid errors where the parameter pack does not
//        have any parameters.

// Types of Fold Expression (4)
// - Unary Right Fold  : (pack op ...)
template <typename... Arguments>
bool allRightFold(Arguments... args)
{
    return (args && ...);
};

void unaryRightFold()
{
    bool b = allRightFold(true, true, true, false);
    std::cout << "Unary Right Fold result : " << std::boolalpha << b << std::endl; // False
};

// In this example, all function checks if all the arguments are true by performing a unary right
// fold with the logical AND operator &&.

// The right fold expression will be expanded as :
// (pack1 op (... op (packN-1 op packN)))
//
// In our example
// (true && (true && (true && false)))

// - Unary Left Fold   : (... op pack)
template <typename... Arguments>
bool allLeftFold(Arguments... args)
{
    return (... && args);
};

void unaryLeftFold()
{
    bool b = allLeftFold(true, true, true, false);
    std::cout << "Unary Left Fold result : " << std::boolalpha << b << std::endl; // False
};

// Same as the previous one except the syntax if left to right ( ... op pack)

// The left fold expression will be expanded as:
// ((pack1 op pack2) op ... ) op packN

// In our example
// ((true && true) && true) && false

// - Binary Right Fold : (pack op ... op init)
template <typename... Arguments>
int addsOneToSumBinaryRightFold(Arguments &&...args)
{
    return (args + ... + 1); // Performs a binary right fold with addition
};

void binaryRightFold()
{
    int result = addsOneToSumBinaryRightFold(1, 2, 3, 4);
    std::cout << "Binary Right Fold result : " << result << std::endl;
};

// Here, the sum function calculates the sum of all its arguments using a binary right fold with
// the addition operator +

// The binary right fold will be expanded as:
// (pack1 op (... op (packN op init)))

// In our example
// (1 + (2 + (3 + (4 + 1))))

// - Binary Left Fold  : (init op ... op pack)
template <typename... Arguments>
int addsOneToSumBinaryLeftFold(Arguments &&...args)
{
    return (1 + ... + args); // Performs a binary right fold with addition
};

void binaryLeftFold()
{
    int result = addsOneToSumBinaryLeftFold(1, 2, 3, 4);
    std::cout << "Binary Left Fold result : " << result << std::endl;
};

// Same as previous one, except left to right

// In binary fold expression, both operators op must be the same

// The binary left fold will be expanded as:
// (((init op pack1) op ...) op packN)

// In our example:
// ((((1 + 1) + 2) + 3) + 4)

// Another example
// Unary left fold with empty pack
template <typename... Arguments>
bool any(Arguments... args)
{
    return (... || args);
};

void unaryLeftFoldWithEmptyPack()
{
    bool b = any();
    std::cout << "Unary Left Fold with Empty Pack result : " << std::boolalpha << b << std::endl;
};

// Using lambda with fold expressions
template <typename... Arguments>
void foldExpressionsWithLambda(Arguments... args)
{
    int i = 0;
    // Here we are taking advantage of the comma operator
    // As a reminder, the default version of the comma operator
    // executes the left operand, then the right operand, then returns the
    // right operand.
    // The comma operator can execute two operations. Therefor folding
    // over the comma operator can execute an arbitrary number of expressions
    (
        [&]
        {
            std::cout << "Arg " << i << " : " << args << std::endl;
            i++;
        }(),
        ...);
    // Expanding this techique we have:
    // (lambda(arg1), lambda(arg2), ..., lambda(argN))
};

// To be more clear of what is going on in the fold
// The lambda could be expressed as
// [](auto arg) {
//    // do something with arg
// }
// The fold would expand on the parameter of the lambda funcion, so this
// (lambda(args), ...) would became (lambda(arg1), lambda(arg2), ..., lambda(argN))
//
// Let's test it
template <typename... Arguments>
void foldExpressionsWithLambdaExpanded(Arguments... args)
{
    int i = 0;
    auto lambdaFunct = [&i](auto arg)
    {
        std::cout << "Expanded approach " << i << " : " << arg << std::endl;
        i++;
    };
    (lambdaFunct(args), ...);
};

int main()
{
    std::cout << "Fold Expressions" << std::endl;
    unaryRightFold();
    unaryLeftFold();
    binaryRightFold();
    binaryLeftFold();
    unaryLeftFoldWithEmptyPack(); // False, as the logical OR operator || returns false for an empty pack
    foldExpressionsWithLambda<int, double, std::string, float>(1, 1.3, "This is a string", 5.8f);
    // Type definitions can be ommited in this example.
    foldExpressionsWithLambda(1, 1.3, "This is a string", 5.8f);
    foldExpressionsWithLambdaExpanded(1.1, "Wow!! how this is even possible", 3, 5.4f);
    
    return 0;
}
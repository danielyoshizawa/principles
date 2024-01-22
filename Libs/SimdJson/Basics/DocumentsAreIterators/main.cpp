// Documents are Iterators
//
// The simdjson library relies on an approach to parsing JSON that we call "On Demand".
// A document is not a fully-parsed JSON value; rather, it is an iterator over the JSON text.
// This means that while you iterate an array, or search for a field in an object, it is actually
// walking through the original JSON text, merrily reading commans and colons and brackets
// to make sure you get where you are going. This it the key to On Demand's performance:
// since it's just an iterator, it lets you parse values as you use them. And particularly, it
// lets you skip values you do not want to use. On Demand is also ideally suited when you
// want to capture part of the document without parsing it immediately(e.g. see Raw Strings).
//
// We refer to "On Demand" as a front-end component since it is an interface between the low-level
// parsing functions and the user. It hides much of the complexity of parsing JSON documents.
//
// Parser, Document and JSON scope
//
// For code safety, you should keep (1) the parser instance, (2) the input string and (3) the
// document instance alive throughout your parsing. Additionally, you should follow the following
// rules:
//
// - A parser may have at most one document open at a time, since it holds allocated memory used
//   for parsing.
// - By design, you should only have one document instance per JSON document. Thus, if you must
//   pass a document instance to a function, you should avoid passing it by value: choose to pass
//   it by reference instance to avoid the copy. (We also provide a document_reference class if
//   you need to pass by value).
//
// During the iterate call, the original JSON text is never modified-only read. After you are done
// with the document, the source (wheter file or string) can be safely discarded.
//
// For best performance, a parser instance should be reused over several files: otherwise you will
// needlessly reallocate memory, an expensive process. It is also possible to avoid entirely memory
// allocations during parsing when using simdjson.
//
// If you need to have several documents active at once, you should have several parser instances.

#include <iostream>
#include <simdjson.h>
#include <string>

int main()
{
    simdjson::ondemand::parser parser;
    std::string data = "Test data";
    simdjson::padded_string my_padded_data(data);
    simdjson::ondemand::document doc = parser.iterate(my_padded_data);
    std::cout << doc << std::endl;

    return 0;
}
// Newline-Delimited JSON (ndjson) and JSON lines
//
// When processing large inputs (e.g. in the context of data engineering),
// engineers commonly serialize data into strams of multiple JSON documents.
// That is, instead of one large (e.g. 2 GB) JSON document containing multiple
// recors, it is often preferable to write out multiple records as independent
// JSON documents, to be read one-by-one.
//
// The simdjson library also supports multithread JSON streaming through a large
// file containing many smaller JSON documents in either ndjson or JSON lines format.
// If you JSON document all contain arrays or objects, we even support direct file
// concatenation without whitespace. However, if there is content between your JSON
// documents, it should be exclusively ASCII white-space characters.
//
// The concatenated file has no size restrictions (including larger than 4MB),
// though each individual document must be no larger than 4 GB.
//
// Here is an example:

#include <iostream>
#include <simdjson.h>

void iterate_many_example()
{
    auto json = R"({"foo" : 1}{ "foo" : 2}{ "foo" : 3})"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document_stream docs = parser.iterate_many(json);

    for (auto doc : docs)
    {
        std::cout << doc["foo"] << std::endl;
    }
}

// Unlike parser.iterate, parser.iterate_many may parse "on demand" (lazily).
// That is, no parsing may have been done before you enter the loop for (auto doc : docs) {
// and you should expect the parser to only ever fully parse one JSON document
// at time.
//
// As with parser.iterate, when calling parser.(string), no copy is made of the
// provided string input. The provided memory buffer may be accessed each time a JSON document
// is parsed. Calling parser.iterate_many(string) on a temporary string buffer
// (e.g. docs = parser.parse_many("[1,2,3]"_padded)) is unsafe (and will not compile) because
// the document_stream instance needs access to the buffer to return the JSON documents.
//
// The iterate_many function can also take an optional parameter size_t batch_size which defines
// the window processing size. It is set by default to a large value (1000000 corresponding to 1MB).
// None of your JSON documents should exceed this window size, or else you will get the error
// simdjson::CAPACITY. You cannot set this window size larger than 4GB: you will get the error
// simjson::CAPACITY. The smaller the window size is, the less memory the function will use.
// Setting the window size too small (e.g. less than 100kB) may also imapct perfromace negatively.
// Leavint it to 1MB is exxpected to be a good choice, unless you have some larger documets.
//
// The following toy examples illustrates how to get capacity errors. It is an artificial example
// since you should never use a batch_size of 50 bytes (it is far too small).

void small_batch_size()
{
    // We are going to set the capacity to 50 bytes which means that we cannot
    // loading a document longer than 50 bytes. The first few documents are small,
    // but the last one is large. We will get an error at the last document.
    auto json = R"(
        [1,2,3,4,5] [1,2,3,4,5] [1,2,3,4,5] [1,2,3,4,5] [1,2,3,4,5] [1,2,3,4,5] 
        [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100]
        )"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document_stream stream;
    size_t counter{0};
    auto error = parser.iterate_many(json, 50).get(stream);
    if (error)
    { /* handle the error */
    }
    for (auto doc : stream)
    {
        if (counter < 6)
        {
            int64_t val;
            error = doc.at_pointer("/4").get(val);
            if (error)
            { /* handle the error */
            }
            std::cout << "5 = " << val << std::endl;
        }
        else
        {
            simdjson::ondemand::value val;
            error = doc.at_pointer("/4").get(val);
            // error == simdjson::CAPACITY
            if (error)
            {
                std::cerr << error << std::endl;
                // We left 293 bytes unprocessed at the tail end of the input.
                std::cout << " unprocessed bytes at the end: " << stream.truncated_bytes() << std::endl;
                break;
            }
        }
        counter++;
    }
}

// This example should print out:
// 5 = 5
// 5 = 5
// 5 = 5
// 5 = 5
// 5 = 5
// 5 = 5
// this parser can't support a document that big
//  unprocessed bytes at the end: 302
//
// If your documents are large (e.g. larger than a megabyte), then the iterate_many function is
// maybe ill-suited. It is really meant to support reading efficiently streams of relatively
// small docuemnts (e.g., a few kilobytes each). If you have larger documents, you should use other
// functions like iterate.
//
// We also provide somesupport for comma-separated documents and other advanced features.
// See iterate_many for detailed information and design.

int main()
{
    iterate_many_example();
    small_batch_size();

    return 0;
}
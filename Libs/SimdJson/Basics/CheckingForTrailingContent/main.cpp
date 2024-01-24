// Checking for trailing content
//
// The parser validates all parsed content, but your code may exhaust the content while not having
// processed the entire docuemtn. Thus, as a final optional step, you may call at_ent() on the
// document instance. If it returns false, then you may conclude that you have trailing content
// and that your document is not valid JSON. You may then use doc.current_location() to obtain a
// pointer to the start of the trailing content.

#include <iostream>
#include <simdjson.h>

void check_trailing()
{
    auto json = R"([1,2] foo)"_padded;
    simdjson::ondemand::parser parser;
    simdjson::ondemand::document doc = parser.iterate(json);
    simdjson::ondemand::array array = doc.get_array();

    for (uint64_t values : array)
    {
        std::cout << values << std::endl;
    }
    // if (!doc.at_end()) // This method doesn't exist in the version that I'm using
    if (doc.current_location().error() != simdjson::SUCCESS)
    {
        // In this instance, we will be left pointing at 'foo' since we have consumed the array
        // [1,2].
        std::cerr << "Trailing content at byte index" << doc.current_location() - json.data() << std::endl;
    }
}

// The at_end() method is equivalent to doc.current_location().error() == sindjsom::SUCCESS but
// more convenient.

int main()
{
    check_trailing();

    return 0;
}
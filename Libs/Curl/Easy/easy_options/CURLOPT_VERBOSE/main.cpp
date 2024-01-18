// Name
// CURLOPT_VERBOSE - verbose mode
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_VERBOSE, long onoff);
//
// Description
// Set the onoff parameter to 1 to make the library display a lot of verbose information about its
// operations on this handle. Useful for libcurl and/or protocol debugging and understanding.
// The verbose information is sent to stderr, or the stream set with CURLOPT_STDERR.
//
// You hardly ever want this enabled in production use, you almost always want this used when you
// debug/report problems.
//
// To also get all the protocol data sent and received, consider using the CURLOPT_DEBUGFUNCTION.
//
// Default
// 0, meaning disabled.
// 
// Protocols
// All
//
// Availability
// Always
//
// Return Value
// Returns CURLE_OK
//

#include <iostream>
#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    // ask libcurl to show us the verbose output
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    curl_easy_cleanup(curl);
  }

  return 0;
}

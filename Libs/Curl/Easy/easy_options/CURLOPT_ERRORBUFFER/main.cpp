// Name
// CURLOPT_ERRORBUFFER - error buffer for error messages
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_ERRORBUFFER, char* buf);
//
// Description
// Pass a char* to a buffer that libcurl may use to store human readable error
// messages on failures or problems. This may be more helpful than just the
// return code from curl_easy_perform and related functions.
// The buffer must be at least CURL_ERROR_SIZE bytes big.
//
// You must keep the associated buffer available until libcurl no longer needs
// it. Failing to do so might cause odd behavior or even crashes.
// libcurl might need it until you call curl_easy_cleanup or you set the
// same option again to use a different pointer.
//
// Do not rely on the contents of the buffer unless an error code was returned.
// Since 7.60.0 libcurl initializes the contents of the error buffer to an empty
// string beforte performing the transfer. For earlier versions if an error code
// was returned but there was no error detail then the buffer was untouched.
//
// Consider CURLOPT_VERBOSE and CURLOPT_DEBUGFUNCTION to better debug and trace
// why errors happen.
//
// Default
// NULL
//
// Protocols
// All
//
// Availability
// Always
//
// Return Value
// Returns CURLE_OK.
//

#include <iostream>
#include <curl/curl.h>
#include <string.h> // For strlen

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    char errbuf[CURL_ERROR_SIZE];
    curl_easy_setopt(curl, CURLOPT_URL, "https://ERROR.ERROR");

    // provide a buffer to stroe erros in
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
    // set the error buffer as empty before performing a request
    errbuf[0] = 0;

    // Request
    response = curl_easy_perform(curl);

    // If the request did not complete correctly, show the error information.
    // If no detailed error information was written to errbuf
    // show the more geneeric information from curl_easy_strerror instead.
    if (response != CURLE_OK)
    {
      size_t len = strlen(errbuf);
      if (len)
      {
        std::cout << "## error buffer : " << errbuf << std::endl;
      } else {
        std::cout << "## error response : " << curl_easy_strerror(response) << std::endl;
      }
    }
    curl_easy_cleanup(curl);
  }

  return 0;
}

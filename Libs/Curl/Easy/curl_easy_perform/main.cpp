// Name
// curl_easy_perform - Perform a file transfer synchronously
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_perform(CURL *easy_handle);
//
// Description
// curl_easy_perform performs a network transfer in a blocking manner and returns
// when done, or earlier if it fails. For non-blocking behavior, see curl_multi_perform.
//
// Invoke this function after curl_easy_init and all the curl_easy_setopt calls
// are made, and it performs the transfer as described in the options. It must
// be called with the same easy_handle as input as the curl_easy_init call returned.
//
// You can do any amount of calls to curl_easy_perform while using the same
// easy_handel. If you intend to transfer more than one file, you are encouraged
// to do so. libcurl attempts to reuse existing connections for the following
// transfers, thus making the operations faster, less CPU intense and using less
// network resources. You probably want to use curl_easy_setopt between the invokes
// to set options for the following curl_easy_perform calls.
//
// You must never call this function simultaneously from two places using the same
// easy_handle. Let the function return first before invoking it another time.
// If you want parallel transfers, you must use several curl easy_handles.
//
// A network transfer moves data to a peer or from a peer. An application tells
// libcurl how to receive data by sending CURLOPT_WRITEFUNCTION and CURLOPT_WRITEDATA
// options. To tell libcurl what data to send, there are a few more alternatives but
// two common ones are CURLOPT_READFUNCTION and CURLOPT_POSTFIELDS.
//
// While the easy_handle is added to a multi handle, it cannot be used by curl_easy_perform.
//
// Availability
// Always
//
// Return Value
// CURLE_OK (0) means everything was OK, non-zero means an error occured as
// <curl/curl.h> defines - see libcurl-erros. If the CURLOPT_ERRORBUFFER was set
// with curl_easy_setopt there is a readable error message stored in the error
// buffer when non-zero is returned.

#include <iostream>
#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    // Reusing curl_easy_perform
    std::cout << "##############################" << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    curl_easy_cleanup(curl);
  }

  return 0;
}

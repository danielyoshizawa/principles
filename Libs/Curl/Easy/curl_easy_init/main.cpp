// curl_easy_init - create an easy handle
// Name
// curl_easy_init - Start a libcurl easy session
//
// Synopsis
// #include <curl/curl.h>
// CURL * curl_easy_init();
//
// Description
// This function allocates and returns a CURL easy handle. Such a handle is used
// as input to other funcitons in the easy interface. This call must have a
// corresponding call to curl_easy_cleanup when the operation is complete.
//
// The easy handle is used to hold and control a single network transfer.
// It is encouraged to reuse easy handles for repeated transfers.
//
// An alternative way to get a new easy handle is to duplicate an already
// existing one with curl_easy_duphandle, which has the upside that it gets all
// the options that were set in the source handle set in the new copy as well.
//
// If you did not already call curl_global_init before calling this function,
// curl_easy_init does it automatically. This may be lethal in multi-thread cases,
// if curl_global)init is not thread-safe in your system, and it may then result
// in resouce problems because there is no corresponding cleanup.
//
// You are strongly advised to not allow this automatic behavior, by calling
// curl_global_init yourself properly.
// See the description in libcurl(3) of global environment requirements for
// details of how to use this funciton.

// Availability
// Always
//
// Return Value
// If this function returns NULL, something went wrong and you cannot use the
// other curl funcitons.

#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    response = curl_easy_perform(curl); // By default curl_easy_perform will print the page to the console
    curl_easy_cleanup(curl);
  }

  return 0;
}

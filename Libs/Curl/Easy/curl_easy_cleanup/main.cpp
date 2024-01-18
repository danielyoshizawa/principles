// Name
// curl_easy_init - End a libcurl easy handle
//
// Synopsis
// #include <curl/curl.h>
// void curl_easy_cleanup(CURL *handle);
//
// Description
// This function is the opposit of curl_easy_init. It closes down and frees all
// resources previously associated with this easy handle.
//
// This call closes all connections this handle has used and possibly has kept
// open until now unless the easy handle was attached to a multi hanlde while
// doing the transfers. Do not call this function if you intend to transfer
// more files, reusing handles is a key to good performance with libcurl.
//
// Occasionally you may get your progress callbacks or header callback called
// from within curl_easy_cleanup (if previously set for the handle using
// curl_easy_setopt). Like if libcurl decides to shut down the connection and
// the protocol is of a kind that requires a command/response sequence before
// disconnect. Examples of such protocols are FTP, POP3 and IMAP.
//
// Any use of the easy handle after this function has been called and have
// returned, is illegal.
//
// To close an easy handle that has been used with the multi interface, make sure
// to first call curl_multi_remove_handle to remove it from the multi handle
// before it is closed.
//
// Passing in a NULL pointer in handle makes this function return immediately
// with no action.
//
// Availability
// Added in 7.1
//
// Return Value
// None

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
    curl_easy_cleanup(curl);
  }

  return 0;
}

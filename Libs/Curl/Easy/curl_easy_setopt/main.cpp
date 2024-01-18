// Name
// curl_easy_setopt - set options for a curl easy handle
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameters);
//
// Description
// curl_easy_setopt is used to tell libcurl how to behave. By setting the appropriate options,
// the application can change libcurl's behavior. All options are set with an option followed by
// a parameter. That parameter can be a long, a function pointer, an object pointer or a curl_off_t,
// depending on what the specific option expects. Read this manual carefully as bad input values
// may cause libcurl to behave badly! You can only set one option in each function call. A typical
// application uses many curl_easy_setopt calls in the setup phase.
//
// Options set with this function call are valid for all forthcoming transfers performed using this
// hanlde. The options are not in any way reset between transfers, so if you want subsequent transfers
// with different options, you must change them between the transfers. You can optionally reset all
// options back to internal default with curl_easy_reset.
//
// Strings passed to libcurl as 'char *' arguments, are copied by the library; the string storage
// associated to the pointer argument may be discarded or reused after curl_easy_setopt returns.
// The only exception to this rule is really CURLOPT_POSTFIELDS, but the alternative that copies
// the string CURLOPT_COPYPOSTFIELDS has some usage characteristics you need to read up on.
// This function does not accept input strings longer than CURL_MAX_INPUT_LENGTH (8 MB).
//
// The order in which the options are set does not matter.
//
// Before verions 7.17.0, strings were not copied. Instead the user was forced to keep them available
// until libcurl no longer needed them.
//
// The handle is the return code from a curl_easy_init or curl_easy_duphandle call.
//
// Behavior options
// We will cover the most important ones as we go with our studies, since this list is very extensive
// I'll try to add more of them as I go, for now I'll keep the reference link here and move on.
//
// https://curl.se/libcurl/c/curl_easy_setopt.html
// https://curl.se/libcurl/c/easy_setopt_options.html
//
// CURLOPT_VERBOSE - Display verbose information.
// CURLOPT_HEADER - Include the header in the body output.
// CURLOPT_NOPROGRESS - Shut off the progress meter.
// CURLOPT_NOSIGNAL - Do not install signal handlers.
// CURLOPT_WILDCARDMATCH - Transfer multiple files according to a file name pattern.
//
// # Callback options
// CURLOPT_WRITEFUNCTION - Callback for writting data.
// CURLOPT_WRITEDATA - Data pointer to pass to the write callback.
// CURLOPT_READFUNCTION - Callback for reading data.
// CURLOPT_READDATA - Data pointer to pass to the read callback.
// CURLOPT_IOCTLFUNCTION - (Deprecated) - Callback for I/O operations.
// CURLOPT_IOCTLDATA - (Deprecated) - Data pointer to pass to the I/O callback.
// CURLOPT_SEEKFUNCTION - Callback for seek operations.
// CURLOPT_SEEKDATA - Data pointer to pass to the seek callback.
// CURLOPT_SOCKOPTFUNCTION - Callback for sockopt operations.
// CURLOPT_SOCKOPTDATA - Data pointer to pass to the sockopt callback.
// CURLOPT_OPENSOCKETFUNCTION - Callback for socket creation.
// CURLOPT_OPENSOCKETDATA - Data pointer to pass to the open socket callback.
// CURLOPT_CLOSESOCKETFUNCTION - Callback for closing socket.
// CURLOPT_CLOSESOCKETDATA - Data pointer to pass to the close socket callback.
// 
// # Error options
// # Network options
// # Names and passwords options (authentication)
// # Http options
// # Smtp options
// # Tftp options
// # Ftp options
// # Rtsp options
// # Protocol options
// # Connection options
// # SSL and security options
// # SSH options
// # Websocket
// # Other options
// # Telnet options
//
// Availability
// Always
//
// Return Value
// CURLE_OK (0) means that the option was set properly, non-zero means an error occurred as
// <curl/curl.h> defines. See the libcurl-errors man page for the full list with descriptions.
//
// Strings passed on to libcurl must be shorter than 8000000 bytes, otherwise curl_easy_setopt
// returns CURLE_BAD_FUNCTION_ARGUMENT (added in 7.65.0).
//
// CURLE_BAD_FUNCTION_ARGUMENT is returned when the argument to an option is invalid, like perhaps
// out of range.
//
// If you try to set an option that libcurl does not know about, perhaps because the library is too
// old to support it or the option was removed in a recent version, this function returns
// CURLE_UNKNOWN_OPTION. If support for that option was disabled at compile-time, it returns 
// CURLE_NOT_BUILT_IN.

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

// Name
// CURLOPT_URL - URL for this transfer
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_URL, char* URL);
//
// Description
// Pass in a pointer to the URL to work with. The parameter should be a char*
// to a null-terminated string which must be URL-encoded in the following format:
//
// scheme://host:port/path
//
// For a greater explanation of the formar please see RFC 3986.
//
// libcurl does not validate the syntax or use the URL until the transfer is started.
// Even if you set a crazy value here, curl_easy_setopt might still return CURLE_OK.
//
// If the given URL is missing a schema name (such as "http://" or "ftp://" etc)
// then libcurl guesses based on the host. If the outermost subdomain name matches
// DICT, FTP, IMAP, LDAP, POP3 or SMTP then that protocol gets used, otherwise
// HTTP is used. Since 7.45.0 guessing can be disabled by setting a default
// protocol, see CURLOPT_DEFAULT_PROTOCOL for details.
//
// Should the protocol, either as specified by the URL scheme or deduced by libcurl
// from the host name, not be supported by libcurl then CURLE_UNSUPPORTED_PROTOCOL
// is returned from either the curl_easy_perform or curl_multi_perform functions
// when you call them. Use CURLOPT_PROTOCOLS_STR can be used to limit what protocols
// libcurl may use for this transfer, independent of what libcurl has been compiled
// to support. That may be useful if you accept the URL from an external source
// and want to limit the accessibility.
//
// The CURLOPT_URL stirng is ignored if CURLOPT_CURLU is set.
//
// Either CURLOPT_URL or CURLOPT_CURLU must be set before a transfer is started.
//
// The application does not keep the string around after setting this option.
//
// The parser used for handling the URL set with CURLOPT_URL is the same that
// curl_url_set uses.
//
// Encoding
// The string pointed to in the CURLOPT_URL argument is generally expected to be
// a sequence of characters using an ASCII compatible encoding.
//
// If libcurl is built with IDN support, the server name part of the URL can use
// an "international name" by using the current encoding (according to locale)
// or UTF-8 (when winidn is used; or a Windows Unicode build using libidn2).
//
// If libcurl is built without IDN support, the server name is used exactly as
// specified when passed to the name resolver functions.
//
// Security concerns
// Applications may at times find it convenient to allow users to specifiy URLs
// for various purposes and that string would then end up fed to this option.
//
// Getting a URL from an external untrusted party brings several security concerns:
//
// If you have an application that runs as or in a server application, getting
// unfiltered URL can easily trick your application to access a local resource
// instead of a remote. Protecting yourself againt localhost accesses is hard
// when accepting user provided URLs.
//
// Such custom URLs can also access other ports than you planned as port numbers
// are part of the regular URL format. The combination of a local host and a
// custom port number can allow external users to play tricks with your local
// services.
//
// Accepting external URLs may also use other protocols than http:// or other
// common ones. Restrict what accept with CURLOPT_PROTOCOLS/
//
// User provided URLs can also be made to point to sitees that redirect further
// on (possibly to other protocols too). Consider your CURLOPT_FOLLOWLOCATION
// and CURLOPT_REDIR_PROTOCOLS settings.
//
// Default
// There is no default URL. If this option is not set, no transfer can be performed.
//
// Protocols
// All
//
// Availability
// POP3 and SMTP were added in 7.31.0
//
// Return Value
// Return CURLE_OK (0) on success or CURLE_OUT_OF_MEMORY if there was
// insufficient heap space.
//
// Note that curel_easy_setopt does not parse the given string so given a bad URL,
// it is not detected until curl_easy_perform or similar is called.
//

#include <iostream>
#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://catfact.ninja/fact");
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    curl_easy_cleanup(curl);
  }

  return 0;
}

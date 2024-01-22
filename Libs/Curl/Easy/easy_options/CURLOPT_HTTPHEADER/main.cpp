// Name
// CURLOPT_HTTPHEADER - set of HTTP headers
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_HTTPHEADER, struct curl_slist *headers);
//
// Description
// Pass a pointer to a linked list of HTTP headers to pass to the server and/or proxy in your
// HTTP request. The same list can be used for both host and proxy requests!
//
// When used within an IMAP or SMTP request to upload a MIME mail, the given header list establishes
// the document-level MIME headers to prepend to the uploaded document described by CURLOPT_MIMEPOST.
// This does not affect raw mail uploads.
//
// The linked list should be a fully valid list of struct curl_slist struct properly filled in.
// Use curl_slist_append to create the list and curl_slist_free_all to clean up an entire list.
// If you add a header that is otherwise generated and used by libcurl internally, you added header
// is used instead. If you add a header with no content as in 'Accept:'(no data on the right side
// of the colon), the internally used header is disables/removed. With this option you can add new
// headers, replace internal headers and remove internal headers. To add a header with no content
// (nothing to the right side of the colon), use the form 'name;' (note the ending semicolon).
//
// The headers included in the linked list must not be CRLF-terminated, because libcurl adds CRFL
// after each header item itself. Failure to comply with this might result in strange behavior.
// libcurl passes on the verbatim strings you give it, without any filter or other safe guards.
// That includes white spaces and control characters.
//
// The first line in an HTTP request (containing the method, usually a GET or POST) is not a header
// and cannot be replaced using this option. Only the lines following the request-line are headers.
// Adding this method line in this list of headers only causes your request to send an invalid header.
// Use CURLOPT_CUSTOMREQUEST to change the method.
//
// When this option is passed to curl_easy_setopt, libcurl does not copy the entire list so you must
// keep it around until you no longer use this handle for a transfer before you call curl_slis_free_all
// on the list.
//
// Pass a NULL to this option to reset back to no custom headers.
//
// The most commonly replaced HTTP headers have "shortcuts" in the option CURLOPT_COOKIE,
// CURLOPT_USERAGENT and CURLOPT_REFERER. We recommend using those.
//
// There is an alternative option that sets or replaces headers only for requests that are sent with
// CONNECT to a proxy: CURLOPT_PROXYHEADER. Use CURLOPT_HEADEROPT to control the behavior.
//
// Specific http headers
// Setting some specific headers causes libcurl to act differently.
//    Host:
//      The specified host name is used for cookie matching if the cookie engine is also enabled
//      for this transfer. If the request is done over HTTP/2 or HTTP/3, the custom host name is
//      instead used in the ":authority" header field and Host: is not sent at all over the wire.
//
//    Transfer-Encoding: chuncked
//      Tells libcurl the upload is to be done using this chunked encoding instead of providing
//      the Content-Length: fiels in the request.
//
// Specific mime headers
// When used to build a MIME email for IMAP or SMTP, the following document-level header can be set
// to override libcurl-generated values:
//
//  Mime-Version:
//    Tells the parser at the receiving site how to interpret the MIME framing. It defaults to "1.0"
//    and should normally not be altered.
//
//  Content-Type:
//    Indicates the document's global structure type. By default, libcurl sets it to "multipart/mixed",
//    describing a document made of independent parts. When a MIME mail is only composed of alternative
//    representations of the same data (i.e.: HTML and plain text), this header must be set to
//    "multipart/alternative". In all cases the value must be of the form "multipart/*" to respect the
//    document structure and may not include the "boundary=" parameter.
//
//    Other specific headers that do not have a libcurl default value but are strongly desired by mail
//    delivery and user agents should also be included. These are "Form:", "To:", "Date:" and "Subject:"
//    among others and their presence and value is generally checked by anti-spam utilities.
//
// Security concerns
// By default, this option makes libcurl send the given headers in all HTTP requests done by this handle
// You should therefore use this option with caution if you for example connect to the remote site
// using a proxy and a CONNECT request, you should to consider if that proxy is supposed to also get
// the headers. They may be private or otherwise sensitive to leak.
//
// Use CURLOPT_HEADEROPT to make the headers only get sent to where you intend them to get sent.
//
// Custom headers are sent in all requests done by the easy handle, which implies that if you tell
// libcurl to follow redirects (CURLOPT_FOLLOWLOCATION), the same set of custom headers is sent in the
// subsequent request. Redirects can of course go to other hosts and thus those servers get all the
// contents of your cuestom headers too.
//
// Starting in 7.58.0, libcul specifically prevents "Authoriztion:" headers from being sent to other
// hosts than the first used one, unless specifically permitted with CURLOPT_UNRESTRICTED_AUTH option.
//
// Starting in 7.64.0 libcurl specifically prevents "Cookie:" headers from being sent to other hosts
// than the first used one, unless specifically permitted with the CURLOPT_UNRESTRICTED_AUTH option.
//
// Default
// NULL
// 
// Protocols
// HTTP, IMAP and SMTP
//
// Availability
// As long as HTTP is enabled. Use in MIME mail added in 7.56.0
//
// Return Value
// Returns CURLE_OK if HTTP is supported, and CURLE_UNKNOWN_OPTION if not.
//

#include <iostream>
#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  struct curl_slist *list = NULL;

  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://catfact.ninja/fact");
    
    list = curl_slist_append(list, "Test: 10");
    list = curl_slist_append(list, "Accept:");

    // Set the list of headers
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    curl_slist_free_all(list); // free the list
    curl_easy_cleanup(curl);
  }

  return 0;
}
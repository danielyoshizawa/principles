// Name
// CURLOPT_PROTOCOLS_STR - allowed protocols
//
// Synopsis
// #include <curl/curl.h>
// CURLcode curl_easy_setopt(CURL *handle, CURLOPT_PROTOCOLS_STR, char* spec);
//
// Description
// Pass a pointer to a string that holds a comma-separated list of case
// insensitive protocols names (URL schemes) to allow in the transfer.
// This option allows applications to use libcurl built to support a wide range
// of protocols but still limit specific transfers to only be allowed to use a
// subset of them. By default, libcurl accepts all protocols it was built with
// support for. See also CURLOPT_REDIR_PROTOCOLS_STR.
//
// If trying to set a non-existing protocol or if no matching protocol at all
// is set, it return error.
//
// There are the available protocols:
// DICT, FILE, FTP, FTPS, GOPHER, GOPHERS, HTTP, HTTPS, IMAP, IMAPS, LDAP,
// LDAPS, MQTT, POP3, POP3S, RTMP, RTMPE, RTMPS, RTMPT, RTMPTE, RTMPTS, RTSP,
// SCP, SFTP, SMB, SMBS, SMTP, SMTPS, TELNET, TFTP, WS, WSS
//
// You can set "ALL" as a short-cut to enable all protocols. Note that by
// setting all, you may enable protocols that were not supported the day you
// write this but are introduced in a future libcurl version.
//
// curl_version_info can be used to get a list of all supported protocols in the
// current libcurl.
// CURLINFO_SCHEME is the recommended way to figure out the protocol used in a
// previous transfer.
//
// Default
// All protocols built-in
//
// Protocols
// All
//
// Availability
// Added in 7.85.0
//
// Return Value
// Returns CURLE_UNKNOWN_OPTION if the option is not implemented,
// CURLE_UNSUPPORTED_PROTOCOL if a listed protocol is not supported or disables,
// CURLE_BAD_FUNCTION_ARGUMENT if no protocol is listed else CURLE_OK.
//

#include <iostream>
#include <curl/curl.h>

int main()
{
  CURL *curl = curl_easy_init();
  if (curl) {
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://catfact.ninja/fact");
    // Only allow HTTPS, TFTP and SFTP
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS_STR, "https,tftp,sftp");
    response = curl_easy_perform(curl);
    if (response)
    {
      std::cout << "## error : " << curl_easy_strerror(response) << std::endl;
    }
    curl_easy_cleanup(curl);
  }

  return 0;
}

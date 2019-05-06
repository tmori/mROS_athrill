#include "mros_packet_fmt_http.h"

const char* mros_packet_fmt_http_post =
		"POST /RPC2 HTTP/1.1\n"
		"Host: \n"
		"Accept-Encoding: \n"
		"User-Agent: \n"
		"Content-Type: \n"
		"Content-Length: %u\n"	/* ARG1: xml size */
		"\n%s";					/* ARG2: xml data */

const char* mros_packet_fmt_http_ok =
		"%u\n\n"		/* xml size */
		"HTTP/1.1 200 OK\n"
		"Host: \n"
		"Accept-Encoding: \n"
		"User-Agent: \n"
		"Content-Type: \n"
		"Content-Length: %u\n"	/* ARG1: xml size */
		"\n%s";					/* ARG2: xml data */


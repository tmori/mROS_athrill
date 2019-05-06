#ifndef _MROS_PACKET_FMT_HTTP_H_
#define _MROS_PACKET_FMT_HTTP_H_

/*
 * ARG1: xml size
 */
#define MROS_PACKET_FMT_HTTP_POST	\
	"POST /RPC2 HTTP/1.1\n"	\
	"Host: \n"				\
	"Accept-Encoding: \n"	\
	"User-Agent: \n"		\
	"Content-Type: \n"		\
	"Content-Length: %u\n\n"	\


/*
 * ARG1: xml size
 */
#define MROS_PACKET_FMT_HTTP_OK		\
		"%u\n\n"					\
		"HTTP/1.1 200 OK\n"			\
		"Host: \n"					\
		"Accept-Encoding: \n"		\
		"User-Agent: \n"			\
		"Content-Type: \n"			\
		"Content-Length: %u\n\n"		\

#endif /* _MROS_PACKET_FMT_HTTP_H_ */

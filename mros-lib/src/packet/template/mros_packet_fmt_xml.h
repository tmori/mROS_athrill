#ifndef _MROS_PACKET_FMT_XML_H_
#define _MROS_PACKET_FMT_XML_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ARGS1: method name
 * ARGS2: id
 * ARGS3: topic
 * ARGS4: type
 * ARGS5: uri
 */
#define MROS_PACKET_FMT_XML_REGISTER	\
	"<?xml version='1.0'?>\n"			\
	"<methodCall>\n"					\
	"<methodName>"						\
	"%s"								\
	"</methodName>\n"					\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%u" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%s" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%s" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%s" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"</methodCall>\n"

/*
 * ARGS1: method name
 * ARGS2: id
 * ARGS3: topic
 * ARGS4: tcpros
 */
#define MROS_PACKET_FMT_XML_REQUEST	\
	"<?xml version='1.0'?>\n"			\
	"<methodCall>\n"					\
	"<methodName>"						\
	"%s"								\
	"</methodName>\n"					\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%s" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"<params>\n"						\
	"<param>\n<value>"					\
	"%s" 								\
	"</value>\n</param>\n"				\
	"</params>"							\
	"<params>\n"						\
	"<param>\n<value>"					\
    "<array>\n<data><value><array>\n<data><value>"	\
    "%s"								\
    "</value></data>\n</array></value></data>\n</array>"	\
	"</value>\n</param>\n"				\
	"</params>"							\
	"</methodCall>\n"

#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_FMT_XML_H_ */

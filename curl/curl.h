#ifndef CURL_H
#define CURL_H

enum METHOD {
    GET,
    POST,
    HEAD
};

struct headers {
    enum METHOD method;
    char * path;
    char * version;
    char * host;
};

struct options {
    int port;
};

extern char * curl();

#endif
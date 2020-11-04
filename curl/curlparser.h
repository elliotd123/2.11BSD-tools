#ifndef CURLPARSER_H
#define CURLPARSER_H

#define MAXARGS 64

struct argument {
    char key;
    char* value;
};

struct argument * parse();

#endif
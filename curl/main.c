#include <stdlib.h>

#include "curl.h"
#include "curlparser.h"
#define MAXARGS 64

struct argument {
    char key;
    char* value;
};

int main(argc,argv) 
int argc;
char** argv;
{
    struct headers head;
    struct options opt;
    struct argument a[MAXARGS];
    char * body;
    int i;

    parse(argc,argv,a);

    opt.port = 80;
    head.method = GET;
    head.path = "/";

    for (i = 0; i < MAXARGS; i++) {
        if (a[i].key == '\0') {
            break;
        }
        
        switch (a[i].key) {
            case 'H':
            case 'h':
              head.host = a[i].value;
              break;
            case 'M':
            case 'm':
              /* Get method */
              if (strcmp(a[i].value,"GET") == 0) head.method = GET;
              if (strcmp(a[i].value,"POST") == 0) head.method = POST;
              if (strcmp(a[i].value,"HEAD") == 0) head.method = HEAD;
              break;
            case 'P':
            case 'p':
              head.path = a[i].value;
              break;
            case 'T':
            case 't':
              opt.port = atoi(a[i].value);
              break;
            case 'B':
            case 'b':
              body = a[i].value;
        }
    }

    curl(head,body,opt);
}
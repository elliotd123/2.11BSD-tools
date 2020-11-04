#include "curlparser.h"
#include <stdio.h>

struct argument * parse(argc,argv,a)
int argc;
char** argv;
struct argument * a;
{
    int i;
    int argnum;

    argnum = 0;
    for (i = 0; i < MAXARGS; i++) {
        struct argument arg;
        arg.key = '\0';
        arg.value = "";
        a[i] = arg;
    }

    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            struct argument arg;
            arg.key = argv[i][1];
            i++;
            arg.value = argv[i];
            a[argnum] = arg;
            argnum++;
        }
    }
}
#include "curlparser.h"
#include <stdio.h>

struct argument * parse(argc,argv,a)
int argc;
char** argv;
struct argument * a;
{
    int i;
    int j;
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
        } else {
            int found;
            found = 0;
            for (j = 0; j < MAXARGS; j++) {
                if (a[j].key == 'H' || a[j].key == 'h') {
                    a[j].value = argv[i];
                    found = 1;
                }
            }
            if (!found) {
                struct argument arg;
                arg.key = 'H';
                arg.value = argv[i];
                a[argnum] = arg;
                argnum++;
            }
        }
    }
}
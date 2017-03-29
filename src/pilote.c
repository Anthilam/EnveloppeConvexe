/*
  GUY Timothée , LAURENT Timothée
  Groupe TP2A - CMI
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vecset.h"
#include "convex.h"

#define BUFSIZE 1024

int main()
{
    setbuf(stdout, NULL); // avoids buffering in the output

    struct vecset * self = malloc(sizeof(struct vecset));
    struct vecset * out  = malloc(sizeof(struct vecset));
    vecset_create(self);
    vecset_create(out);

    char buffer[BUFSIZE];
    fgets(buffer, BUFSIZE, stdin);

    size_t count = strtol(buffer, NULL, 10);

    for (size_t i = 0; i < count; ++i) {
        struct vec p;

        fgets(buffer, BUFSIZE, stdin);

        char * endptr = buffer;
        p.x = strtod(endptr, &endptr);
        p.y = strtod(endptr, &endptr);

        vecset_add(self, p);
    }
	// Uncomment the algorithm you want to use and comment the others  :
    jarvis_march(self, out);
    //graham_scan(self, out)
    //quickhull(self, out);
    //------------------------------------------------------------------

    //Prints the output : 
    printf("%lu\n", out->size);
    vecset_dump(out);

    return 0;
}

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

int main() {
	setbuf(stdout, NULL); // avoid buffering in the output

	char buffer[BUFSIZE];
	fgets(buffer, BUFSIZE, stdin);

	size_t count = strtol(buffer, NULL, 10);

	printf("%lu\n", count);
	for (size_t i = 0; i < count; ++i) {
		struct vec p;

		fgets(buffer, BUFSIZE, stdin);

		char *endptr = buffer;
		p.x = strtod(endptr, &endptr);
		p.y = strtod(endptr, &endptr);

		printf("%f %f\n", p.x, p.y);
		// then do something with p
	}

	return 0;
}

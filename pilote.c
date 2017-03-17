#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "vecset.h"
#include "convex.h"

#define BUFSIZE 1024
// Timothée LAURENT - Timothée GUY

int main() {
	setbuf(stdout, NULL); // avoid buffering in the output
	char buffer[BUFSIZE];
	fgets(buffer, BUFSIZE, stdin);
	size_t count = strtol(buffer, NULL, 10);
	for (size_t i = 0; i < count; ++i) {
		struct vec p;
		fgets(buffer, BUFSIZE, stdin);
		char *endptr = buffer;
		p.x = strtod(endptr, &endptr);
		p.y = strtod(endptr, &endptr);
		// then do something with p
	}
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vecset.h"
#include "convex.h"

// Timothée LAURENT - Timothée GUY

void jarvis_march(const struct vecset *in, struct vecset *out) {
	struct vecset R = malloc(struct vecset());
	struct vec first = malloc(struct vec());
	struct vec next = malloc(struct vec());
	first = vecset_min(in, compare_min, NULL);
	struct vec current = first;

	do {
		vecset_add(R, current);
		next = vecset_random(in); 
		for (int i = 0; i < in->size; i++) {
			if (is_left_turn(current, in->data[i], next)) {
				next = in->data[i]			
			}
		}
		current = next;
	} while (first == current);
	return R;
}

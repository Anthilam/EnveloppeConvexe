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

void jarvis_march(const struct vecset *in, struct vecset *out) {
								assert(in);
								assert(out);

								// first est le point le plus à droite
								const struct vec *first = malloc(sizeof(struct vec));
								first = vecset_min(in, &compare_x, NULL);

								// current est le point courant
								struct vec *current = malloc(sizeof(struct vec));
								*current = *first;

								int j = 0;
								do {
																vecset_add(out, *current);
																struct vec *next = malloc(sizeof(struct vec));
																next = &in->data[j];

																for (int i = 0; i < in->size; i++) {
																								if (is_left_turn(current, &in->data[i], next)) {
																																next = &in->data[i];
																								}
																}
																current = next;
																++j;
								} while (first != current);
}

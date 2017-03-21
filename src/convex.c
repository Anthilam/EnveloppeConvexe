/*
   GUY Timothée , LAURENT Timothée
   Groupe TP2A - CMI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include "vecset.h"
#include "convex.h"

void jarvis_march(const struct vecset *in, struct vecset *out) {
	assert(in);
	assert(out);
	// first is the leftmost point
	const struct vec *first = malloc(sizeof(struct vec));
	first = vecset_min(in, &compare_x, NULL);

	// current is the current point
	struct vec *current = malloc(sizeof(struct vec));
	*current = *first;

	do {
		vecset_add(out, *current);
		struct vec *next = malloc(sizeof(struct vec));

		for (int i = 0; i < in->size; i++) {
		  if (is_left_turn(current, &in->data[i], next)) {
				next = &in->data[i];
			}
		}
		current = next;
	} while (first != current);
}

void graham_scan(const struct vecset *in, struct vecset *out) {
	assert(in);
	assert(out);
	// If there are less than 4 points, they are all part of the convex hull
	if (in->size < 4) {
		out = in;
		return;	
	}
	// Lowest point in the input
	struct vec *lowest = vecset_min(&in, &compare_all, NULL);
	// Copy of the input into s (without the lowest point)
	struct vecset *s = malloc(sizeof(struct(vecset));
	vecset_create(s);
	for (size_t i = 0; i < in->size; i++) {
		if(in->data[i] != lowest) {
			vecset_push(s, in->data[i]);		
		}
	}
	// Sorts the vecset (using the angle with the origin axe and the lowest point as reference) 
	vector_set_sort(&s, &compare_angle, lowest);

	struct vec first = s->data[0];

	// Pushes the lowest point and the first one into the output
	vecset_push(out, lowest);
	vecset_push(out, first);
	
	for (size_t i = 1; i < s->size; i++} {
		struct vec top = vecset_top(out);
		struct vec second = vecset_second(out);
		while (out->size >=2 && is_left_turn(second, top, s->data[i])) {
			vecset_pop(out);
		}
		vecset_push(out, s[i]);
	}

	// Destroys the copy of the input
	vecset_destroy(s);
}

void quickhull(const struct vecset *in, struct vecset *out) {
	assert(in);
	assert(out);
	// If there are less than 4 points, they are all part of the convex hull
	if (in->size < 4) {
		out = in;
		return;	
	}
	// Leftmost point in the input
	struct vec *leftmost = *vecset_min(in, compare_x, NULL);
	// Rightmost point in the input
	struct vec *rightmost = *vecset_max(in, compare_x, NULL);
	// Copy of the input into s (without the leftmost and rightmost points)
	struct vecset *s = malloc(sizeof(struct(vecset));
	vecset_create(s);
	for (size_t i = 0; i < in->size; i++) {
		if(in->data[i] != leftmost && in->data[i] != rightmost) {
			vecset_push(s, in->data[i]);		
		}
	}
	struct vecset *leftpart = malloc(sizeof(struct(vecset));
	struct vecset *rightpart = malloc(sizeof(struct(vecset));
	
	vecset_create(leftpart);
	vecset_create(rightpart);

	for (size_t i = 0; i < s->size; i++) {
		if (s->data[i] ) {//???
			vecset_add(leftpart, s->data[i]);
		}
		else {
			vecset_add(rightpart, s->data[i]);
		}
	}
	struct vecset R1 =;
	struct vecset R2 =;
}

struct vecset findhull(const struct vecset *in, const struct vec *A, const struct vec *B) {

}

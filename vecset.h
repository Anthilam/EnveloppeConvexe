#ifndef VECSET_H
#define VECSET_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
// Timothée LAURENT - Timothée GUY

/* 
  This header contains the functions related to vecsets (sets of vectors)
  defined in the strutures below 
*/

struct vec {
	double x;
	double y;
};

struct vecset {
	struct vec *data;
	size_t size;
	size_t capacity;
};

// creates a set of vectors 
void vecset_create(struct vecset *self);

// destroys a set of vectors
void vecset_destroy(struct vecset *self);

// adds a vector to a set of vectors
void vecset_add(struct vecset *self, struct vec p);

// pushes an element on top of the pile
void vecset_push(struct vecset *self, struct vec p);

// pops an element out of top of the pile
void vecset_pop(struct vecset *self);

// returns the first element of the pile
const struct vec *vecset_top(const struct vecset *self);

// returns the second element of the pile
const struct vec *vecset_second(const struct vecset *self);

// calculates the dot product of 2 vectors
double dot(const struct vec *v1, const struct vec *v2);

// calculates the cross product of 3 vectors
double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3);

// determinates if 2 vectors are forming a left or a right turn
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3);

// returns the max vector of a set of vectors
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx);

// returns the min vector of a set of vectors
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx);

// sorts a set of vectors
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);

// compares two vectors
typedef int *(comp_func_t)(struct vec *p1, const struct vec *p2, const void *ctx);

const struct vec *vecset_random(const struct vecset *self);
#endif

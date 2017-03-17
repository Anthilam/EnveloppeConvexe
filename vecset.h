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

//---STRUCTURES-----------------------------------------------------------------

struct vec {
	double x;
	double y;
};

struct vecset {
	struct vec *data;
	size_t size;
	size_t capacity;
};

//---TYPEDEF--------------------------------------------------------------------

// Typedef of functions that compare two vectors with/without a context
typedef int *(comp_func_t)(struct vec *p1, const struct vec *p2, const void *ctx);

//---FUNCTIONS------------------------------------------------------------------

// Calculates the dot product of 2 vectors
double dot(const struct vec *v1, const struct vec *v2);

// Calculates the cross product of 3 vectors
double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3);

// Determinates if two vectors are forming a left or a right turn
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3);

// Create a vector
void vec_create(struct vec *self, double x, double y);

// Destroy a vector
void vec_destroy(struct vec *self);

// Print a vector
void vec_dump(const struct vec *self);

// Creates a set of vectors
void vecset_create(struct vecset *self);

// Destroys a set of vectors
void vecset_destroy(struct vecset *self);

// Print a set of vectors
void vecset_dump(const struct vecset *self);

// Adds a vector to a set of vectors
void vecset_add(struct vecset *self, struct vec p);

// Pushes an element on top of the pile
void vecset_push(struct vecset *self, struct vec p);

// Pops the element at the top of the pile
void vecset_pop(struct vecset *self);

// Returns the first element of the pile
const struct vec *vecset_top(const struct vecset *self);

// Returns the second element of the pile
const struct vec *vecset_second(const struct vecset *self);

// Returns the max vector of a set of vectors
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx);

// Returns the min vector of a set of vectors
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx);

// Sorts a set of vectors
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);

// Generates a random vecset
const struct vec *vecset_random(const struct vecset *self);

#endif

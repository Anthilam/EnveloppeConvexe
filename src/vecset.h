/*
   GUY Timothée , LAURENT Timothée
   Groupe TP2A - CMI
 */

#ifndef VECSET_H
#define VECSET_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

/*
   This header contains the functions related to vecsets (sets of vectors)
   defined in the strutures below
 */

//---STRUCTURES-----------------------------------------------------------------
/* vec structure: represents a vector */
struct vec {
	double x;
	double y;
}; 

/* vecset structure: represents a set vectors */
struct vecset {
	struct vec *data;
	size_t size;
	size_t capacity;
};

//---COMPARE--------------------------------------------------------------------

// Typedef of functions that compare two vectors with/without a context
typedef int (*comp_func_t)(const struct vec *p1, const struct vec *p2, const void *ctx);

/* Compares two vectors using their x coordinates */
int compare_x(const struct vec *p1, const struct vec *p2, const void *ctx);

/* Compares two vectors by their y coordinates */
int compare_y(const struct vec *p1, const struct vec *p2, const void *ctx);

/* Compares two vectors by their most left-bottomness */
int compare_left_bottom(const struct vec *p1, const struct vec *p2, const void *ctx);

/* Compares two vectors using their y coordinates first and then their x coordinates */
int compare_all(const struct vec *p1, const struct vec *p2, const void *ctx);

/* Compares two vectors based on their angle with the origin axis */
int compare_angle(const struct vec *p1, const struct vec *p2, const void *ctx);

//---FUNCTIONS------------------------------------------------------------------

/* Calculates the dot product of 2 vectors */
double dot(const struct vec *v1, const struct vec *v2);

/* Calculates the cross product of 3 vectors */
double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3);

/* Determinates if two vectors are forming a left or a right turn */
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3);

/* Create a vector */
void vec_create(struct vec *self, double x, double y);

/* Destroys a vector */
void vec_destroy(struct vec *self);

/* Prints a vector */
void vec_dump(const struct vec *self);

/* Creates a set of vectors */
void vecset_create(struct vecset *self);

/* Destroys a set of vectors */
void vecset_destroy(struct vecset *self);

/* Prints a set of vectors */
void vecset_dump(const struct vecset *self);

/* Adds a vector to a set of vector */
void vecset_add(struct vecset *self, struct vec p);

/* Pushes an element on top of the pile */
void vecset_push(struct vecset *self, struct vec p);

/* Pops the element at the top of the pile */
void vecset_pop(struct vecset *self);

/* Returns the first element of the pile */
const struct vec *vecset_top(const struct vecset *self);

/* Returns the second element of the pile */
const struct vec *vecset_second(const struct vecset *self);

/* Returns the max vector of a set of vectors */
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx);

/* Returns the min vector of a set of vectors */
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx);

/* Sorts a set of vectors */
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);

//---FUNCTIONS RELATED TO vector_set_sort---------------------------------------
/* Creates a partition in the vecset */
long vector_partition(struct vecset *self, long i, long j, comp_func_t func, const void *ctx);

/* Swaps two vectors in a vecset */
void vector_swap(struct vecset *self, size_t i, size_t j);

/* Quick sort function, used in vector_set_sort */
void vector_quick_sort_partial(struct vecset *data, long i, long j, comp_func_t func, const void *ctx);

#endif

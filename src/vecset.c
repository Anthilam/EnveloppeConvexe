/*
  GUY Timothée , LAURENT Timothée
  Groupe TP2A - CMI
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "vecset.h"

/*---FUNCTIONS----------------------------------------------------------------*/

/* Calculates the dot product of 2 vectors */
double dot(const struct vec * v1, const struct vec * v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

/* Calculates the cross product of 3 vectors */
double cross(const struct vec * v1, const struct vec * v2, const struct vec * v3)
{
    return ((v2->x - v1->x) * (v3->y - v1->y)) - ((v2->y - v1->y) * (v3->x - v1->x));
}

/* Determinates if two vectors are forming a left or a right turn */
bool is_left_turn(const struct vec * p1, const struct vec * p2, const struct vec * p3)
{
    return cross(p1, p2, p3) > 0;
}

/* Create a vector */
void vec_create(struct vec * self, double x, double y)
{
    self->x = x;
    self->y = y;
}

/* Destroys a vector */
void vec_destroy(struct vec * self)
{
    free(self);
}

/* Prints a vector */
void vec_dump(const struct vec * self)
{
    printf("%f %f\n", self->x, self->y);
}

/* Creates a set of vectors */
void vecset_create(struct vecset * self)
{
    assert(self);
    self->data     = malloc(6 * sizeof(struct vec));
    self->capacity = 6;
    self->size     = 0;
}

/* Destroys a set of vectors */
void vecset_destroy(struct vecset * self)
{
    assert(self);
    free(self->data);
    free(self);
}

/* Prints a set of vectors */
void vecset_dump(const struct vecset * self)
{
    for (int i = 0; i < self->size; ++i) {
        vec_dump(&self->data[i]);
    }
    printf("\n");
}

/* Adds a vector to a set of vector */
void vecset_add(struct vecset * self, struct vec p)
{
    if (self->size == self->capacity) {
        self->capacity = self->capacity * 2;
        struct vec * data = calloc(self->capacity, sizeof(struct vec));
        memcpy(data, self->data, self->size * sizeof(struct vec));
        free(self->data);
        self->data = data;
    }
    self->data[self->size] = p;
    ++self->size;
}

/* Pushes an element on top of the pile */
void vecset_push(struct vecset * self, struct vec p)
{
    assert(self);
    vecset_add(self, p);
}

/* Pops the element at the top of the pile */
void vecset_pop(struct vecset * self)
{
    assert(self);
    struct vec * data = calloc(self->capacity, sizeof(struct vec));
    memcpy(data, self->data, (self->size - 1) * sizeof(struct vec));
    free(self->data);
    self->data = data;
    --self->size;
}

/* Returns the first element of the pile */
const struct vec * vecset_top(const struct vecset * self)
{
    assert(self);
    return &self->data[self->size - 1];
}

/* Returns the second element of the pile */
const struct vec * vecset_second(const struct vecset * self)
{
    assert(self);
    return &self->data[self->size - 2];
}

/* Compares two vectors using their x coordinates */
int compare_x(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (p1->x < p2->x) {
        return -1;
    } else if (p1->x > p2->x) {
        return 1;
    }
    return 0;
}

/* Compares two vectors by their y coordinates */
int compare_y(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (p1->y < p2->y) {
        return -1;
    } else if (p1->y > p2->y) {
        return 1;
    }
    return 0;
}

/* Compares two vectors by their most left-bottomness */
int compare_left_bottom(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (compare_x(p1, p2, ctx) == 1) {
        return 1;
    } else if (compare_x(p1, p2, ctx) == 0 && compare_y(p1, p2, ctx) == 1) {
        return 1;
    } else if (compare_x(p1, p2, ctx) == -1) {
        return -1;
    }
    return 0;
}

/* Compares two vectors using their y coordinates first and then their x coordinates */
int compare_all(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (p1->y < p2->y) {
        return -1;
    } else if (p1->y > p2->y) {
        return 1;
    }
    compare_x(p1, p2, ctx);
    return 0;
}

/* Compares two vectors based on their angle with the origin axis */
int compare_angle(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    assert(ctx);
    assert(p1);
    assert(p2);
    const struct vec * ref = ctx;

    double dp1X = p1->x - ref->x;
    double dp1Y = p1->y - ref->y;

    double dp2X = p2->x - ref->x;
    double dp2Y = p2->y - ref->y;

    double ap1 = atan2(dp1X, dp1Y);
    double ap2 = atan2(dp2X, dp2Y);

    if (ap1 > ap2) {
        return 1;
    }
    if (ap1 < ap2) {
        return -1;
    }
    return compare_all(p1, p2, ctx);
}

/* Returns the max vector of a set of vectors */
const struct vec * vecset_max(const struct vecset * self, comp_func_t func, const void * ctx)
{
    struct vec * res = &self->data[0];

    for (size_t i = 1; i < self->size; ++i) {
        int test = func(res, &self->data[i], &ctx);
        if (test == -1) {
            res = &self->data[i];
        }
    }
    return res;
}

/* Returns the min vector of a set of vectors */
const struct vec * vecset_min(const struct vecset * self, comp_func_t func, const void * ctx)
{
    struct vec * res = &self->data[0];

    for (size_t i = 1; i < self->size; ++i) {
        int test = func(res, &self->data[i], &ctx);
        if (test == 1) {
            res = &self->data[i];
        }
    }
    return res;
}

/* Sorts a set of vectors */
void vector_set_sort(struct vecset * self, comp_func_t func, const void * ctx)
{
    long n = self->size;

    vector_quick_sort_partial(self, 0, n - 1, func, ctx);
}

/* Swaps two vectors in a vecset */
void vector_swap(struct vecset * self, size_t i, size_t j)
{
    struct vec tmp = self->data[i];

    self->data[i] = self->data[j];
    self->data[j] = tmp;
}

/* Creates a partition in the vecset */
long vector_partition(struct vecset * self, long i, long j, comp_func_t func, const void * ctx)
{
    long pivot_index       = i;
    const struct vec pivot = self->data[pivot_index];

    vector_swap(self, pivot_index, j);
    long l = i;
    for (long k = i; k < j; ++k) {
        if (func(&self->data[k], &pivot, ctx) == -1) {
            vector_swap(self, k, l);
            l++;
        }
    }
    vector_swap(self, l, j);
    return l;
}

/* Quick sort function, used in vector_set_sort */
void vector_quick_sort_partial(struct vecset * data, long i, long j, comp_func_t func, const void * ctx)
{
    if (i < j) {
        long p = vector_partition(data, i, j, func, ctx);
        vector_quick_sort_partial(data, i, p - 1, func, ctx);
        vector_quick_sort_partial(data, p + 1, j, func, ctx);
    }
}


/*
 *  GUY Timothée , LAURENT Timothée
 *  Groupe TP2A - CMI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "vecset.h"

/*---FUNCTIONS----------------------------------------------------------------*/

/* Calculates the dot product of 2 vectors
 * Test = OK */
double dot(const struct vec * v1, const struct vec * v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

/* Calculates the cross product of 3 vectors
 * Test = OK */
double cross(const struct vec * v1, const struct vec * v2, const struct vec * v3)
{
    return ((v2->x - v1->x) * (v3->y - v1->y)) - ((v2->y - v1->y) * (v3->x - v1->x));
}

/* Determinates if two vectors are forming a left or a right turn
 * TEST = OK */
bool is_left_turn(const struct vec * p1, const struct vec * p2, const struct vec * p3)
{
    return cross(p1, p2, p3) > 0;
}

/* Create a vector
 * Test = OK */
void vec_create(struct vec * self, double x, double y)
{
    self->x = x;
    self->y = y;
}

/* Destroy a vector
 * Test = OK */
void vec_destroy(struct vec * self)
{
    free(self);
}

/* Print a vector
 * Test = OK */
void vec_dump(const struct vec * self)
{
    printf("%f %f\n", self->x, self->y);
}

/* Creates a set of vectors
 * Test = OK */
void vecset_create(struct vecset * self)
{
    self->data     = NULL;
    self->capacity = 0;
    self->size     = 0;
}

/* Destroys a set of vectors
 * Test = OK */
void vecset_destroy(struct vecset * self)
{
    assert(self);
    free(self->data);
    free(self);
}

/* Print a set of vectors
 * Test = OK */
void vecset_dump(const struct vecset * self)
{
    for (int i = 0; i < self->size; ++i) {
        vec_dump(&self->data[i]);
    }
    printf("\n");
}

/* Adds a vector to a set of vector
 * Test = OK */
void vecset_add(struct vecset * self, struct vec p)
{
    if (self->size == self->capacity) {
        ++self->capacity;
        struct vec * data = calloc(self->capacity, sizeof(struct vec));
        memcpy(data, self->data, self->size * sizeof(struct vec));
        free(self->data);
        self->data = data;
    }
    self->data[self->size] = p;
    ++self->size;
}

/* Pushes an element on top of the pile
 * Test = OK */
void vecset_push(struct vecset * self, struct vec p)
{
    assert(self);
    vecset_add(self, p);
}

/* Pops the element at the top of the pile
 * Test = OK */
void vecset_pop(struct vecset * self)
{
    assert(self);
    struct vec * data = calloc(self->capacity, sizeof(struct vec));
    memcpy(data, self->data, (self->size - 1) * sizeof(struct vec));
    free(self->data);
    self->data = data;
    --self->size;
}

/* Returns the first element of the pile
 * Test = OK */
const struct vec * vecset_top(const struct vecset * self)
{
    assert(self);
    return &self->data[self->size - 1];
}

/* Returns the second element of the pile
 * Test = OK */
const struct vec * vecset_second(const struct vecset * self)
{
    assert(self);
    return &self->data[self->size - 2];
}

/* Compare two vectors by their x coordinates
 * Test = OK */
int compare_x(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (p1->x < p2->x) {
        return -1;
    } else if (p1->x > p2->x) {
        return 1;
    }
    return 0;
}

/* Returns the max vector of a set of vectors
 * Test = OK */
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

/* Returns the min vector of a set of vectors
 * Test = OK */
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

/* Returns a random vector of the vecset in, not already present in the vecset out
 * Test = OK */
void vec_random(struct vec * self, const struct vecset * in, struct vecset * out)
{
    srand(time(NULL));
    int n = (int) (rand() % in->size)-1;

    self->x = in->data[n].x;
    self->y = in->data[n].y;
}

/* Sorts a set of vectors
 * Test = ? */
void vector_set_sort(struct vecset * self, comp_func_t func, const void * ctx);

/*int main() {
 *      struct vecset *set = malloc(sizeof(struct vecset));
 *      struct vecset *set2 = malloc(sizeof(struct vecset));
 *
 *      struct vec *v = malloc(sizeof(struct vec));
 *      struct vec *v1 = malloc(sizeof(struct vec));
 *      struct vec *v2 = malloc(sizeof(struct vec));
 *      struct vec *v3 = malloc(sizeof(struct vec));
 *      struct vec *v4 = malloc(sizeof(struct vec));
 *      struct vec *v5 = malloc(sizeof(struct vec));
 *      struct vec *v6 = malloc(sizeof(struct vec));
 *
 *      vecset_create(set);
 *      vecset_create(set2);
 *
 *      vec_create(v,3,4);
 *      vec_create(v1,2,1);
 *      vec_create(v2,5,6);
 *      vec_create(v3,8,1);
 *      vec_create(v4,5,8);
 *      vec_create(v5,12,4);
 *      vec_create(v6,9,7);
 *
 *      vecset_add(set, *v);
 *      vecset_add(set, *v1);
 *      vecset_add(set, *v2);
 *      vecset_add(set, *v3);
 *      vecset_add(set, *v4);
 *      vecset_add(set, *v5);
 *      vecset_add(set, *v6);
 *
 *      vecset_add(set2, *v4);
 *      vecset_add(set2, *v5);
 *      vecset_add(set2, *v6);
 *
 *      vecset_dump(set);
 *      vecset_dump(set2);
 *
 *      struct vec *res = malloc(sizeof(struct vec));
 *      res = vec_random(set, set2);
 *      vec_dump(res);
 * }*/

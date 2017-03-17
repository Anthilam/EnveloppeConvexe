#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vecset.h"
// Timothée LAURENT - Timothée GUY

double dot(const struct vec *v1, const struct vec *v2) {
        return (v1->x*v2->x + v1->y*v2->y);
}

double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3) {
        return (((v2->x - v1->x) * (v3->y - v1->y)) - ((v2->y - v1->y)*(v3->x - v1->x)));
}

void vecset_push(struct vecset *self, struct vec p) {
        assert(self);
        vecset_add(self, p);
}

void vecset_pop(struct vecset *self) {
        assert(self);
        free(self[self->size-1]);
        self->size -= 1;
}

const struct vec *vecset_top(const struct vecset *self) {
        assert(self);
        return self[self->size-1];
}

const struct vec *vecset_second(const struct vecset *self) {
        assert(self);
        return self[self->size-2];
}

bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3) {
        return (cross(p1, p2, p3) > 0);
}

// Creates a set of vectors
void vecset_create(struct vecset *self) {
        self->data = NULL;
        self->capacity = 0;
        self->size = 0;
}

// Destroys a set of vectors
void vecset_destroy(struct vecset *self) {
        if (self != NULL)
        {
                free(self->data);
        }
}

// Adds a vector to a set of vector
void vecset_add(struct vecset *self, struct vec p) {
        if (self->size == self->capacity)
        {
                ++self->capacity;
                struct vec *data = calloc(self->capacity, sizeof( struct vec));
                memcpy(data, self->data, self->size * sizeof(struct vec));
                free(self->data);
                self->data = data;
        }
        self->data[self->size] = p;
        ++self->size;
}

// Compares two vectors
typedef int *(comp_func_t)(struct vec *p1, const struct vec *p2, const void *ctx);

// Returns the max vector of a set of vectors
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx) {
        struct vec *res = &self->data[0];
        for (size_t i = 0; i < self->size; ++i) {
                int test = *func(res, &self->data[i], &ctx);
                if (test < 0) {
                        res = &self->data[i];
                }
        }
        return res;
}

// Returns the min vector of a set of vectors
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx) {
        struct vec *res = &self->data[0];
        for (size_t i = 0; i < self->size-1; ++i) {
                int test = *func(res, &self->data[i], &ctx);
                if (test > 0) {
                        res = &self->data[i];
                }
        }
        return res;
}

// Sorts a set of vectors
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);


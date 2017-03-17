#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vecset.h"
// Timothée LAURENT - Timothée GUY

//---FUNCTIONS------------------------------------------------------------------

// Calculates the dot product of 2 vectors
// Test = OK
double dot(const struct vec *v1, const struct vec *v2) {
        return v1->x*v2->x+v1->y*v2->y;
}

// Calculates the cross product of 3 vectors
// Test = OK
double cross(const struct vec *v1, const struct vec *v2, const struct vec *v3) {
        return ((v2->x-v1->x)*(v3->y-v1->y))-((v2->y-v1->y)*(v3->x-v1->x));
}

// Determinates if two vectors are forming a left or a right turn
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3) {
        return cross(p1, p2, p3) > 0;
}

// Create a vector
// Test = OK
void vec_create(struct vec *self, double x, double y) {
        self->x = x;
        self->y = y;
}

// Destroy a vector
// Test = OK
void vec_destroy(struct vec *self) {
        free(self);
}

// Print a vector
// Test = OK
void vec_dump(const struct vec *self) {
        printf("(%f, %f)\n", self->x, self->y);
}

// Creates a set of vectors
// Test = OK
void vecset_create(struct vecset *self) {
        self->data = NULL;
        self->capacity = 0;
        self->size = 0;
}

// Destroys a set of vectors
// Test = OK
void vecset_destroy(struct vecset *self) {
        if (self != NULL)
        {
                free(self);
        }
}

// Print a set of vectors
// Test = OK
void vecset_dump(const struct vecset *self){
        for (int i = 0; i < self->size; ++i)
        {
                vec_dump(&self->data[i]);
        }
        printf("\n");
}

// Adds a vector to a set of vector
// Test = PAS OK, il manque un free sur le data
void vecset_add(struct vecset *self, struct vec p) {
        if (self->size == self->capacity)
        {
                ++self->capacity;
                struct vec *data = calloc(self->capacity, sizeof(struct vec));
                memcpy(data, self->data, self->size * sizeof(struct vec));
                free(self->data);
                self->data = data;
        }
        self->data[self->size] = p;
        ++self->size;
}

// Pushes an element on top of the pile
// Test = OK
void vecset_push(struct vecset *self, struct vec p) {
        assert(self);
        vecset_add(self, p);
}

// Pops the element at the top of the pile
// Test = A REFAIRE
void vecset_pop(struct vecset *self) {
        assert(self);
}

// Returns the first element of the pile
// Test = OK
const struct vec *vecset_top(const struct vecset *self) {
        assert(self);
        return &self->data[self->size-1];
}

// Returns the second element of the pile
// Test = OK
const struct vec *vecset_second(const struct vecset *self) {
        assert(self);
        return &self->data[self->size-2];
}

// Returns the max vector of a set of vectors
// Test = ?
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
// Test = ?
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
// Test = ?
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);

// Generates a random vecset
// Test = ?
const struct vec *vecset_random(const struct vecset *self);

//---MAIN (DEBUG)---------------------------------------------------------------

int main(int argc, char *argv[]) {
        struct vecset *set = malloc(sizeof(struct vecset));
        struct vec *w = malloc(sizeof(struct vec));
        struct vec *u = malloc(sizeof(struct vec));
        struct vec *v = malloc(sizeof(struct vec));
        struct vec *z = malloc(sizeof(struct vec));

        vec_create(w, 2, 3);
        vec_create(u, 5, 6);
        vec_create(v, 3, 3);
        vec_create(z, 4, 8);
        vecset_create(set);

        vecset_add(set, *w);
        vecset_add(set, *u);
        vecset_add(set, *v);
        vecset_push(set, *z);
        vecset_dump(set);

        const struct vec *p = vecset_top(set);
        vec_dump(p);
        p = vecset_second(set);
        vec_dump(p);

        vecset_destroy(set);
        vec_destroy(w);
        vec_destroy(v);
        vec_destroy(u);

        return 0;
}

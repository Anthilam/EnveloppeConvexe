#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct vec {
        double x;
        double y;
};

struct vecset {
        struct vec *data;
        size_t size;
        size_t capacity;
};

// Create a set of vector
void vecset_create(struct vecset *self) {
        self->data = NULL;
        self->capacity = 0;
        self->size = 0;
}

// Destroy a set of vector
void vecset_destroy(struct vecset *self) {
        if (self != NULL)
        {
                free(self->data);
        }
}

// Add a vector to a set of vector
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

// Compare two vectors
typedef int *(comp_func_t)(struct vec *p1, const struct vec *p2, const void *ctx);

// Return the max vector of a set of vector
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

// Return the min vector of a set of vector
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx) {
        struct vec *res = &self->data[0];
        for (size_t i = 0; i < self->size; ++i) {
                int test = *func(res, &self->data[i], &ctx);
                if (test > 0) {
                        res = &self->data[i];
                }
        }
        return res;
}

// Sort a set of vector
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx);

int main(int argc, char *argv[])
{















}

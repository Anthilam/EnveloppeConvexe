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

/* Calculates the dot product of 2 vectors
   Test = OK */
double dot(const struct vec *v1, const struct vec *v2) {
        return v1->x*v2->x+v1->y*v2->y;
}

/* Calculates the cross product of 3 vectors
   Test = OK */
double cross(const struct vec *v1, const struct vec *v2, const struct vec *v3) {
	return ((v2->x-v1->x)*(v3->y-v1->y))-((v2->y-v1->y)*(v3->x-v1->x));
}

/* Determinates if two vectors are forming a left or a right turn
   TEST = OK */
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3) {
        return cross(p1, p2, p3) > 0;
}

/* Create a vector
   Test = OK */
void vec_create(struct vec *self, double x, double y) {
        self->x = x;
        self->y = y;
}

/* Destroy a vector
   Test = OK */
void vec_destroy(struct vec *self) {
        free(self);
}

/* Print a vector
   Test = OK */
void vec_dump(const struct vec *self) {
        printf("%f %f\n", self->x, self->y);
}

/* Creates a set of vectors
   Test = OK */
void vecset_create(struct vecset *self) {
	assert(self);
        self->data = malloc(6*sizeof(struct vec));
        self->capacity = 6;
        self->size = 0;
}

/* Destroys a set of vectors
   Test = OK */
void vecset_destroy(struct vecset *self) {
        assert(self);
        free(self->data);
        free(self);
}

/* Print a set of vectors
   Test = OK */
void vecset_dump(const struct vecset *self){
        for (int i = 0; i < self->size; ++i)
        {
                vec_dump(&self->data[i]);
        }
        printf("\n");
}

/* Adds a vector to a set of vector
   Test = OK */
void vecset_add(struct vecset *self, struct vec p) {


        if (self->size == self->capacity)
        {
                self->capacity = self->capacity*2 ;
                struct vec *data = calloc(self->capacity, sizeof(struct vec));
                memcpy(data, self->data, self->size * sizeof(struct vec));
                free(self->data);
                self->data = data;
        }
        self->data[self->size] = p;
        ++self->size;
}

/* Pushes an element on top of the pile
   Test = OK */
void vecset_push(struct vecset *self, struct vec p) {
        assert(self);
        vecset_add(self, p);
}

/* Pops the element at the top of the pile
   Test = OK */
void vecset_pop(struct vecset *self) {
        assert(self);
        struct vec *data = calloc(self->capacity, sizeof(struct vec));
        memcpy(data, self->data, (self->size-1) * sizeof(struct vec));
        free(self->data);
        self->data = data;
        --self->size;
}

/* Returns the first element of the pile
   Test = OK */
const struct vec *vecset_top(const struct vecset *self) {
        assert(self);
        return &self->data[self->size-1];
}

/* Returns the second element of the pile
   Test = OK */
const struct vec *vecset_second(const struct vecset *self) {
        assert(self);
        return &self->data[self->size-2];
}

/* Compares two vectors using their x coordinates
   Test = OK */
int compare_x(const struct vec *p1, const struct vec *p2, const void *ctx) {
        if (p1->x < p2->x) {
                return -1;
        }
        else if (p1->x > p2->x) {
                return 1;
        }
        return 0;
}

/* Compare two vectors by their y coordinates
 * Test = OK */
int compare_y(const struct vec * p1, const struct vec * p2, const void * ctx)
{
    if (p1->y < p2->y) {
        return -1;
    } else if (p1->y > p2->y) {
        return 1;
    }
    return 0;
}

/* Compares two vectors by their most left-bottomness
 * Test = OK */
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

/* Compares two vectors using their y coordinates first and then their x coordinates
   Test = OK */
int compare_all(const struct vec *p1, const struct vec *p2, const void *ctx) {
	if (p1->y < p2->y) {
		return -1;
	}
	else if(p1->y > p2->y) {
		return 1;
	}
	compare_x(p1, p2, ctx);
	return 0;
}

/* Compares two vectors based on their angle with the origin axis
   Test = ?*/
int compare_angle(const struct vec *p1, const struct vec *p2, const void *ctx) {
	const struct vec *ref = ctx;

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
	return 0;

}

/* Returns the max vector of a set of vectors
   Test = OK */
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx) {
        struct vec *res = &self->data[0];
        for (size_t i = 1; i < self->size; ++i) {
                int test = func(res, &self->data[i], &ctx);
                if (test == -1) {
                        res = &self->data[i];
                }
        }
        return res;
}

/* Returns the min vector of a set of vectors
   Test = OK */
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx) {
        struct vec *res = &self->data[0];
        for (size_t i = 1; i < self->size; ++i) {
                int test = func(res, &self->data[i], &ctx);
                if (test == 1) {
                        res = &self->data[i];
                }
        }
        return res;
}


/* Sorts a set of vectors
   Test = OK */
void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx) {
	long n = self->size;
	vector_quick_sort_partial(self, 0, n - 1, func);
}

/* Swaps two vectors in a vecset */
void vector_swap(struct vecset *self, size_t i, size_t j) {
	struct vec tmp = self->data[i];
	self->data[i] = self->data[j];
	self->data[j] = tmp;
}

long vector_partition(struct vecset *self, long i, long j, comp_func_t func) {
	long pivot_index = i;
	const struct vec pivot = self->data[pivot_index];
	vector_swap(self, pivot_index, j);
	long l = i;
	for (long k = i; k < j; ++k) {
		if (compare_all(&self->data[k],&pivot, 0) == -1) {
			vector_swap(self, k, l);
			l++;
		}
	}
	vector_swap(self, l, j);
	return l;
}

void vector_quick_sort_partial(struct vecset *data, long i, long j, comp_func_t func) {
	if (i < j) {
		long p = vector_partition(data, i, j, func);
		vector_quick_sort_partial(data, i, p - 1, func);
		vector_quick_sort_partial(data, p + 1, j, func);
	}
}


//Temporary main function in order to test vecset functions
/*int main() {
        struct vecset *set = malloc(sizeof(struct vecset));
        vecset_create(set);

        struct vec *v = malloc(sizeof(struct vec));
        struct vec *v1 = malloc(sizeof(struct vec));
        struct vec *v2 = malloc(sizeof(struct vec));
        struct vec *v3 = malloc(sizeof(struct vec));
        struct vec *v4 = malloc(sizeof(struct vec));

        vec_create(v, 8, 6);
        vec_create(v1, 2, 3);
        vec_create(v2, 1, 1);
        vec_create(v3, 4, 6);
        vec_create(v4, 5, 2);


        vecset_add(set, *v);
        vecset_add(set, *v1);
        vecset_add(set, *v2);
        vecset_add(set, *v3);
        vecset_add(set, *v4);


	vector_set_sort(set, compare_all, NULL);
	vecset_dump(set);
        const struct vec *res = vecset_min(set, &compare_x, NULL);
        vec_dump(res);
        vec_destroy(v);
        vec_destroy(v1);
        vec_destroy(v2);
        vec_destroy(v3);
        vec_destroy(v4);
        vecset_destroy(set);

        return 0;
}*/

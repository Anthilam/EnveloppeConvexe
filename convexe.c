#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "vecset.h"
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

int main(int argc, char * argv) {
	return 0;
}

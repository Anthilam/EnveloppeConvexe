/*
 * GUY Timothée , LAURENT Timothée
 * Groupe TP2A - CMI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "vecset.h"
#include "convex.h"

/* Jarvis march algorithm */
void jarvis_march(const struct vecset * in, struct vecset * out)
{
    assert(in);
    assert(out);

    if (in->size == 2) {
        vecset_add(out, in->data[0]);
        vecset_add(out, in->data[1]);
        struct vec * v = malloc(sizeof(struct vec));
        vec_create(v, (in->data[0].x + in->data[1].x) / 2, (in->data[0].y + in->data[1].y) / 2);
        vecset_add(out, *v);
    } else {
        const struct vec * first = vecset_min(in, &compare_left_bottom, NULL);
        struct vec * current = malloc(sizeof(struct vec));
        current->x = first->x;
        current->y = first->y;
        struct vec * next;
        int r = 0;

        srand(time(NULL));

        do {
            vecset_add(out, *current);

            do {
                r = rand() % (in->size - 1);
            } while (&in->data[r] == current);

            next = &in->data[r];

            for (int i = 0; i < in->size; ++i) {
                if (is_left_turn(current, &in->data[i], next)) {
                    next = &in->data[i];
                }
            }

            current = next;
        } while (first != current);
    }
} /* jarvis_march */

void graham_scan(const struct vecset * in, struct vecset * out)
{
    assert(in);
    assert(out);

    // Lowest point in the input
    const struct vec * lowest = vecset_min(in, &compare_all, NULL);
    // Copy of the input into s (without the lowest point)
    struct vecset * s = malloc(sizeof(struct vecset));
    vecset_create(s);
    for (size_t i = 0; i < in->size; i++) {
        if (compare_all(&in->data[i], lowest, NULL)) {
            vecset_push(s, in->data[i]);
        }
    }

    // Sorts s (using the angle with the origin axe and the lowest point as reference)
    vector_set_sort(s, &compare_angle, lowest);

    // First element in s
    struct vec * first = s->data;

    // Pushes the lowest point and the first one into the output
    vecset_push(out, *lowest);
    vecset_push(out, *first);
    const struct vec * top;
    const struct vec * second;
    for (size_t i = 1; i < s->size; i++) {
        top    = vecset_top(out);
        second = vecset_second(out);
        const struct vec third = s->data[i];
        while (out->size >= 2 && is_left_turn(second, top, &third)) {
            vecset_pop(out);
            top    = vecset_top(out);
            second = vecset_second(out);
        }
        vecset_push(out, s->data[i]);
    }

    // Destroys the copy of the input
    vecset_destroy(s);
} /* graham_scan */

void quickhull(const struct vecset * in, struct vecset * out)
{
    assert(in);
    assert(out);
    // If there are less than 4 points, they are all part of the convex hull
    if (in->size <= 3) {
        for (size_t i = 0; i < in->size; ++i) {
            vecset_add(out, in->data[i]);
            if (in->size == 2 && i == 0) {
                struct vec * v = malloc(sizeof(struct vec));
                vec_create(v, (in->data[0].x + in->data[1].x) / 2, (in->data[0].y + in->data[1].y) / 2);
                vecset_add(out, *v);
            }
        }
        return;
    }
    // Leftmost point in the input
    const struct vec leftmost = *vecset_min(in, compare_x, NULL);
    // Rightmost point in the input
    const struct vec rightmost = *vecset_max(in, compare_x, NULL);
    // Copy of the input into s (without the leftmost and rightmost points)
    struct vecset * s = malloc(sizeof(struct vecset));
    vecset_create(s);
    for (size_t i = 0; i < in->size; i++) {
        if (compare_all(&in->data[i], &leftmost, NULL) && compare_all(&in->data[i], &rightmost, NULL)) {
            vecset_push(s, in->data[i]);
        }
    }
    struct vecset * leftpart  = malloc(sizeof(struct vecset));
    struct vecset * rightpart = malloc(sizeof(struct vecset));

    vecset_create(leftpart);
    vecset_create(rightpart);

    for (size_t i = 0; i < s->size; i++) {
        // if (s->data[i] == NULL) {//??? A FAIRE (c'est quoi la condition???)
        vecset_add(leftpart, s->data[i]);
        // }
        // else {
        vecset_add(rightpart, s->data[i]);
        // }
    }
    // struct vecset R1 = NULL;
    // struct vecset R2 = NULL;
} /* quickhull */

/*struct vecset findhull(const struct vecset *in, const struct vec *A, const struct vec *B) {
 *  return NULL;
 * }*/

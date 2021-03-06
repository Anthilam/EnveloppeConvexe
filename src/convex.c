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
void jarvis_march(const struct vecset *in, struct vecset *out)
{
    assert(in);
    assert(out);
    // Case where the size of the hull is equal to 2 points
    if (in->size == 2) {
        vecset_add(out, in->data[0]);
        vecset_add(out, in->data[1]);
        // Creation of a new vector in order for the hull to be drawn
        struct vec v;
        v.x = (in->data[0].x + in->data[1].x) / 2;
        v.y = (in->data[0].y + in->data[1].y) / 2;
        vecset_add(out, v);
    // Case where the size of the hull is superior or equal to 3 points
    } else {
        // First is the most left-bottom point in the hull
        const struct vec *first = vecset_min(in, &compare_left_bottom, NULL);
        // Current point
        const struct vec *current = first;
        // Next point
        struct vec * next;

        int r = 0;
        srand(time(NULL));

        do {
            vecset_add(out, *current);

            // Gets a random point from the hull, different from current
            do {
                r = rand() % (in->size - 1);
            } while (&in->data[r] == current);

            next = &in->data[r];

            // If is_left_turn() is true, next gets the point i from the vecset in
            for (int i = 0; i < in->size; ++i) {
                if (is_left_turn(current, &in->data[i], next)) {
                    next = &in->data[i];
                }
            }

            current = next;
        } while (first != current);
    }
} /* jarvis_march */

/* Graham scan algorithm */
void graham_scan(const struct vecset * in, struct vecset * out)
{
    assert(in);
    assert(out);

    // Lowest point in the input
    const struct vec *lowest = vecset_min(in, &compare_all, NULL);
    // Copy of the input into s (without the lowest point)
    struct vecset *s = malloc(sizeof(struct vecset));
    vecset_create(s);

    for (size_t i = 0; i < in->size; ++i) {
        if (compare_all(&in->data[i], lowest, NULL)) {
            vecset_push(s, in->data[i]);
        }
    }

    // Sorts s (using the angle with the origin axe and the lowest point as reference)
    vector_set_sort(s, &compare_angle, lowest);

    // First element in s
    struct vec *first = s->data;

    // Pushes the lowest point and the first one into the output
    vecset_push(out, *lowest);
    vecset_push(out, *first);

    const struct vec *top;
    const struct vec *second;

    for (size_t i = 1; i < s->size; ++i) {
        top = vecset_top(out);
        second = vecset_second(out);
        const struct vec third = s->data[i];
        while (out->size >= 2 && is_left_turn(second, top, &third)) {
            vecset_pop(out);
            top = vecset_top(out);
            second = vecset_second(out);
        }
        vecset_push(out, s->data[i]);
    }

    // Destroys the copy of the input
    vecset_destroy(s);
    free(s);
    s = NULL;
} /* graham_scan */

/* Findhull function */
struct vecset * findhull(struct vecset * S, const struct vec * X, const struct vec * Y)
{
    if (S->size == 0) {
        struct vecset *T = malloc(sizeof(struct vecset));
        vecset_create(T);
        return T;
    }

    // m is the leading coefficient of (X,Y)
    double m = (X->y - Y->y) / (X->x - Y->x);
    // p is the ordered at the origion of (X,Y)
    double p = X->y - m * X->x;

    // Calculates the farthest point in S from (X,Y)
    struct vec * M;
    double res = 0;
    for (int i = 0; i < S->size; ++i) {
        if ((fabs(m * S->data[i].x - S->data[i].y + p) / sqrt(pow(m, 2) + 1)) > res) {
            M = &S->data[i];
            res = (fabs(m * S->data[i].x - S->data[i].y + p) / sqrt(pow(m, 2) + 1));
        }
    }

    struct vecset *S1 = malloc(sizeof(struct vecset));
    struct vecset *S2 = malloc(sizeof(struct vecset));
    vecset_create(S1);
    vecset_create(S2);

    for (size_t i = 0; i < S->size; i++) {
        if (S->data[i].x != M->x && S->data[i].y != M->y) {
            const struct vec T = S->data[i];
            // If the point is on the left of (X,M)
            if (is_left_turn(X, M, &T)) {
                vecset_add(S1, S->data[i]);
            // If the point is on the left of (M,Y)
            } else if (is_left_turn(M, Y, &T)) {
                vecset_add(S2, S->data[i]);
            }
        }
    }

    struct vecset *R1 = findhull(S1, X, M);
    struct vecset *R2 = findhull(S2, M, Y);

    struct vecset *R = malloc(sizeof(struct vecset));
    vecset_create(R);

    // Union of R1, M and R2
    for (int i = 0; i < R1->size; ++i) {
        vecset_add(R, R1->data[i]);
    }
    vecset_add(R, *M);
    for (int i = 0; i < R2->size; ++i) {
        vecset_add(R, R2->data[i]);
    }

    // Destroys the created vecsets
    vecset_destroy(S1);
    vecset_destroy(S2);
    vecset_destroy(R1);
    vecset_destroy(R2);
    free(S1);
    free(S2);
    free(R1);
    free(R2);
    S1 = NULL;
    S2 = NULL;
    R1 = NULL;
    R2 = NULL;

    return R;
} /* findhull */

/* Quickhull algorithm */
void quickhull(const struct vecset *in, struct vecset *out)
{
    assert(in);
    assert(out);

    // Leftmost point in the input
    const struct vec A = *vecset_min(in, compare_x, NULL);
    // Rightmost point in the input
    const struct vec B = *vecset_max(in, compare_x, NULL);

    struct vecset *S1 = malloc(sizeof(struct vecset));
    struct vecset *S2 = malloc(sizeof(struct vecset));
    vecset_create(S1);
    vecset_create(S2);

    // Copy of the input into s (without the leftmost and rightmost points)
    for (size_t i = 0; i < in->size; i++) {
        if (in->data[i].x != A.x && in->data[i].x != B.x &&
          in->data[i].y != A.y && in->data[i].y != B.y)
        {
            const struct vec test = in->data[i];
            if (is_left_turn(&A, &B, &test)) {
                vecset_push(S1, in->data[i]);
            } else {
                vecset_push(S2, in->data[i]);
            }
        }
    }

    struct vecset *R1 = findhull(S1, &A, &B);
    struct vecset *R2 = findhull(S2, &B, &A);

    // Union of A, R1, B and R2
    vecset_add(out, A);
    for (int i = 0; i < R1->size; ++i) {
        vecset_add(out, R1->data[i]);
    }
    vecset_add(out, B);
    for (int i = 0; i < R2->size; ++i) {
        vecset_add(out, R2->data[i]);
    }

    // Destroys the created vecsets
    vecset_destroy(S1);
    vecset_destroy(S2);
    vecset_destroy(R1);
    vecset_destroy(R2);
    free(S1);
    free(S2);
    free(R1);
    free(R2);
    S1 = NULL;
    S2 = NULL;
    R1 = NULL;
    R2 = NULL;
} /* quickhull */

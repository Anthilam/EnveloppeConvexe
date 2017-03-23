/*
 * GUY Timothée , LAURENT Timothée
 * Groupe TP2A - CMI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
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
        // first est le point le plus à droite
        const struct vec * first = vecset_min(in, &compare_left_bottom, NULL);

        // current est le point courant
        struct vec * current = first;
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

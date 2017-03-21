/*
 * GUY Timothée , LAURENT Timothée
 * Groupe TP2A - CMI
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "vecset.h"
#include "convex.h"

/* Jarvis march algorithm */
void jarvis_march(const struct vecset * in, struct vecset * out)
{
    assert(in);
    assert(out);

    if (in->size <= 3) {
        for (size_t i = 0; i < in->size; ++i) {
            vecset_add(out, in->data[i]);
            if (in->size == 2 && i == 0) {
                struct vec * v = malloc(sizeof(struct vec));
                vec_create(v, (in->data[0].x + in->data[1].x) / 2, (in->data[0].y + in->data[1].y) / 2);
                vecset_add(out, *v);
            }
        }
    } else {
        // first est le point le plus à droite
        const struct vec * first = malloc(sizeof(struct vec));
        first = vecset_min(in, &compare_x, NULL);
        vecset_dump(in);
        printf("first:");
        vec_dump(first);

        // current est le point courant
        struct vec current;
        current = *first;

        do {
            vecset_add(out, current);
            struct vec next;

            next = in->data[0];

            for (size_t i = 0; i < in->size; ++i) {
                if (is_left_turn(&current, &in->data[i], &next)) {
                  for (size_t j = 0; j < out->size; ++j) {
                    if (in->data[i].x != out->data[j].x && in->data[i].y != out->data[j].y) {
                      next = in->data[i];
                      vec_dump(&next);
                    }
                  }
                }
            }

            current = next;
        } while (first->x != current.x && first->y != current.y);
    }
}

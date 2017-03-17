#ifndef CONVEX_H
#define CONVEX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "vecset.h"
// Timothée LAURENT - Timothée GUY

// This header contains the 3 following convex hull algorithms

// Jarvis march function
void jarvis_march(const struct vecset *in, struct vecset *out);

// Graham scan function
void graham_scan(const struct vecset *in, struct vecset *out);

// Quick hull function
void quickhull(const struct vecset *in, struct vecset *out);
#endif

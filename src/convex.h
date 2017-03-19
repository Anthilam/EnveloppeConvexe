/*
		GUY Timothée , LAURENT Timothée
		Groupe TP2A - CMI
*/

#ifndef CONVEX_H
#define CONVEX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "vecset.h"

// This header contains the 3 following convex hull algorithms

// Jarvis march function
struct vecset *jarvis_march(const struct vecset *in, struct vecset *out);

// Graham scan function
struct vecset *graham_scan(const struct vecset *in, struct vecset *out);

// Quick hull function
struct vecsets *quickhull(const struct vecset *in, struct vecset *out);

#endif

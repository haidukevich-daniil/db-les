#ifndef BUILDER_H
#define BUILDER_H

#include <stdio.h>
#include "common.h"

void builder(FILE *in, FILE *out, FILE *index);
void generator(FILE *dat, FILE *index);

#endif
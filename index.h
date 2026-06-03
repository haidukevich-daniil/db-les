#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include "common.h"

long insert_node(FILE *index, long root_offset, long data_offset, int year, double area);

long find_node(FILE *index, long root_offset, int year);

void print_same(FILE *index, FILE *data, long offset);

double total_area(FILE *index, long offset_from, int from, int to);

void print_stats(FILE *index);

#endif
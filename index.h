#ifndef INDEX_H
#define INDEX_H

#include <stdio.h>
#include "common.h"

long create_node(FILE *index, int year, long data_offset);

IndexNode read_node(FILE *index, long offset);

void write_node(FILE *index, long offset, IndexNode node);

long insert_node(FILE *index, long root_offset, long data_offset, int year);

long find_node(FILE *index, long root_offset, int year);

void print_same(FILE *index, long offset);

double total_area(FILE *index, long offset_from, int from, int to);

void print_stats(FILE *index);

#endif
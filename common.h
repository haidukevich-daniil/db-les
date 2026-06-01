#ifndef COMMON_H
#define COMMON_H

typedef struct{
    char code[20];
    int year;
    int species;
    double area;
}LesData;

typedef struct{
    int year;
    long data_offset;
    long right;
    long left;
    long next;
}IndexNode;

#endif 
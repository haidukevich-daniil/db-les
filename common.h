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
     double year_area;
     double subtree_area;
}IndexNode;

typedef struct{
     int count;
     double total_area;
     long root_offset;
}IndexHeader;

#endif 
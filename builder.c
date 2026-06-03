#include "builder.h"
#include "common.h"
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void builder(FILE *in, FILE *out, FILE *index){
     if( in == NULL || out == NULL || index == NULL) {
          printf("Error opening file\n");
          return;
     }

     LesData data;
     IndexHeader header = {0, 0.0, -1};
     fwrite(&header, sizeof(IndexHeader), 1, index);
     long offset = 0;

     while(fscanf(in, "%s %d %d %lf",
               data.code, 
               &data.year,
               &data.species,
               &data.area) == 4){
          fwrite(&data, sizeof(LesData), 1, out);

          header.root_offset = insert_node(index, header.root_offset, offset, data.year, data.area);
          
          offset += sizeof(LesData);
          header.count++;
          header.total_area += data.area;
     }

     fseek(index, 0, SEEK_SET);
     fwrite(&header, sizeof(IndexHeader), 1, index);

}
void generator(FILE *dat, FILE *index, int count){
      srand(time(NULL));

      if( dat == NULL || index == NULL) {
           printf("Error opening file\n");
           return;
      }   

      IndexHeader header = {0, 0.0, -1};
      fwrite(&header, sizeof(IndexHeader), 1, index);
      long offset = 0;

      for(int i = 0; i < count; i++){
           LesData data;
           sprintf(data.code, "%c%d", 'A' + rand() % 26, i);
           data.year = 1960 + rand() % 66;
           data.species = 1 + rand() % 100;
           data.area = (double)(rand() % 100);

           printf("Generated: %s %d %d %.2lf\n", data.code, data.year, data.species, data.area);

           fwrite(&data, sizeof(LesData), 1, dat);

           header.root_offset = insert_node(index, header.root_offset, offset, data.year, data.area);
           offset += sizeof(LesData);
           header.count++;
           header.total_area += data.area;
      }

      fseek(index, 0, SEEK_SET);
      fwrite(&header, sizeof(IndexHeader), 1, index);

}
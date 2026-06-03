#include <stdio.h>
#include "common.h"
#include "index.h"

int main(int argc, char *argv[]) {
     if(argc < 2){
       printf("Usage: %s <input_file>/<--generate>\n", argv[0]);
         return 1;
     }

     FILE *in = fopen("input.txt","r");
     FILE *out = fopen("les.dat","wb");
     FILE *index = fopen("les.idx","wb");
     if( in == NULL || out == NULL || index == NULL) {
          printf("Error opening file\n");
          return 1;
     }

     if(strcmp(argv[1], "--generate")==0){

     }else{
          builder(in, out, index);
     }

      fclose(in);
      fclose(out);
      fclose(index);
     
     return 0;
}
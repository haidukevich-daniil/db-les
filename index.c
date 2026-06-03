#include <stdio.h>
#include "common.h"
#include "index.h"

long create_node(FILE *index, int year, long data_offset, double area){
     IndexNode node;
     node.year = year;
     node.data_offset = data_offset;
     node.left = -1;
     node.right = -1;
     node.next = -1;
     node.subtree_area = area;
     node.year_area = area;


     fseek(index, 0, SEEK_END);
     long offset = ftell(index);
     fwrite(&node, sizeof(IndexNode), 1, index);
     return offset;
}

IndexNode read_node(FILE *index, long offset){
     IndexNode node;
     fseek(index, offset, SEEK_SET);
     fread(&node, sizeof(IndexNode), 1, index);
     return node;
}

void write_node(FILE *index, long offset, IndexNode node){
     fseek(index, offset, SEEK_SET);
     fwrite(&node, sizeof(IndexNode), 1, index);
}

long insert_node(FILE *index, long root_offset, long data_offset, int year, double area){
     if(root_offset == -1){
          return create_node(index, year, data_offset, area);
    }

     IndexNode current = read_node(index, root_offset);
     current.subtree_area += area;
     write_node(index, root_offset, current);

     if(year < current.year){
          if(current.left == -1){
          long left_offset = create_node(index, year, data_offset, area);
          current.left = left_offset;
          write_node(index, root_offset, current);
          }else{
                insert_node(index, current.left, data_offset, year, area);
          }
     }
     else if(year > current.year){
          if(current.right == -1){
               long right_offset = create_node(index, year, data_offset, area);
               current.right = right_offset;
               write_node(index, root_offset, current);
          }else{
                insert_node(index, current.right, data_offset, year, area);
          }
     }else{
          current.year_area += area;
          write_node(index, root_offset, current);

          long next_offset = create_node(index, year, data_offset, area);
          long list_offset = root_offset;
          IndexNode list = read_node(index, list_offset);

          while(list.next != -1){
                list_offset = list.next;
                list = read_node(index, list.next);
          }
          list.next = next_offset;
          write_node(index, list_offset, list);
     }
     return root_offset;
}

long find_node(FILE *index, long root_offset, int year){
     if(root_offset == -1){
          return -1;
     }

     IndexNode current = read_node(index, root_offset);

     if(year < current.year){
          return find_node(index, current.left, year);
     }
     else if(year > current.year){
          return find_node(index, current.right, year);
     }
     else return root_offset;
}

void print_same(FILE *index, FILE *data, long offset){
     while (offset != -1){
          IndexNode node = read_node(index, offset);
          LesData dat;
          fseek(data, node.data_offset, SEEK_SET);
          fread(&dat, sizeof(LesData), 1, data);
          printf("%s %d %d %.2lf\n", dat.code, dat.year, dat.species, dat.area);
          offset = node.next;
     }
}

double total_area(FILE *index, long offset_from, int from, int to){
     if(offset_from == -1) return 0.0;

     IndexNode current = read_node(index, offset_from);
     double total = 0.0;

     if(current.year > from){
          total +=total_area(index, current.left, from, to);
     }

     if(current.year < to){
          total +=total_area(index, current.right, from, to);
     }   

     if(current.year >= from && current.year <= to){
          total += current.year_area;
     }
     return total;
}

void print_stats(FILE *index){
     IndexHeader header;
     fseek(index, 0, SEEK_SET);
     fread(&header, sizeof(IndexHeader), 1, index);
     printf("Total records: %d\n", header.count);
     printf("Total area: %.2lf\n", header.total_area);
}

void previous_sum(FILE *index, long offset_from, int year){
     if(offset_from == -1) return;

     Index Node current = read_node(index, offset_from);

     if(current.year > year){
        previous_sum(index, current.left, year);
     }else{
        double total_left = 0.0;
        if(current.left != -1){
             IndexNode left = read_node(index, current.left);
             total_left += left.subtree_area;    
        }
     }
     return total_left + node.year_area + previous_sum(index, current.right, year);
}
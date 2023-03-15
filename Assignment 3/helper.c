#include <stdlib.h>
#include "helper.h"

/*finds max value in array*/
int arr_max(int nrid, int *dests){
  int max = dests[0];
  for(int i = 1; i < nrid; i++)
    if(max < dests[i]) max = dests[i];
  return max;
}

/*
fw function of the recursive expression
returns the cost of ascending and descending
for passengers that have a d destinations between floors a and b
*/
int fw(int a, int b, int nrid, int *dests){
  int sum = 0;
  for(int i = 0; i < nrid; i++){
    if(dests[i] > a && dests[i] <= b){
      /*calculate least floors walked*/
      int temp;
      if(dests[i] - a < b - dests[i])
        temp = dests[i] - a;
      else
        temp = b - dests[i];

      sum += temp;
    }
  }
  return sum;
}

/*creates a 2d int array*/
int **create_2d(int height, int width){
    int **arr;
    if((arr = malloc(height * sizeof(int *))) == NULL)
        return NULL;
    for(int i = 0; i < height; i++){
        if((arr[i] = malloc(width * sizeof(int))) == NULL)
            return NULL;
    }
    return arr;
}

/*frees a 2d int array*/
void free_2d(int **arr, int height){
    for(int i = 0; i < height; i++)
        free(arr[i]);
    free(arr);
}

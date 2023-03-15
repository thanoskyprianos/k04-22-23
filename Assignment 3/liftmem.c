/*
This implimentation is almost identical to liftrec.c with the difference that
we use a dynamically alocated 2d array called memo that stores already calculated M(i, j) values
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> /*used to represent infinity as INT_MAX*/
#include "lift.h"
#include "helper.h"

/*recursive function that caclulates and stores M(i, j) values*/
int mij(int nst, int j, int nrid, int *dests, int **memo){
  if(memo[nst][j] != - 1) /*the value was previously calculated so just return it*/
    return memo[nst][j];

  int min = INT_MAX;
  int temp;
  for(int k = 0; k <= j; k++){
    if(nst != 0)
      temp = mij(nst - 1, k, nrid, dests, memo)
            - fw(k, INT_MAX, nrid, dests)
            + fw(k, j, nrid, dests)
            + fw(j, INT_MAX, nrid, dests);
    else
      temp = fw(0, INT_MAX, nrid, dests);

    if(temp < min)
      min = temp;
  }

  memo[nst][j] = min; /*not only return min, but also store it for later*/
  return min;
}

/*calls the recursive mij and finds MinCost*/
int solve(int nrid, int nst, int *dests){
    int min_cost = INT_MAX;
    int min_stop;
    int nfl = arr_max(nrid, dests);

    /*memoization 2d matrix*/
    int **memo;
    if((memo = create_2d(nst + 1, nfl + 1)) == NULL) /*ranges are [0, nst] and [0, nfl] thus nst + 1, nfl + 1 sizes*/
        return -1;
    for(int i = 0; i <= nst; i++)
        for(int j = 0; j <= nfl; j++)
            memo[i][j] = -1; /*can't have negative cost, used for checking if mij is already calculated*/

    for (int j = 0; j <= nfl; j++)
    {
      int temp = mij(nst, j, nrid, dests, memo);
      if(temp < min_cost){
        min_cost = temp;
        min_stop = j;
      }
    }

    if(min_stop != 0)
        printf("Last stop at floor %d\n", min_stop);
    else
        printf("No lift stops\n");

    free_2d(memo, nst + 1);
    return min_cost;
}

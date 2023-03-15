/*
Recursive program that exactly executes the recursive algorithm
for finding the minimum cost of ascendings and descendings of passengers
from the point they get off to their desired stop. The formula is:

-MinCost = min{M(nst, j)} for j in [0, nfl]
-M(i, j) = * fw(0, inf) for i = 0
           * min{M(i - 1, k) - fw(k, inf) + fw(k, j) + fw(j ,inf)} for k in [0, j] and i != 0

The MinCost part is handled in the solve function which calls the recursive
function mij that handles the part of calculating every M(i, j) value
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> /*used to represent infinity as INT_MAX */
#include "lift.h"
#include "helper.h"

/*recursive function that calculates M(i, j) values*/
int mij(int nst, int j, int nrid, int *dests){
    int min = INT_MAX;
    int temp;
    for(int k = 0; k <= j; k++){
        if(nst != 0)
            temp = mij(nst - 1, k, nrid, dests)
                  - fw(k, INT_MAX, nrid, dests)
                  + fw(k, j, nrid, dests)
                  + fw(j, INT_MAX, nrid, dests);
        else
            temp = fw(0, INT_MAX, nrid, dests);

        if(temp < min)
            min = temp;
    }
    return min;
}

/*calls the recursive mij and finds MinCost*/
int solve(int nrid, int nst, int *dests){
    int min_cost = INT_MAX;
    int min_stop = 0;
    int nfl = arr_max(nrid, dests);

    for (int j = 0; j <= nfl; j++){
        int temp = mij(nst, j, nrid, dests);
        if(temp < min_cost){
            min_cost = temp;
            min_stop = j;
        }
    }

    if(min_stop != 0)
        printf("Last stop at floor %d\n", min_stop);
    else
        printf("No lift stops\n");

    return min_cost;
}

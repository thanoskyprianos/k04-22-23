/*
Program that uses dynamic programming to find MinCost.
It basically reverses the formula of recursion, ie. it first
calculates the M(0, j) for j in [0, nfl]
values that are then used for the M(1, k) values for k in [0, j] etc...

It stores the values in a 2d array called **costs.
The program a 2d array called **prevs with the same dimensions as **costs
that stores the last floor where the respective minimum M(i, j) value was found.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> /*used to represent infinity as INT_MAX*/
#include "lift.h"
#include "helper.h"

/*
Prints the floors that result in the least cost.
Uses recursion to find and print them in ascending order
*/
void print_floors(int min_i, int min_j, int **prevs){
    if(min_j == 0)
        return;

    print_floors(min_i - 1, prevs[min_i][min_j], prevs);
    printf("%d ", min_j);
}

/*finds MinCost*/
int solve(int nrid, int nst, int *dests){
    int min_cost = INT_MAX, min_i = 0, min_j = 0;
    int nfl = arr_max(nrid, dests);
    int **costs; /*store M(i, j) values*/
    int **prevs; /*store floor of previous recursive value*/

    /*ranges are [0, nst] and [0, nfl] thus nst + 1, nfl + 1 sizes*/
    if((costs = create_2d(nst + 1, nfl + 1)) == NULL)
        return -1;
    if((prevs = create_2d(nst + 1, nfl + 1)) == NULL)
        return -1;

    int all_walk = fw(0, INT_MAX, nrid, dests); /*when i of M(i, j) is 0*/
    for(int i = 0; i <= nst; i++){
        for(int j = 0; j <= nfl; j++){
            if(i == 0){
                costs[i][j] = all_walk;
                prevs[i][j] = 0; /*M(i, j) is always found in floor 0*/
            }
            else{
                int temp_min = INT_MAX, temp_stop;
                for(int k = 0; k <= j; k++){
                    int temp_cost = costs[i - 1][k]
                                   - fw(k, INT_MAX, nrid, dests)
                                   + fw(k, j, nrid, dests)
                                   + fw(j, INT_MAX, nrid, dests);

                    if(temp_cost < temp_min){
                        temp_min = temp_cost;
                        temp_stop = k;
                    }
                }
                costs[i][j] = temp_min;
                prevs[i][j] = temp_stop;
            }
            if(costs[i][j] < min_cost){
                min_cost = costs[i][j];
                min_i = i; min_j = j;
            }

            printf("%3d ", costs[i][j]);
       }
       putchar('\n');
    }

    if(min_j != 0){
        printf("Lift stops are: ");
        print_floors(min_i, min_j, prevs);
    }
    else
        printf("No lift stops");

    putchar('\n');

    free_2d(costs, nst + 1); free_2d(prevs, nst + 1);
    return min_cost;
}

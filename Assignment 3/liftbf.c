/*

The program is based on this algorithm: https://www.guru99.com/print-all-possible-combinations.html

It uses recursion to pick and choose combinations
of k elements in an n sized array in an ascending fashion e.g.:

3 choose 2 on the array:                      [1,          5,          3]
                                              / \           \           \
                                         [1, 5] [1, 3]      [5, 3]  (no other element to group 3 with)

In our case we pass to the algorithm an array that contains the numbers from 1 to nfl.
That will:
1) choose every combination of all floors and
2) do it without redunduncy because the floors
   are going to be stored in an strictly ascending order.

To tackle the possibility of the elevator not moving for some of its stops e.g.: [0, 0, 6],
we just call the combinations function nst times. That way we can check combinations such as:
[0, 1, 2, 3] and [0, 0, 6]. These are simply just checked as [1, 2, 3] and [6] respectively.

The program uses an array of size k to create every combination by picking and choosing the next ascending numbers.
It also uses another array that stores the combination that give MinCost. If a new MinCost is found, the function just
frees the previous array and creates a new one with size equal to the combination array and proceeds to copy its contents to it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lift.h"
#include "helper.h"


/*
In the cases of the min_cost, the *min_stops and the stops_count their addresses are passed because
their values need to be altered inside the recursive function
*/
void combinations(int *floors, int *comb_arr, int *min_cost, int **min_stops, int *stops_count,
                  int index, int start, int nfl, int k, int nrid, int *dests)
{
    /*we check min_cost to return when needed: -1 if malloc failed or 0 because it is the minimum cost*/
    if((*min_cost) == -1 || (*min_cost) == 0)
        return;

    if(index == k){ /*created a combination of the needed size*/
        int cur_cost = 0;
        int prev = 0;
        for(int i = 0; i < k; i++){
            cur_cost += fw(prev, comb_arr[i], nrid, dests);

            if(cur_cost > (*min_cost)) /*used to not waste time on unwanted calculations*/
                return;

            prev = comb_arr[i];
        }
        cur_cost += fw(prev, INT_MAX, nrid, dests);

        if(cur_cost < (*min_cost)){
            *min_cost = cur_cost;
            free(*min_stops);

            if((*min_stops = malloc(k * sizeof(int))) == NULL){
                *min_cost = -1; /*done for checking above and notifying the solve function later*/
                return;
            }
            for(int i = 0; i < k; i++)
                (*min_stops)[i] = comb_arr[i];
            *stops_count = k;
        }
    }
    else{
        for(int i = start; i < nfl; i++){
            comb_arr[index] = floors[i]; /*put in the combination array the next ascending number*/
            combinations(floors, comb_arr, min_cost, min_stops, stops_count, index + 1, i + 1, nfl, k, nrid, dests);
        }
    }
}


int solve(int nrid, int nst, int *dests){

    /*we initialize the values to the case where the elevator does not move at all (case [0])*/
    int min_cost, temp_cost, stops_count = 1, nfl = arr_max(nrid, dests);
    int *min_stops, *floors;

    min_cost  = fw(0, INT_MAX, nrid, dests);
    temp_cost = min_cost;/*used for later to check if cost changed*/

    if((min_stops = malloc(stops_count * sizeof(int))) == NULL) return -1;
    if((floors = malloc(nfl * sizeof(int))) == NULL)            return -1;
    for(int i = 0; i < nfl; i++)
        floors[i] = i + 1;

    /*for loop is used to check all the combinations of size 1 to nst of the numbers 1 to nfl*/
    /*we basically do nfl choose k for k = [1, nst]*/
    for(int i = 1; i <= nst; i++){
        int *comb_arr;
        if((comb_arr = malloc(i * sizeof(int))) == NULL)
            return -1;

        combinations(floors, comb_arr, &min_cost, &min_stops, &stops_count, 0, 0, nfl, i, nrid, dests);
        free(comb_arr);

        if(min_cost == -1) /*malloc failed*/
            break;
    }

    if(min_cost != -1){
        if(min_cost != temp_cost){
            printf("Lift stops are: ");
            for(int i = 0; i < stops_count; i++)
                printf("%d ", min_stops[i]);
        }
        else
            printf("No lift stops");

        putchar('\n');
    }

    free(min_stops); free(floors);
    return min_cost;
}

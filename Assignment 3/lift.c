/*
The program should be compiled as:

All methods:
    gcc -c lift.c
    gcc -c helper.c

And then:
*Recursion:
    gcc -c liftrec.c
    gcc -o liftrec lift.o helper.o liftrec.o
*Brute Force:
    gcc -c liftbf.c
    gcc -o liftbf lift.o helper.o liftbf.o
*Memoization:
    gcc -c liftmem.c
    gcc -o liftmem lift.o helper.o liftmem.o
*Dynamic Programming:
    gcc -c liftdp.c
    gcc -o liftdp lift.o helper.o liftdp.o
*/

#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "lift.h"

int main(void){
    int nrid, nst, *dests;
    if(scanf("%d", &nrid) != 1)
        return -1;
    if(scanf("%d", &nst)  != 1)
        return -1;

    if(nrid < 0 || nst < 0)
        return -1;

    int cost = 0;
    if(nrid > 0){
        if((dests = malloc(nrid * sizeof(int))) == NULL)
            return -1;

        for(int i = 0; i < nrid; i++){
            if(scanf("%d", &dests[i]) != 1)
                return -1;
            if(dests[i] < 0)
                return -1;
        }

        cost = solve(nrid, nst, dests);
        if(cost < 0)
            return -1; /*used for liftmem, liftdp and liftbf where malloc could fail*/

        free(dests);
    }
    else /*no passengers so elevator is not moving*/
        printf("No lift stops\n");

    printf("Cost is: %d\n", cost);

    return 0;
}
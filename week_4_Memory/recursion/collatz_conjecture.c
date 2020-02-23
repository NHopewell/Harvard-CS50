/* Given a positive integer, it is always possible to
 * get back to 1 given the following steps are taken:
 *  - if n is 1, stop.
 *  - else if n is even, repeat process on n/2
 *  - else (n is odd), repeat process on 3n + 1
 */

#include <stdlib.h>
#include <stdio.h>

int collatz(int num, int steps);
    
int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]);
    if (n <= 0){
        printf("Must pass a positive integer\n");
        exit(0);
    }
    printf("The number of steps to reach 1:\n");
    printf("%i\n", collatz(n, 0));
}

int collatz(int num, int steps) 
{
    // base case
    if (num == 1)
        return steps;
    // even recursion case
    else if (num%2 == 0){
        steps += 1;
        return collatz(num/2, steps);
    // odd recusion case
    }
    else {
        steps += 1;
        return collatz(3*num+1, steps);
    }
}

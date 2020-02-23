#include <stdlib.h>
#include <stdio.h>

int factorial(int n);
    
int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]);
    printf("%i\n", factorial(n));
}

int factorial(int n) 
{
    if (n ==1)
        return 1;
    else
        return n * factorial(n-1);
}
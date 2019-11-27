#include <stdlib.h>
#include <stdio.h>

int fib(int n);
    
int main(int argc, char *argv[]) 
{
    int n = atoi(argv[1]);
    printf("%i\n", fib(n));
}

int fib(int n) 
{
    if (n == 1)
        return 1;
    else if (n == 2)
        return 2;
    else
        return fib(n-1) + fib(n-2);
}

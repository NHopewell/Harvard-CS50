#include <stdio.h>
#include <cs50.h>

int get_long_length(long);
int return_first_n_digits(long, int);

int main(void)
{
    long cc_number = get_long("Enter credit card number: ");
    int cc_number_length = get_long_length(cc_number);
    
     // convert cc input to string
    char buffer [20];
    snprintf(buffer, 20, "%lu", cc_number);
    
    int check_sum;
    int sum_every_other = 0;
    int sum_rest = 0;
    int total = 0;
    
    for (int i = 0; i < cc_number_length; i +=2 ){
        int x = buffer[i] - '0';
        x *= 2;
        if (x>9){
            char buffer_2 [10];
            snprintf(buffer_2, 10, "%d", x);
            for (int j = 0; j < 2; j++){
                int y = buffer_2[j] - '0';
                sum_every_other += y;
                } 
            } else {
                sum_every_other += x;
        }
    }
    for (int i = cc_number_length-1; i > 0; i-=2){
        int z = buffer[i] - '0';
        sum_rest += z;
    }
    
    total += sum_every_other + sum_rest;
    
    if (total % 10 == 0){
        if (cc_number_length == 15 && ( return_first_n_digits(cc_number, 2) ==34 
                                      || return_first_n_digits(cc_number, 2) ==37)){
            printf("AMEX\n");
        } else if (cc_number_length == 16 && ( return_first_n_digits(cc_number, 2) == 51  
                                          || return_first_n_digits(cc_number, 2) == 52
                                          || return_first_n_digits(cc_number, 2) == 53
                                          || return_first_n_digits(cc_number, 2) == 54
                                          || return_first_n_digits(cc_number, 2) == 55)){
                printf("MASTERCARD\n");
        } else if ((cc_number_length == 16 || cc_number_length == 16) && 
                   return_first_n_digits(cc_number, 1) == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else{
            printf("INVALID\n");
    }

}

int get_long_length(long number){
    // get the length of an a long
    int len = 1;
    while (number > 9){
        number /= 10;
        len ++;
    }
    return len;
}

int return_first_n_digits(long number, int n_digits)
{
   // return first n_digits of a long
    int int_length = get_long_length(number);
    int counter = int_length-n_digits;
    while (counter > 0){
        number/=10;
        counter--;
    }
    return number;
}



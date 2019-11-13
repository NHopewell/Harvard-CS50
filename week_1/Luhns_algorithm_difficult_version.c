// My implementation of Luhns algorithm to check
// the type and validity of a credit card number. 
// User enters a cc number, it must be parsed to
// be ensure it is valid and determine which
// type of card it is (Visa, AMEX, Mastercard).

#include <stdio.h>
#include <cs50.h>

int get_long_length(long);
int return_first_n_digits(long, int);

int main(void)
{
    // prompt for user cc number and store len
    long cc_number = get_long("Enter credit card number: ");
    int cc_number_length = get_long_length(cc_number);
    
    // convert cc input to string
    char buffer [20];
    snprintf(buffer, 20, "%lu", cc_number);
    
    int check_sum;
    int sum_every_other = 0;
    int sum_rest = 0;
    int total = 0;
    
    // convert every other char in array to int
    // multiply by 2
    // repeat if return val > 9
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
    // from end of array to start, convert to int, sum
    for (int i = cc_number_length-1; i > 0; i-=2){
        int z = buffer[i] - '0';
        sum_rest += z;
    }
    // sum every odd digit which has been multipled by 
    // 2 with the even digits
    total += sum_every_other + sum_rest;
    // check is sum ends in 0
    if (total % 10 == 0){
        // get first and first&second digits for checking
        int first_digit = return_first_n_digits(cc_number, 1);
        int first_two_digits = return_first_n_digits(cc_number, 2);

        // check terms for each typeof credit card to be valid
        if (cc_number_length == 15 && ( first_two_digits == 34 
                                      || first_two_digits ==37 )){
            printf("AMEX\n");
        } else if (
            cc_number_length == 16 && (
                first_two_digits == 51 || first_two_digits == 52 ||
                first_two_digits == 53 || first_two_digits == 54 ||
                first_two_digits == 55)
                  ){ printf("MASTERCARD\n");
        } else if (
            (cc_number_length == 16 || cc_number_length == 16) && 
                   first_digit  == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else{  // base case
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



/* crack.c tries to crack a hased password. 

Specifications
1. Your program should accept one and only one 
    command-line argument: a hashed password.
2. If your program is executed without any command-line
   arguments or with more than one command-line argument, 
   your program should print an error (of your choice) and 
   exit immediately, with main returning 1 (thereby signifying
   an error).
3. Otherwise, your program must proceed to crack the given 
   password, ideally as quickly as possible, ultimately printing 
   the password in the clear followed by \n, nothing more, nothing 
   less, with main returning 0.
4. Assume that each password has been hashed with C’s DES-based 
   (not MD5-based) crypt function.
5. Assume that each password is no longer than five (5)
   characters. Gasp!
6. Assume that each password is composed entirely of alphabetical 
   characters (uppercase and/or lowercase).

Example: 
$ ./crack 50cI2vYkF0YU2
LOL

*/

#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc !=2 || argv[1] == NULL) {
        string usage = "Usage: ./crack hash\n";
        printf("%s", usage);
        exit(1);
    }
    
    // 26 lowercase + 26 uppercase + \0 counts as 1 character = 53
    const int NUM_LETTERS = 53;

    // looping will halt at null bit - this is used to halt below
    string all_letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    char salt[3];         
    char to_check[5] = "\0\0\0\0\0";            
    //second char of user passed string into salt
    strncpy(salt, argv[1], 2); 
    salt[2] = '\0';

    for (int m = 0; m < NUM_LETTERS; m++){
        for (int l = 0; l < NUM_LETTERS; l++){
            for (int k = 0; k < NUM_LETTERS; k++){
                for (int j = 0; j < NUM_LETTERS; j++){
                    for (int i = 1; i < NUM_LETTERS; i++){ // start at a not null
                        // first pass through all_letters, other positions held null
                        to_check[0] = all_letters[i];  
                        to_check[1] = all_letters[j]; 
                        to_check[2] = all_letters[k];  
                        to_check[3] = all_letters[l]; 
                        to_check[4] = all_letters[m]; 
                        if (strcmp(crypt(to_check, salt), argv[1]) == 0)
                        {
                            printf("%s\n", to_check);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}



#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])

{
    const int NUM_LETTERS = 26;
    int z = (int) 'z';
    int Z = (int) 'Z';

    string usage = "Usage: ./caesar key\n";
    // assert user passed 2 args
    if (argc < 2 || argc > 2) {
        printf("%s", usage);
        exit(0);
    }
    // if word contains digit, exit
    for (int i = 0, n = strlen(argv[1]); i < n; i++){
        if (isdigit(argv[1][i])){
            printf("%s", usage);
            exit(0);
        }
    }

    string plain_text = get_string("plaintext:  ");

    int key[strlen(argv[1])];

    // shift each letter of key
    for (int i = 0, n = strlen(argv[1]); i < n; i++){
        key[i] = shift(argv[1][i]);

    }

    printf("ciphertext: ");
    // for each char in str array,
    // convert to int, add value passed by user, print as char
    int key_index = 0;
    int text_counter = 0;
    for (int i = 0, plain_text_len = strlen(plain_text); i < plain_text_len; i++) {
        // check if letter of alphabet, must skip grammar.
        if (text_counter > strlen(argv[1])-1) {
            key_index = 0;
            text_counter = 0;
        }
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            int c = (int) plain_text[i]+key[key_index];
            // if lower case, check if result larger than 'z'
            // // if so minus NUM_LETTERS
            if (c > z) {
                c = c - NUM_LETTERS;
                printf("%c", c);
            } else {
                printf("%c", c);
            }
            key_index++;
            text_counter++;
        } else if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            int c = (int) plain_text[i]+key[key_index];
            if (c > Z) {
                c = c - NUM_LETTERS;
                printf("%c", c);
            } else {
                printf("%c", c);
            }
            key_index++;
            text_counter++;
        } else {
            // else make no changes
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
} 

int shift(char c)
{
    // arent supposed to use something like
    // a hash map to do this. Have to do it
    // the long way.
    int shift_val;

    switch(toupper(c)) {

    case 'A' :
      shift_val = 0;
       break;
    case 'B' :
       shift_val = 1;
       break;
    case 'C' :
       shift_val = 2;
       break;
    case 'D' :
       shift_val = 3;
       break;
    case 'E' :
       shift_val = 4;
       break;
    case 'F' :
       shift_val = 5;
       break;
    case 'G' :
      shift_val = 6;
       break;
    case 'H' :
       shift_val = 7;
       break;
    case 'I' :
       shift_val = 8;
       break;
    case 'J' :
       shift_val = 9;
       break;
    case 'K' :
       shift_val = 10;
       break;
    case 'L' :
       shift_val = 11;
       break;
    case 'M' :
       shift_val = 12;
       break;
    case 'N' :
       shift_val = 13;
       break;
    case 'O' :
       shift_val = 14;
       break;
    case 'P' :
       shift_val = 15;
       break;
    case 'Q' :
       shift_val = 16;
       break;
    case 'R' :
       shift_val = 17;
       break;
    case 'S' :
       shift_val = 18;
       break;
    case 'T' :
       shift_val = 19;
       break;
    case 'U' :
       shift_val = 20;
       break;
    case 'V' :
       shift_val = 21;
       break;
    case 'W' :
       shift_val = 22;
       break;
    case 'X' :
       shift_val = 23;
       break;
    case 'Y' :
       shift_val = 24;
       break;
    case 'Z' :
       shift_val = 25;
       break;
    default :
       shift_val = 99;
   }
    if (shift_val == 99){
        printf("Invalid value passed\n" );
        exit(0);
    }
    return shift_val;

}
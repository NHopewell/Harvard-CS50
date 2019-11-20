#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int check_args(int c);
char build_arr_1(string letters);
string build_arr_2(string letters);
string build_arr_3(string letters);
string build_arr_4(string letters);

int main(int argc, string argv[])
{
    int ck = check_args(argc);
    
    if (ck != 0) { 
        exit(1); 
    }
    
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    build_arr_1(letters);
    build_arr_2(letters);
    build_arr_3(letters);
    build_arr_4(letters);
    
    string fail = "Could not crack this password";
    printf("%s", fail);  
    
}

int check_args(int c){
    if (c < 2 || c > 2) {
        string usage = "Usage: ./crack hash";
        printf("%s", usage);
        return 1;
    }
    return 0;
}

int check_hash(string hash, string encrypted){
    
    int n = strlen(hash);
    for (int i = 0; i < n; i++){
        if (hash[i+2] != encrypted[i]){
            return 0;
        }
    }
    return 1;
}

char build_arr_1(string letters){
    const int N_LETS = strlen(letters);
    string to_encrypt[2];
    
    for (int i = 0; i < N_LETS; i++){
         to_encrypt[0] = letters[i];
         char encrypted = crypt(to_encrypt, 'test');
         int check = check_hash(argv[1], encrypted);
         
         if (check == 1) {
                return letters[i]; }}
}

string build_arr_2(string letters) {
    const int N_LETS = strlen(letters);
    string to_encrypt[3];
    
    for (int i = 0; i < N_LETS; i++){
        to_encrypt[0] = letters[i]
        for (int j = 0; j < N_LETS; j++){
            to_encrypt[1] = letters[j]
            
            string encrypted = crypt(to_encrypt, 'test');
            int check = check_hash(argv[1], encrypted);
            
            if (check == 1) {
                   return to_encrypt; }}}
}

string build_arr_3(string letters) {
    const int N_LETS = strlen(letters);
    string to_encrypt[4];
    
    for (int i = 0; i < N_LETS; i++){
        to_encrypt[0] = letters[i]
        for (int j = 0; j < N_LETS; j++){
            to_encrypt[1] = letters[j]
            for (int k = 0; k < N_LETS; k++){
                to_encrypt[2] = letters[k]
               
                string encrypted = crypt(to_encrypt, 'test');
                int check = check_hash(argv[1], encrypted);
                
                if (check == 1) {
                       return to_encrypt; }}}}

}

string build_arr_3(string letters) {
    const int N_LETS = strlen(letters);
    string to_encrypt[5];
    
    for (int i = 0; i < N_LETS; i++){
        to_encrypt[0] = letters[i]
        for (int j = 0; j < N_LETS; j++){
            to_encrypt[1] = letters[j]
            for (int k = 0; k < N_LETS; k++){
                to_encrypt[2] = letters[k]
                for (int l = 0; l < N_LETS; l++){
                    to_encrypt[3] = letters[l]
                        
                    string encrypted = crypt(to_encrypt, 'test');
                    int check = check_hash(argv[1], encrypted);
                    
                    if (check == 1) {
                           return to_encrypt; }}}}}

}



/*
Use the Coleman-Liau Index to calculate the reading level of an input text.

index = (0.0588 * L) - (0.296 * S) - 15.8

L is the average number of letters per 100 words in the text.
S is the average number of sentences per 100 words in the text.

First, must count up how many words, letters, and sentences there are. Then
plug them into the formula and use the result to return a reading level.

step 1) count number of letters in a text:
    Count the number of upper and lowercase letters, ignoring spaces and
    punctuation. nLetters = 0, loop through text, ask if its an ascii upper
    or lower char, increase count. If not, dont increase count.
    include ctype.h and use isalpha().

step 2) count how many words in text:
    Count number of words.
    Any sequence of characters seperated to one or more spaces is a word.
    nWords = 1. if i == space and isalpha(i+1), increment count.

step 3) count number of sentences in text:
    nSentences = 0.
    Any period, exclaimation mark, or question mark indicates a sentence.
    dont use ispunct(), match exactly or write a new function to match.

Calculating the index:
    L = (nLetters / nWords) * 100
    S = (nSentences / baseNum) * 100

Output:
    Must round the number to the nearest whole number first.
    Should output "Grade x"
    If the output is < 1, should output "Before Grade 1"
    If output is >= 16, should output "Grade 16+"

*/
# include <cs50.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include <math.h>

float lettersPerHundredWords(int nLetters, int nWords);
float sentencesPerHundredWords(int nSentences, int Words);
int computeCLI(float L, float S);
void printReadingLevel(int CLI);

int main(int argc, string argv[]){

    int nLetters = 0;
    int nWords = 1;
    int nSentences = 0;

    // prompt user for text with get_string()
    string userText = get_string("Please enter text: ");

    // count num letters
    for (int i = 0, textLen = strlen(userText); i < textLen; i++){
        if isalpha(userText[i]) {
            nLetters++;
        }
    }
    // count num words
    for (int i = 0, textLen = strlen(userText); i < textLen; i++){
        if (userText[i] == ' ') {
            nWords++;
        }
    }
    // count num sentences
    for (int i = 0, textLen = strlen(userText); i < textLen; i++){
        if (userText[i] == '.' || userText[i] == '!' || userText[i] == '?') {
            nSentences++;
        }
    }
    // calc avg letters per 100 words
    float L = lettersPerHundredWords(nLetters, nWords);
    // calc avg sentences per 100 words
    float S = sentencesPerHundredWords(nSentences, nWords);
    // compute CLI
    int CLI = computeCLI(L, S);
    // return reading level (include Text :  and reading level)
    printReadingLevel(CLI);

}

float lettersPerHundredWords(int nLetters, int nWords){
    // L = (nLetters / nWords) * 100
    return ((float)nLetters / nWords) * 100;
}

float sentencesPerHundredWords(int nSentences, int nWords){
    // S = (nSentences / nWords) * 100
    return ((float)nSentences / nWords) * 100;
}

int computeCLI(float L, float S){
    // index = (0.0588 * L) - (0.296 * S) - 15.8
    // MUST ROUND TO NEAREST WHOLE NUMBER
    float CLI = (0.0588 * L) - (0.296 * S) - 15.8;
    return round(CLI);
}

void printReadingLevel(int CLI){
    // return reading level
    // If the output is < 1, should output "Before Grade 1"
    // If output is >= 16, should output "Grade 16+"
    if (CLI < 1) {
        printf("Before Grade 1\n");
    }
    else if (CLI >= 16){
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", CLI);
    }

}

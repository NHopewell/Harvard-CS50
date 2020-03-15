#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // if all rbg vals are the same, you have a shade of grey
    // take the average of r g and b and set r g and b to that val
    // must round to nearest int - include math.h

    // iterate over rows of 2d array
    for (int i = 0; i < height; i++){
        // iterate over cols of 2d array
        for (int j = 0; j < width; j++){
            // store rbg vals
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            // calc avg and round
            float rgbAvg = (float)(red + green + blue) / 3;
            int roundedAvg = round(rgbAvg);
            // set each of the triples to the rounded avg
            image[i][j].rgbtRed = roundedAvg;
            image[i][j].rgbtGreen = roundedAvg;
            image[i][j].rgbtBlue = roundedAvg;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate over rows of 2d array
    for (int i = 0; i < height; i++){
        // iterate over cols of 2d array
        for (int j = 0; j < width; j++){
            // store rbg vals
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            // calc sep rbgs, make sure its in 8bit range
            float sepRed = (0.393 * red) + (0.769 * green) + (0.189 * blue);
            if (sepRed > 255){sepRed = 255;}
            float sepGreen = (0.349 * red) + (0.686 * green) + (0.168 * blue);
            if (sepGreen > 255){sepGreen = 255;}
            float sepBlue = (0.272 * red) + (0.534 * green) + (0.131 * blue);
            if (sepBlue > 255){sepBlue = 255;}
            // set each of the triples to the sep version
            image[i][j].rgbtRed = round(sepRed);
            image[i][j].rgbtGreen = round(sepGreen);
            image[i][j].rgbtBlue = round(sepBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = 0;

    // if width is an odd number, floor the division
    if (width % 2 != 0){
        mid += floor( (float)width / 2 );
    // if even, divide and add 1
    } else {
        mid += (width / 2);
    }

    // iterate over rows of 2d array
    for (int i = 0; i < height; i++){
        // iterate over cols of 2d array, up to mid
        for (int j = 0; j < mid; j++){
            // store left side rbgts
            int left_red = image[i][j].rgbtRed;
            int left_green = image[i][j].rgbtGreen;
            int left_blue = image[i][j].rgbtBlue;
            // store right side rgbts
            int right_red = image[i][(width - 1) -j].rgbtRed;
            int right_green = image[i][(width - 1) -j].rgbtGreen;
            int right_blue = image[i][(width - 1) -j].rgbtBlue;
            // swap left for right
            image[i][j].rgbtRed = right_red;
            image[i][j].rgbtGreen = right_green;
            image[i][j].rgbtBlue = right_blue;
            // swap right for left
            image[i][(width - 1) -j].rgbtRed = left_red;
            image[i][(width - 1) -j].rgbtGreen = left_green;
            image[i][(width - 1) -j].rgbtBlue = left_blue;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a second 2d array copy of the image
    RGBTRIPLE copyOfImage[height][width];
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            // copy rbgtriples exactly
            copyOfImage[i][j] = image[i][j];
        }
    }
    // iterate over rows
    for (int i = 0; i < height; i++){
        // iterate over cols
        for (int j = 0; j < width; j++){
            // intialize all rbg vals to div by counter
            int allReds = 0;
            int allGreens = 0;
            int allBlues = 0;
            int counter = 0;

            // if condition met, increment counter. do not other wise
            if (i >= 0 && j >= 0){
                counter++;
                // simple case, grab matching rbgs
                allReds += copyOfImage[i][j].rgbtRed;
                allGreens += copyOfImage[i][j].rgbtGreen;
                allBlues += copyOfImage[i][j].rgbtBlue;
            }
            if (i >= 0 && j - 1 >= 0){
                counter++;
                // one col to left
                allReds += copyOfImage[i][j-1].rgbtRed;
                allGreens += copyOfImage[i][j-1].rgbtGreen;
                allBlues += copyOfImage[i][j-1].rgbtBlue;
            }
            if ( (i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width) ){
                counter++;
                // one col to right
                allReds += copyOfImage[i][j+1].rgbtRed;
                allGreens += copyOfImage[i][j+1].rgbtGreen;
                allBlues += copyOfImage[i][j+1].rgbtBlue;
            }
            if (i - 1 >= 0 && j >= 0){
                counter++;
                // one row up
                allReds += copyOfImage[i-1][j].rgbtRed;
                allGreens += copyOfImage[i-1][j].rgbtGreen;
                allBlues += copyOfImage[i-1][j].rgbtBlue;
            }
            if (i - 1 >= 0 && j - 1 >= 0){
                counter++;
                // one row up, one col ot left
                allReds += copyOfImage[i-1][j-1].rgbtRed;
                allGreens += copyOfImage[i-1][j-1].rgbtGreen;
                allBlues += copyOfImage[i-1][j-1].rgbtBlue;
            }
            if ( (i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width) ){
                counter++;
                // one row up, one col to right
                allReds += copyOfImage[i-1][j+1].rgbtRed;
                allGreens += copyOfImage[i-1][j+1].rgbtGreen;
                allBlues += copyOfImage[i-1][j+1].rgbtBlue;
            }
            if ( (i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0) ){
                counter++;
                // one row down
                allReds += copyOfImage[i+1][j].rgbtRed;
                allGreens += copyOfImage[i+1][j].rgbtGreen;
                allBlues += copyOfImage[i+1][j].rgbtBlue;
            }
            if ( (i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0) ){
                counter++;
                // one row down, one col to left
                allReds += copyOfImage[i+1][j-1].rgbtRed;
                allGreens += copyOfImage[i+1][j-1].rgbtGreen;
                allBlues += copyOfImage[i+1][j-1].rgbtBlue;
            }
            if ( (i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width) ){
                counter++;
                // one row down, one col to right
                allReds += copyOfImage[i+1][j+1].rgbtRed;
                allGreens += copyOfImage[i+1][j+1].rgbtGreen;
                allBlues += copyOfImage[i+1][j+1].rgbtBlue;
            }
            // we now have entire grid around pixel (if they can be found)

            // replace pixel at jth position of row i with avg rbg vals
            // totalled above, dividing by the counter.
            image[i][j].rgbtRed = round( allReds / ((float)counter) );
            image[i][j].rgbtGreen = round( allGreens / ((float)counter) );
            image[i][j].rgbtBlue = round( allBlues / ((float)counter) );
        }
    }

    return;
}

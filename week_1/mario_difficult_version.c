// A simple algorithm to printf a mario-like pyramid
// with hashes of the height specified by the user.
// Pyramid cannot be left alligned and its base
// must increment by 2 hashes per teir of the pyramid.
// Pyramid must also have 2 spaces in the middle of each
// teir. Height can only be between 1 and 8.

// Example:
// >>>> User enters a height of 4.
//   #  #
//  ##  ##
// ###  ###
//####  ####

#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int pyramid_height;

		do {    // prompt user for height 
		        pyramid_height = get_int(
				"How tall should the pyramid be? \
				(pick a number less than 9)\n");
		} while (pyramid_height < 1 || pyramid_height > 8);

		int count = 1;
		while (count <= pyramid_height){
			// print one less space than height, decrement
			for (int i = pyramid_height-count; i > 0; i--){
				printf(" ");
				}
			// print count hashes
			for (int i = 1; i < count+1; i++){
				printf("#");
				} printf("  "); // print 2 spaces
			// print count hashes
			for (int i = 1; i < count+1; i++){
				printf("#");
				} printf("\n"); // print newline
		// increment count
		count += 1;        
		}
}

#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int pyramid_height;

		do{
			pyramid_height = get_int("How tall should the pyramid be? (pick a number less than 9)\n");
		} while( pyramid_height<1 || pyramid_height>8 );

		int count = 1;
		while(count <= pyramid_height){
			for(int i=pyramid_height-count; i>0; i--){
				printf(" ");
				} 
			for(int i=1; i<count+1; i++){
				printf("#");
				} printf("  ");
			for(int i=1; i<count+1; i++){
				printf("#");
				} printf("\n");
		count += 1;        
		}
}

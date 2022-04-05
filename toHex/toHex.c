#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    //
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // first, read the number
    signed short int input;
    fscanf(fp, "%hd", &input); // note how the 'h' modifier shortens the %d to half size
    // int array[16];
    // print bits; you will see this kind of for loop often in this assignment
    // for(signed short int input = -32768; input < 32767; input++ ){
      for ( int digit=12; 0<=digit; digit-=4 ) {
          int char_val = 0xF & input>>digit; // shift and mask
          // array[digit] = char_value;
          if( char_val > 9){
            printf("%c", 55+char_val);
          }
          else{
            printf("%d",char_val);
          }
        }
        printf("\n");
    // }

    // useful hints for printing uppercase hexadecimal
    // printf("The character value of '0' = %d\n",'0');
    // printf("The character value of 'A' = %d\n",'A');

    return EXIT_SUCCESS;

}

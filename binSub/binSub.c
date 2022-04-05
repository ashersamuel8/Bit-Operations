#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        minuend[i] = buff - 48;
        // printf("%d",minuend[i]);
    }
    // puts("");
    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp, "%c", &buff);
    // second, read the subtrahend (number to subtract)
    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        fscanf(fp, "%c", &buff);
        subtrahend[i] = !(buff - 48);
        // printf("%d", subtrahend[i]);
    }
    // puts("");
    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    /* ... */
    // printf("%d\n",minuend[0]^subtrahend[0]);
    // add one
    bool difference[8];
    bool carry = false; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
        /* ... */
        if((minuend[i]^subtrahend[i]) && !carry){
          difference[i] = 1;
        }
        else if((minuend[i]^subtrahend[i]) && carry){
          difference[i] = 0;
        }
        else if(minuend[i] == 1 && subtrahend[i] == 1 && carry){
          difference[i] = 1;
        }
        else if(minuend[i] == 1 && subtrahend[i] == 1 && !carry){
          difference[i] = 0;
          carry = true;
        }
        else if(minuend[i] == 0 && subtrahend[i] == 0 && carry){
          difference[i] = 1;
          carry = false;
        }
        else if(minuend[i] == 0 && subtrahend[i] == 0 && !carry){
          difference[i] = 0;
        }
    }

    for(int i = 0; i < 8; i++){
        if(difference[i] == 1){
           difference[i] = 0;
        }
        else{
          difference[i] = 1;
          break;
        }
    }

    // Add the minuend and the negated subtrahend

    /* ... */

    // print the difference bit string
    for (int i=7; 0<=i; i--)
        printf("%d",difference[i]);

    return EXIT_SUCCESS;

}

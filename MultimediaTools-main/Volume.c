// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

//Change the name of the function below to volume.c
int volume()
{
    char in[50], out[50];
    printf("Enter the input file\n");
    scanf("%s",in);

    // Open files and determine scaling factor
    FILE *input = fopen(in, "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    printf("Enter the output file\n");
    scanf("%s",out);

    FILE *output = fopen(out, "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    /*
    printf("Do you want to change the volume?[y/n]\n");
    char ch;
    scanf("%c",&ch);
    if(ch == 'y'){
        //Put the code below in a do while loop
    }
    */

    float factor = 1;
    printf("Enter the factor by which you want to change volume ");
    scanf("%f",&factor);
    
    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, sizeof(uint8_t), input);
    fwrite(header, HEADER_SIZE, sizeof(uint8_t), output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t audio;
    while(fread(&audio, sizeof(int16_t), 1, input)){
        audio *= factor;
        fwrite(&audio, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("User input error.\n");
        return 1;
    }
    
    int Spacing = 512;
    BYTE buffer[Spacing];
    int nPics = 0;

    // filename passed at terminal
    char *userFIle = argv[1];

    // inside the users file
    FILE *userFileCon = fopen(userFIle, "r");
    if (userFileCon == NULL){
        printf("File could not be opened.\n");
        return 1;
    }
    // char arr size 8
    char filename[8];
    FILE *outF = NULL;

    while (true)
    {
        // take a chunk at a time 
        size_t chunk = fread(buffer, sizeof(BYTE), Spacing, userFileCon);

        // must exit if at end of some pic
        if (chunk == 0 && feof(userFileCon)){
            break;
        }
        // is this file a JPEG file?
        bool isJPEG = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
        // fclose las jpeg found
        if (isJPEG && outF != NULL){
            fclose(outF);
            nPics++;
        }
        // open JPEG file 
        if (isJPEG){
            sprintf(filename, "%03i.jpg", nPics);
            outF = fopen(filename, "w");
        }
        // write to any open parsible file
        if (outF != NULL){
            fwrite(buffer, sizeof(BYTE), chunk, outF);
        }
    }
    fclose(outF);
    fclose(userFileCon);

    return 0;
}
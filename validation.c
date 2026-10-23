#include "header.h"

int read_and_validation(int argc, char *argv[], Flist **head)
{
    for(int i = 1; i < argc; i++)
    {
        printf("---------------------------------------------------------------------\n");

        // check argv[i] extension is .txt or not 
        char *extn = strrchr(argv[i], '.');

        if(extn != NULL && strcmp(extn, ".txt") == 0)
        {    
            // check the file is present or not
            FILE *fptr = fopen(argv[i], "r");
            if(fptr != NULL)
            {
                // check file is empty or not 
                fseek(fptr, 0, SEEK_END);
                if(ftell(fptr))
                {
                    int res = insert_filename(argv[i], head);
                    if(res == SUCCESS)
                        printf("Successful : inserting file name : %s into file linked list \n", argv[i]);
                    else if(res == DUPLICATE)
                        printf("%s is already present\n", argv[i]);
                    else
                    {
                        printf("%s is not inserted in flist\n", argv[i]);
                        fclose(fptr);
                        return FAILURE;
                    }
                }
                else
                {
                    printf("%s file is empty\n", argv[i]);
                    
                }
            }
            else
            {
                printf("%s file is not present\n", argv[i]);
                
            }
        }
        else
        {
            printf("%s is not .txt file\n", argv[i]);
            
        }
    }

    printf("---------------------------------------------------------------------\n\n");

    return SUCCESS;
}


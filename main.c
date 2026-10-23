/*
Project Title : Inverted Search
Description :
The Inverted Search project is a menu-driven C program that indexes words from multiple 
text files so that any word can be searched quickly. Instead of scanning every file each time,
it stores for each word the files that contain it and how many times it appears in each. 
The index is a 27-slot hash table (one slot per letter plus one for other characters), 
where each slot holds a linked list of words and each word holds a linked list of files with counts. 
The program validates input files, and lets the user create, display, search, update and save the database, 
using concepts like hashing, linked lists, dynamic memory allocation and file handling.
*/
#include "header.h"

int main(int argc, char *argv[])
{
    // Head pointer for the linked list containing input file names
    Flist *head = NULL;

    // Flag to keep track of whether the database is created
    int created_flag = 0;

    // Hash table with 27 indexes
    // 0-25 -> alphabets A-Z // 26 -> other characters
    Hash_t ht[27];

    // Initialize the hash table
    for(int i = 0; i <27; i++)
    {
        ht[i].index = i;
        ht[i].link = NULL;
    }

    // validates files from CLA input
    read_and_validation(argc, argv, &head);

    //checking whether we have any valid .txt files with us
	//If no valid files found, terminate the programme
	if(!head)
	{
		printf("Input Files are (Invalid or Empty)\n");
		printf("Usage: ./a.out <file_name.txt> <file_name2.txt>\n");
		return FAILURE;
	}

    // Display the names of all valid input files
    printf("Valid Input Files are:\n");
	print_filenames(head);

    
    int choice;
    char ch;
    while(1)
    {
        printf("\n====== INVERTED SEARCH MENU ======\n\n");
        printf("Select your choice among following options:\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                // Check whether database is already created
                if(created_flag)
                {
                    printf("Database is already created.\n");
                }
                // Create the inverted database using all valid files
                else if(create_db(head, ht) == SUCCESS)
                {
                    created_flag = 1;
                }
                break;

            case 2:
                // Display database 
                // Database must be created before displaying it
                if(!created_flag)
                {
                    printf("Database is not created yet. Choose option 1 first.\n");
                    break;
                }

                // Display the complete inverted database
                display_db(ht);
                break;

            case 3:
                // Search database 
                // Database must be created before searching
                if(!created_flag)
                {
                    printf("Database is not created yet. Choose option 1 first.\n");
                    break;
                }

                // Read the word that the user wants to search
                printf("Enter word to search: ");
                char searchWord[100];   
                scanf("%s", searchWord);

                // Search the word in the inverted database
                if(search_db(ht, searchWord) == NOT_FOUND)
                {
                    printf("Not found : (%s) word not present in database\n", searchWord);
                }
                break;

            case 4:
                // Ask the user for a new file name
                printf("Enter the file name to update database: ");
                char updateFile[100];
                scanf("%99s", updateFile);

                // Already in the database? Then do nothing.
                if(is_file_present(head, updateFile))
                {
                    if(created_flag)
                    {
                        // option 1 already built every file in Flist
                        printf("%s is already present in the database. Update skipped.\n", updateFile);    
                    }
                    else
                    {
                        if(create_db(head, ht) == SUCCESS)
                            created_flag = 1;
                    }
                    break;
                }

                // Validate (.txt, exists, not empty) and add to Flist
                read_and_validation(2, (char *[]){argv[0], updateFile}, &head);

                // Validation rejected it, so nothing to build
                if(!is_file_present(head, updateFile))
                {
                    break;
                }

                if(created_flag)
                {
                    // database exists: build only this new file
                    update_db(&head, ht, updateFile);
                }
                else
                {
                    // database not created yet: build all files (including this one)
                    if(create_db(head, ht) == SUCCESS)
                    {
                        created_flag = 1;
                    }
                }
                break;

            case 5:
                // Save database 
                if(!created_flag)
                {
                    printf("Database is not created yet. Choose option 1 first.\n");
                    break;
                }

                // Ask the user for the file name in which the database should be saved
                printf("Enter the filename to save the database: ");
                char saveFile[100];
                scanf("%s", saveFile);

                // Find the extension of the entered filename
                char *extn = strrchr(saveFile, '.');
                // Check whether the filename has .txt extension
                if(extn == NULL || strcmp(extn, ".txt") != 0)
                {
                    printf("ERROR: Invalid file format. Please enter a .txt file.\n");
                }
                else
                {
                    if(save_database(ht, saveFile) == FAILURE)
                    {
                        printf("ERROR: Failed to save database to %s\n", saveFile);
                    }
                    else
                    {
                        printf("Database saved successfully to %s\n", saveFile);
                    }
                }
                break;
            case 6:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }

        printf("\nDo you want to continue ?\n");
        printf("Enter y/Y to continue and n/N to discontinue\n");
        scanf(" %c", &ch);      
        if(ch == 'n' || ch == 'N')
        {
            printf("Exiting...\n");
            break;   
        }
        
    }
    
    
    return 0;
}
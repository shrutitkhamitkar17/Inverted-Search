#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define NOT_FOUND -2
#define DUPLICATE -3

//FileList Node struct
typedef struct node
{
    char *arr;
    struct node *link;
}Flist;

//sub node
typedef struct sub_node
{
    int wordcount;
    char *filename;
    struct sub_node *link;
}Slist;

//main Node
typedef struct main_node
{
    int fileCount;
    char *word;
    struct main_node *link;
    Slist *sublink;
}Mlist;

// Hash table struct
typedef struct hash_table
{
    int index;
    Mlist *link;
} Hash_t;

// Function declarations

// Reads command-line files and validates them
int read_and_validation(int argc, char *argv[], Flist **head);

// Inserts a valid file name into the file list
int insert_filename(char *file_name, Flist **head);

// Displays all valid file names
int print_filenames(Flist *head);

// Checks whether a file is already present in the file list
int is_file_present(Flist *head, char *filename);

// Creates the inverted database using the input files
int create_db(Flist *head, Hash_t *hashTable);

// Displays the complete inverted database
int display_db(Hash_t *ht);

// Searches for a word in the inverted database
int search_db(Hash_t *ht, char *word);

// Saves the inverted database into a file
int save_database(Hash_t *ht, char *filename);

// Updates the database with a new input file
int update_db(Flist **f_head, Hash_t *ht, char *updateFile);

#endif

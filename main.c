// Include required libraries
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Include ADT
#include "tree.h"

// Driver Code
int main(int argc, char *argv[])
{
      // Storing the path name
      char name[MAX];
      // if argc = 1 --> print all files/folders in current directory
      if (argc == 1)
      {
            node *start = create_node(".");
            start->isdir = 1;
            // getting the current working directory --> generating tree
            start->nextDirectory = create_tree(getcwd(0, 0));
            // print the tree with indentation
            print_tree(start);
            // Enlist files and folders
            num_dir_files();
      }

      /*when ms-tree -i is passed --> print all files/folders in current dir*/
      if (argc >= 2 && strcmp(argv[1], "-i") == 0)
      {
            node *start = create_node(".");
            start->isdir = 1;
            // Path to the directory
            printf("Enter path to list files: ");
            scanf("%s", name);
            // creating a tree from specified path
            start->nextDirectory = create_tree(name);
            // printing the tree with indentation
            print_tree(start);
            num_dir_files();
      }

      /*when ms-tree -u is passed --> enlist user details*/
      if (argc >= 2 && strcmp(argv[1], "-u") == 0)
      {
            // take path
            printf("Enter path to list files: ");
            scanf("%s", name);
            // print name of user
            get_username(name);
            printf("\n");
      }

      /*when ms-tree -help is passed --> display the help*/
      if (argc >= 2 && strcmp(argv[1], "-help") == 0)
      {
            printf("\nThis is the help section: \n");
            printf("\nWithout flags it prints all the files/folders in current directory\n");
            printf("\nThe various flags are : \n");
            printf("\n-i : Prints all the files and folders recursively in tree format\n");
            printf("\n-u : user details \n");
            printf("\n-v : prints the version of the tree\n");
            printf("\n-help : prints the help section\n\n");
            printf("\n-cf : Print all the compressed files in hierchial manner\n");
            printf("\n-pf : Prints all the program files in tree hierchial structure\n");
            printf("\n-d : This prints all the folders in a given directory\n");
      }

      /* when ms-tree -v is passed --> display the version */
      if (argc >= 2 && strcmp(argv[1], "-v") == 0)
      {
            printf("M.S. tree 1.0.2 (default, Nov 2 2021) \n");
            printf("[GCC 9.3.0] on ubuntu \n");
            printf("Type \"-help\" for more information.\n");
            printf("This is free software with ABSOLUTELY NO WARRANTY.\n\n");
      }

      /*when ms-tree -cf is passed this --> show file tree only with compressed files 
      eg. .zip,.rar etc*/
      if (argc >= 2 && strcmp(argv[1], "-cf") == 0)
      {
            node *start = create_node(".");
            start->isdir = 1;
            // take path
            printf("Enter the path to list all files : ");
            scanf("%s", name);
            // Create the tree
            start->nextDirectory = create_tree(name);
            // Display the tree with only compressed files
            print_tree_compressed(start);
            num_dir_files();
      }

      /*when ms-tree -pf is passed --> show file tree only with code files eg. .c,.o,.js  etc.*/
      if (argc >= 2 && strcmp(argv[1], "-pf") == 0)
      {
            node *start = create_node(".");
            start->isdir = 1;
            // take path
            printf("Enter the path to list all files : ");
            scanf("%s", name);
            // create the tree
            start->nextDirectory = create_tree(name);
            // Display the tree with only compressed files
            print_tree_programs(start);
            num_dir_files();
      }

      /*when ms-tree -d is passed --> show file tree only with directories */
      if (argc >= 2 && strcmp(argv[1], "-d") == 0)
      {
            node *start = create_node(".");
            start->isdir = 1;
            // take path
            printf("Enter the path to list all files : ");
            scanf("%s", name);
            // create the tree
            start->nextDirectory = create_tree(name);
            // Display the tree with only directories
            print_directories(start);
            num_dir_files();
      }
      // return exit status
      return 0;
}
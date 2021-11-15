// Include required libraries
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>

// ADT of the fs tree
#include "tree.h"

// Coloring
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"

// count, number of files and folders
int count = 0;
int num_dir = 0;
int num_files = 0;

// function to create node once a path is passed
node *create_node(char *n)
{
	// allocating space
	node *temp = (node *)malloc(sizeof(node));
	// name of directory
	temp->name = n;
	// setting next directory and file null
	temp->nextDirectory = NULL;
	temp->nextFile = NULL;
	// returning the newnode
	return temp;
}

// recursive function to create an fs tree
node *create_tree(char *root_name)
{
	// DIR *opendir(const char *dirname) --> opens the directory stream corresponding to
	// the root_name
	// returns a pointer of dir type if operation is successful else NULL returned
	DIR *dir = opendir(root_name);

	// struct dirent contains various members which are used
	// in the code d_type,d_name etc
	struct dirent *dr = NULL;

	// root node
	node *root, *temp, *temp1;
	root = temp = temp1 = NULL;
	// name
	char *name = (char *)malloc(sizeof(char) * MAX);

	// if error in opening --> print error, return NULL
	if (dir == NULL)
	{
		printf("Error: opening directory\n");
		return NULL;
	}

	// Loop to enlist all contents of the directory
	while ((dr = readdir(dir)) != NULL)
	{

		/* "." and ".."  cannot be parsed further*/
		// if dir != "." or ".." --> create a node
		if (strcmp((dr->d_name), ".") != 0 && strcmp((dr->d_name), "..") != 0)
		{
			temp = create_node(dr->d_name);
		}
		// else --> stop further parsing
		else
		{
			temp = NULL;
			// force iteration here
			continue;
		}
		// updating the follower pointer
		if (temp1 != NULL)
		{
			temp1->nextFile = temp; 
		}
		// when reaches null --> set value of root as temp
		else
		{
			root = temp; 
		}

		// Checking if a node is a directory
		if ((dr->d_type) == DT_DIR)
		{ 
			// if the dr type = DT_DIR --> isdir = 1, name = root_name
			temp->isdir = 1;
			strcpy(name, root_name);
			// Recursively call create tree till we reach the inner most one
			temp->nextDirectory = create_tree((strcat((strcat(name, "/")), dr->d_name)));
		}
		// else --> isdir = 0 , stop parsing
		else
		{
			temp->isdir = 0;
			temp->nextDirectory = NULL;
		}
		// keep setting temp1 as temp
		temp1 = temp;
	}
	return root;
}

// function to print the fs tree
void print_tree(node *start)
{
	node *temp = start; //start is the root node from where tree is to be printed

	if (start == NULL)
		return; // if no root node exists return

	temp->level = count; //setting level to count which initially is 0
	printf("\n");

	for (int i = 0; i < count - 1; i++)
		printf("│   "); // if directory this indentation provided

	if (count > 0)
		printf("├── "); //if file then this indentation

	printf("%s  ", temp->name); //print name of the given dir/file

	//Checks if it's a directory
	if (temp->isdir == 1)
	{
		num_dir += 1;					 //increament by 1 as temp is a dir
		count++;						 //increament count
		print_tree(temp->nextDirectory); //recursively print tree for the nextdirectory
		count--;
	}

	num_files += 1;				//increament the num of files
	print_tree(temp->nextFile); //print tree recursively for next file
}

// function to get the user details of a path (username, group id,user id)
void get_username(char *path)
{
	struct stat stats;	//retrive info about the file pointed by the path name
	stat(path, &stats); //reads all props and dumps it into string buffer stats
	struct passwd *pwuser;
	pwuser = getpwuid(stats.st_uid);
	printf("USER ID = %u\n", pwuser->pw_uid);
	printf("Group ID = %u\n", pwuser->pw_gid);
	printf("USERNAME : %s\n", pwuser->pw_name);
}

// function to print compressed file tree
void print_tree_compressed(node *start)
{

	node *temp = start; //start is the root node from where tree is to be printed

	if (start == NULL)
		return; // if no root node exists return

	//setting level to count which initially is 0
	temp->level = count;

	printf("\n");

	for (int i = 0; i < count - 1; i++)
		printf("│   "); // if directory this indentation provided

	if (count > 0)
		printf("├── ");

	if (strstr(temp->name, ".7z") || strstr(temp->name, ".arj") || strstr(temp->name, ".deb") ||

		strstr(temp->name, ".pkg") || strstr(temp->name, ".rar") || strstr(temp->name, ".rpm") ||

		strstr(temp->name, ".tar.gz") || strstr(temp->name, ".z") || strstr(temp->name, ".zip"))
	{

		printf("%s%s\n", ANSI_COLOR_YELLOW, temp->name);
		num_files += 1;
	}
	else
	{
		printf("%s", ANSI_COLOR_MAGENTA);
	}

	if (temp->isdir == 1)
	{
		num_dir += 1; //increament number of dirs in tree
		count++;
		print_tree_compressed(temp->nextDirectory);
		count--;
	}

	print_tree_compressed(temp->nextFile);
}

// function to print program file tree
void print_tree_programs(node *start)
{

	node *temp = start; //start is the root node from where tree is to be printed
	if (start == NULL)
		return; // if no root node exists return

	//setting level to count which initially is 0
	temp->level = count;

	printf("\n");

	for (int i = 0; i < count - 1; i++)
		printf("│   "); // if directory this indentation provided

	if (count > 0)
		printf("├── ");

	if (strstr(temp->name, ".class") || strstr(temp->name, ".css") || strstr(temp->name, ".json")

		|| strstr(temp->name, ".iml") || strstr(temp->name, ".bash") || strstr(temp->name, ".o")

		|| strstr(temp->name, ".layout") || strstr(temp->name, ".cbp") || strstr(temp->name, ".depend")

		|| strstr(temp->name, ".ts") || strstr(temp->name, ".c") || strstr(temp->name, ".h") ||

		strstr(temp->name, ".cpp") || strstr(temp->name, ".java") || strstr(temp->name, ".php") ||

		strstr(temp->name, ".py") || strstr(temp->name, ".sh") || strstr(temp->name, ".swift") ||

		strstr(temp->name, ".vb") || strstr(temp->name, ".js"))
	{

		printf("%s%s", ANSI_COLOR_RESET, temp->name);
		num_files += 1;
	}
	else
	{
		printf("%s\n", ANSI_COLOR_BLUE);
	}

	if (temp->isdir == 1)
	{
		num_dir += 1; //increament number of dirs in tree
		count++;
		print_tree_programs(temp->nextDirectory);
		count--;
	}

	print_tree_programs(temp->nextFile);
}

// function to print only directory file tree
void print_directories(node *start)
{

	node *temp = start; //start is the root node from where tree is to be printed

	if (start == NULL)
		return;

	//setting level to count which initially is 0
	temp->level = count;

	printf("\n");

	for (int i = 0; i < count - 1; i++)
		printf("│  "); // if directory this indentation provided

	if (count > 0)
		printf("├──"); //if file this indentation provided

	if (temp->isdir)
	{

		printf("%s \n", temp->name); //if it is a directory then only name is printed
	}

	if (temp->isdir == 1)
	{

		num_dir += 1; //increament number of dirs in tree
		count++;
		print_directories(temp->nextDirectory); //recursively keep calling this function if temp is dir
		count--;
	}

	num_files += 1;					   //increament number of dirs in tree
	print_directories(temp->nextFile); //recursively call for next file
}

// function to get number of files and directories
void num_dir_files()
{
	num_files = num_files - num_dir;
	num_dir = num_dir - 1;
	if(num_dir == 1)
	{
		printf("\n\n%d directory, %d files\n", num_dir, num_files);
	}
	else
	{
		printf("\n\n%d directories, %d files\n", num_dir, num_files);
	}
}
// Maximum characters in path name
# define MAX 100000

// Node of the tree
typedef struct node{
    // name of the given file/folder
    char* name;
    // is a directory or not
    int isdir;
    // pointer to the next directory of type node
    struct node *nextDirectory;
    // pointer to the next file of type node
    struct node *nextFile;
    // level of the tree
    int level;

}node;

// function to create node once a path is passed
node* create_node(char* n); 
// function to create a tree from the root onwards
node* create_tree(char *root); 
// function to print the fs tree
void print_tree(node *start); 
// function to get the user details of a path (username, group id,user id)
void get_username(char* path); 
// function to print compressed file tree
void print_tree_compressed(node *start); 
// function to print program file tree
void print_tree_programs(node *start); 
// function to print only directory file tree
void print_directories(node *start); 
// function to get number of files and directories
void num_dir_files();
void num_dir_files_cp();
// Header file created by NGO MINH TU
// Contain functions for double linked list


 typedef struct song_s{
 	char *name;
 	char *path;
 }*song_t;

 typedef struct song_list_node{
 	struct *song_list_node next;
 	struct *song_list_node prev;
 	song_t info;
 }*song_list_ptr;

 typedef struct list{
 	song_list_ptr front;
 	song_list_ptr back;
 } *list_ptr;

 song_list_ptr create_node()
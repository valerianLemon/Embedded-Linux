#ifndef SHARED_MEM
#define SHARED_MEM

#define SHM_SIZE 10000

extern int shm_fd;
extern int size;
extern int total_size_content;
extern void *shm_addr;
extern char *name;
extern char *content;

extern void create_shared_memory_object();
extern void add_to_shard_memory(char *file_name_to_add);
extern void list_files_initially ();


#endif
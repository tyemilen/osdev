#ifndef RAM_FS_
#define RAM_FS_

#define RFS_MAX_FILES_COUNT 256

#define RFS_OK 0
#define RFS_ERROR -1

#define RFS_FILE_NOT_EXISTS 0x01
#define RFS_FILE_ALREADY_EXISTS 0x02

#define RFS_FILE_TYPE_TEXT 0x001
#define RFS_FILE_TYPE_NULL 0x002

struct st_ramfs_entry {
    char* name;
    char* content;
    int type;
};

int rfs_create(char*, char*);
int rfs_read(char*, struct st_ramfs_entry*);
int rfs_find(char*, struct st_ramfs_entry*);
int rfs_exists(char*);
int rfs_count();


struct st_ramfs_entry* rfs_list();

#endif // RAM_FS_
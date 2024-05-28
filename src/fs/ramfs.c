#include "fs/ramfs.h"
#include "string.h"

#define RFS_MAX_FILES_COUNT 256

static struct st_ramfs_entry files[RFS_MAX_FILES_COUNT] = { 0 };
static int files_count = 0;

int rfs_count() {
    return files_count;
}

int rfs_create(char* name, char* content) {
    if (rfs_exists(name) == RFS_FILE_ALREADY_EXISTS) return RFS_FILE_ALREADY_EXISTS;

    struct st_ramfs_entry new_file = {
        .name = name,
        .content = content,
        .type = RFS_FILE_TYPE_TEXT
    };

    files[files_count] = new_file;

    files_count += 1;

    return RFS_OK;
}

int rfs_read(char* name, struct st_ramfs_entry* pfile) {
    struct st_ramfs_entry file = { 0 };

    int ret = rfs_find(name, &file);

    if (ret != RFS_OK) return ret;

    pfile->name = file.name;
    pfile->content = file.content;
    pfile->type = file.type;

    return RFS_OK;
}

int rfs_exists(char* name) {
    int ret = RFS_FILE_NOT_EXISTS;

    for (int i = 0; i < files_count; ++i) {
        if (strcmp(files[i].name, name) == 0) {
            ret = RFS_FILE_ALREADY_EXISTS;
            break;
        } 
    }

    return ret;
}

int rfs_find(char* name, struct st_ramfs_entry* pfile) {
    for (int i = 0; i < files_count; ++i) {
        if (strcmp(files[i].name, name) == 0) {
            pfile->name = files[i].name;
            pfile->content = files[i].content;
            
            return RFS_OK;
        } 
    }

    return RFS_FILE_NOT_EXISTS;
}


struct st_ramfs_entry* rfs_list() {
    return files;
}
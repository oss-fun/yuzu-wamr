#ifndef FD_CACHE_H
#define FD_CACHE_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef uint32_t __wasi_fd_t;

typedef enum {
    FD_SOURCE_NONE = 0,
    FD_SOURCE_OPEN,
    FD_SOURCE_ACCEPT,
} fd_source_t;

struct fd_cache_entry {
    __wasi_fd_t wasi_fd;
    int real_fd;      // os_file_handle を int に置き換え
    fd_source_t source;
};

#define MAX_CACHED_FDS 32

extern struct fd_cache_entry g_fd_cache[MAX_CACHED_FDS];
extern size_t g_fd_cache_used;

int fd_cache_insert(__wasi_fd_t wasi_fd, int real_fd, fd_source_t source);
int fd_cache_remove_by_wasi_fd(__wasi_fd_t wasi_fd);
struct fd_cache_entry* fd_cache_find_by_wasi_fd(__wasi_fd_t wasi_fd);
struct fd_cache_entry* fd_cache_find_by_source(fd_source_t source);
void fd_cache_dump(void);

struct fd_cache_entry* fd_cache_get(size_t index);
size_t fd_cache_get_used(void);

__wasi_fd_t fd_cache_get_wasi_fd(struct fd_cache_entry *e);
int fd_cache_get_real_fd(struct fd_cache_entry *e);
fd_source_t fd_cache_get_source(struct fd_cache_entry *e);


#endif
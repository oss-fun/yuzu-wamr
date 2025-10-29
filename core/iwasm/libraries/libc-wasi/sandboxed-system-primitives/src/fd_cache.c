#include "fd_cache.h"

struct fd_cache_entry g_fd_cache[MAX_CACHED_FDS];
size_t g_fd_cache_used = 0;

int fd_cache_insert(__wasi_fd_t wasi_fd, int real_fd, fd_source_t source) {
    if (g_fd_cache_used >= MAX_CACHED_FDS) return -1;
    g_fd_cache[g_fd_cache_used].wasi_fd = wasi_fd;
    g_fd_cache[g_fd_cache_used].real_fd = real_fd;
    g_fd_cache[g_fd_cache_used].source = source;
    g_fd_cache_used++;
    return 0;
}

struct fd_cache_entry* fd_cache_find_by_wasi_fd(__wasi_fd_t wasi_fd) {
    for (size_t i = 0; i < g_fd_cache_used; i++) {
        if (g_fd_cache[i].wasi_fd == wasi_fd) {
            return &g_fd_cache[i];
        }
    }
    return NULL;
}

struct fd_cache_entry* fd_cache_find_by_source(fd_source_t source) {
    for (size_t i = 0; i < g_fd_cache_used; i++) {
        if (g_fd_cache[i].source == source) {
            return &g_fd_cache[i];
        }
    }
    return NULL;
}

void fd_cache_dump(void) {
    printf("FD Cache (used %zu/%d):\n", g_fd_cache_used, MAX_CACHED_FDS);
    for (size_t i = 0; i < g_fd_cache_used; i++) {
        printf("  [%zu] wasi_fd=%u, real_fd=%d, source=%d\n",
               i,
               g_fd_cache[i].wasi_fd,
               g_fd_cache[i].real_fd,
               g_fd_cache[i].source);
    }
}

struct fd_cache_entry* fd_cache_get_entries(size_t *used)
{
    if (used) {
        *used = g_fd_cache_used;
    }
    return g_fd_cache;
}

struct fd_cache_entry* fd_cache_get(size_t index) {
    if (index >= g_fd_cache_used) return NULL;
    return &g_fd_cache[index];
}

size_t fd_cache_get_used(void) {
    return g_fd_cache_used;
}

__wasi_fd_t fd_cache_get_wasi_fd(struct fd_cache_entry *e) {
    return e->wasi_fd;
}

int fd_cache_get_real_fd(struct fd_cache_entry *e) {
    return e->real_fd;
}

fd_source_t fd_cache_get_source(struct fd_cache_entry *e) {
    return e->source;
}
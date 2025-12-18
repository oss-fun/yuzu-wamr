set (MIGRATION_DIR ${CMAKE_CURRENT_LIST_DIR})

#set (LIBC_WASI_DIR ${CMAKE_CURRENT_LIST_DIR}/../libraries/libc-wasi/sandboxed-system-primitives/src)

add_definitions (-DWASM_ENABLE_MIGRATION=1)

include_directories(${MIGRATION_DIR})

file (GLOB source_all ${MIGRATION_DIR}/*.c)

#list(APPEND MIGRATION_SOURCE ${LIBC_WASI_DIR}/posix.c)

set (MIGRATION_SOURCE ${source_all})
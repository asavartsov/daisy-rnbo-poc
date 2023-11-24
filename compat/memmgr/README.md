Memory manager
--------------

Dynamically allocates memory from a fixed pool that is allocated statically at link-time.

Useful for embedded systems, where dynamic allocation is not always supported. Even when it is, it's sometimes safer to pre-allocate the memory pool and not use the heap.

Written by Eli Bendersky (eliben@gmail.com). Inspired by the storage allocator in "The C Programming Language, 2nd Edition" and various allocators found online.

# License

This code is in the public domain.

# Package contents

## memmgr.h

The header file to be included in your application. It contains the API of the memory manager and can be customized by defining pre-processor flags. Read the comment at its top for explanation.

## memmgr.c

The implementation of the memory manager.

## main.c

A sample main application that uses the memory manager, with some tests; the tests were designed for 32-bit systems.

# Usage

After calling `memmgr_init()` in your initialization routine, just use `memmgr_alloc() `instead of `malloc()` and `memmgr_free()` instead of `free()`.
Naturally, you can use the preprocessor to define malloc() and free() as aliases to `memmgr_alloc()` and  `memmgr_free()`. This way the manager will be a drop-in replacement for the standard C library allocators, and can be useful for debugging memory allocation problems and  leaks.

Preprocessor flags you can define to customize the memory manager:

## DEBUG_MEMMGR_FATAL

Allow printing out a message when allocations fail.

## DEBUG_MEMMGR_SUPPORT_STATS

Allow printing out of stats in function `memmgr_print_stats` When this is disabled, `memmgr_print_stats` does nothing.

Note that in production code on an embedded system you'll probably want to keep those undefined, because they cause `printf` to be called.

## POOL_SIZE

Size of the pool for new allocations. This is effectively the heap size of the application, and can  be changed in accordance with the available memory resources.

## MIN_POOL_ALLOC_QUANTAS

Internally, the memory manager allocates memory in quantas roughly the size of two ulong objects. To minimize pool fragmentation in case of multiple allocations and deallocations, it is advisable to not allocate blocks that are too small.

This flag sets the minimal ammount of quantas for an allocation. If the size of a ulong is 4 and you set this flag to 16, the minimal size of an allocation will be `4 * 2 * 16 = 128` bytes If you have a lot of small allocations, keep this value low to conserve memory. If you have mostly large allocations, it is best to make it higher, to avoid fragmentation.

# Notes

This memory manager is **not thread safe**. Use it only for single thread/task applications.

# Reference

```
https:github.com/eliben/code-for-blog/blob/master/2008/memmgr
https:gitrepos.estec.esa.int/taste/panda/blob/master/etc/libbambu/memmgr.c
```


#pragma once

typedef int __gthread_t;
typedef int __gthread_key_t;
typedef int __gthread_once_t;
typedef int __gthread_mutex_t;
typedef int __gthread_recursive_mutex_t;
typedef int __gthread_cond_t;
typedef struct timespec __gthread_time_t;

__gthread_t __gthread_self() { return 1; }
int __gthread_mutex_timedlock(void* m, const void* ts) { return 1; }
int __gthread_recursive_mutex_timedlock(void* m, const void* ts) { return 1; }
template<typename T> void __atomic_load(const T *src, T *dst, int memorder) { memcpy(dst, src, sizeof(T));}
template<typename T> void __atomic_store(T *dst, const T *src, int memorder) { memcpy(dst, src, sizeof(T)); }
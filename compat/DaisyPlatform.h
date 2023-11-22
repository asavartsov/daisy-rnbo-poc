#pragma once

#include "RNBO_PlatformInterface.h"

namespace RNBO {
	class DaisyPlatform : public PlatformInterface
	{
	public:
		DaisyPlatform()
		{
			Platform::set(this);
		}

		~DaisyPlatform() override
		{

		}

		void printMessage(const char* message) override
		{
			/* @TODO */
		}

		// memory allocation
		void* malloc(size_t bytes) override
		{
			return ::malloc(bytes);
		}

		void* calloc(size_t num, size_t size) override
		{
			return ::calloc(num, size);
		}

		void* realloc(void* ptr, size_t bytes) override
		{
			//::realloc doesn't like zero sized allocations
			if (bytes == 0) {
				if (ptr)
					::free(ptr);
				return nullptr;
			}
			return ::realloc(ptr, bytes);
		}

		void free(void* ptr) override
		{
			return ::free(ptr);
		}

		void* memcpy(void* dest, const void* src, size_t n) override
		{
			return ::memcpy(dest, src, n);
		}

		void* memmove(void* dest, const void* src, size_t n) override
		{
			return ::memmove(dest, src, n);
		}

		void* memset(void *dest, int value, size_t n) override
		{
			return ::memset(dest, value, n);
		}

		size_t strlen(const char *s) override
		{
			return ::strlen(s);
		}

		int strcmp(const char* s1, const char* s2) override
		{
			return ::strcmp(s1, s2);
		}

		char *strcpy(char *dest, const char *src) override
		{
			return ::strcpy(dest, src);
		}

		// string formatting
		void toString(char* str, size_t maxlen, number val) override
		{
			snprintf(str, maxlen, "%f", double(val));
		}

		void toString(char* str, size_t maxlen, int val) override
		{
			snprintf(str, maxlen, "%d", val);
		}

		void toString(char* str, size_t maxlen, unsigned int val) override
		{
			snprintf(str, maxlen, "%u", val);
		}

		void toString(char* str, size_t maxlen, long val) override
		{
			snprintf(str, maxlen, "%ld", val);
		}

		void toString(char* str, size_t maxlen, long long val) override
		{
			snprintf(str, maxlen, "%lld", val);
		}

		void toString(char* str, size_t maxlen, unsigned long val) override
		{
			snprintf(str, maxlen, "%lu", val);
		}

		void toString(char* str, size_t maxlen, unsigned long long val) override
		{
			snprintf(str, maxlen, "%llu", val);
		}

		void toString(char* str, size_t maxlen, void* val) override
		{
			snprintf(str, maxlen, "%p", val);
		}

		void abort() override {
			::abort();
		}

		void error(RuntimeError e, const char* msg) override {
			/* @TODO */
		}

		void assertTrue(bool v, const char* msg) override {
			/* @TODO */
		}
	};
} // namespace RNBO

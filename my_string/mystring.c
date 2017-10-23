#include "mystring.h"
#include <stdlib.h>

int atoi(const char *nptr)
{
	return (int)atol(nptr);
}

long atol(const char *nptr)
{
	int sign = (*nptr == '-' ? 1 : 0);
	long result = 0;

	for(char *target_ptr = (char*)(sign ? &nptr[1] : nptr) ; *target_ptr ; target_ptr = &target_ptr[1])
	{
		result *= 10;
		result += *target_ptr - '0';
	}

	if(sign)
	{
		result = -result;
	}

	return result;
}

size_t strlen(const char *s)
{
	size_t length = 0;
	for(char *s_ = (char*)s ; s_[length] ; ++length);

	return length;
}

char *strcpy(char *dest, const char *src)
{
	size_t pointer;
	for(pointer = -1 ; src[(++pointer)] ; dest[pointer] = src[pointer]);
	dest[pointer] = '\0';

	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t pointer;
	for(pointer = 0 ; pointer < n && src[pointer] ; ++pointer)
	{
		dest[pointer] = src[pointer];
	}

	if(pointer < n)
	{
		dest[pointer] = '\0';
	}

	return dest;
}

char *strcat(char *dest, const char *src)
{
	char *dest_pointer = (char*)(dest + strlen(dest));
	
	for(char *src_pointer = (char*)src ; *src_pointer ; (*dest_pointer++) = *(src_pointer++));
	dest_pointer = '\0';

	return dest;
}

char *strncat(char *dest, const char *src, size_t n)
{
	char *dest_pointer = (char*)(dest + strlen(dest));
	
	for(char *src_pointer = (char*)src ; *src_pointer && n ; n--)
	{
		*(dest_pointer++) = *(src_pointer++);
	}

	if(n)
	{
		dest_pointer = '\0';
	}

	return dest;
}

char *strdup(const char *str)
{
	return(strcpy((char*)malloc(sizeof(char) * (strlen(str) + 1)), str));
}

int strcmp(const char *s1, const char *s2)
{
	size_t offset;
	for(offset = 0 ; *(s1 + offset) && *(s2 + offset) && ((*(s1 + offset) == *(s2 + offset))) ; offset++);
	return *(s2 + offset) - *(s1 + offset);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	size_t offset;
	for(offset = 0 ; *(s1 + offset) && *(s2 + offset) && ((*(s1 + offset) == *(s2 + offset))) && offset < n ; offset++);
	return *(s2 + offset) - *(s1 + offset);

}

char *strchr(const char *s, int c)
{
	char *pointer;
	for(pointer = (char*)s ; *pointer != c && *pointer ; ++pointer);

	if(!(*pointer) && c)
	{
		return 0;
	}

	return pointer;
}

char *strrchr(const char *s, int c)
{
	if(!c)
	{
		return((char*)s + strlen(s));
	}
	
	char *pointer;
	for(pointer = (char*)s + strlen(s) ; pointer >= (char*)s && *pointer != c ; --pointer);
	if(pointer < (char*)s)
	{
		return 0;
	}

	return pointer;
}

char *strstr(const char *haystack, const char *needle)
{
	char *end_pointer = (char*)haystack + strlen(haystack) - strlen(haystack);
	char *pointer;

	for(pointer = (char*)haystack ; pointer <= end_pointer && strcmp(pointer, needle) ; ++pointer)
	{
		if(pointer == end_pointer)
		{
			return 0;
		}
	}

	return pointer;

}

static char *global_strtok_saveptr = 0;	//global save pointer for strtok
char *strtok(char *str, const char *delim)
{
	return strtok_r(str, delim, &global_strtok_saveptr);
}

char *strtok_r(char *str, const char *delim, char **saveptr)
{
	if(!str && !(*saveptr))
	{
		return 0;
	}

	if(!str)
	{
		str = *saveptr;
	}
	char *init_string = str;
	size_t delim_size = strlen(delim);

	for( ; *str ; str++)
	{
		for(size_t i = 0 ; i < delim_size ; i++)
		{
			if(*str == delim[i])
			{
				*saveptr = str + 1;
				*str = 0;
				return init_string;
			}
		}
	}

	return init_string;
}

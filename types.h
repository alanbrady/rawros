#ifndef TYPES_H
#define TYPES_H

typedef unsigned char bool;
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned long uint32_t;
typedef signed long int32_t ;

typedef unsigned long long uint64_t ;
typedef signed long long int64_t;

typedef uint32_t intptr_t;

/* implement GNU stdargs virtual arguments */
typedef unsigned char* va_list;
#define va_start(list, last) (list = ((va_list)&last) + sizeof(last))
#define va_arg(list, type) (*(type*)((list += sizeof(type)) - sizeof(type)))
#define va_end(list) (list = NULL)

#endif

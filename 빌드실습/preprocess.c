# 1 "hello.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "hello.c"
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 1 3
# 44 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 1 3
# 37 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 3
# 1 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 1 3
# 121 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 142 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 159 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 213 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 273 "c:/winavr-20100110/lib/gcc/../../avr/include/stdint.h" 3
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 38 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 2 3
# 77 "c:/winavr-20100110/lib/gcc/../../avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;



typedef uint32_t uint_farptr_t;
# 45 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 2 3
# 1 "c:\\winavr-20100110\\bin\\../lib/gcc/avr/4.3.3/include/stdarg.h" 1 3 4
# 43 "c:\\winavr-20100110\\bin\\../lib/gcc/avr/4.3.3/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 105 "c:\\winavr-20100110\\bin\\../lib/gcc/avr/4.3.3/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 46 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 2 3



# 1 "c:\\winavr-20100110\\bin\\../lib/gcc/avr/4.3.3/include/stddef.h" 1 3 4
# 214 "c:\\winavr-20100110\\bin\\../lib/gcc/avr/4.3.3/include/stddef.h" 3 4
typedef unsigned int size_t;
# 50 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 2 3
# 242 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
struct __file {
 char *buf;
 unsigned char unget;
 uint8_t flags;
# 261 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
 int size;
 int len;
 int (*put)(char, struct __file *);
 int (*get)(struct __file *);
 void *udata;
};
# 405 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern struct __file *__iob[];
# 417 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern struct __file *fdevopen(int (*__put)(char, struct __file*), int (*__get)(struct __file*));
# 434 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int fclose(struct __file *__stream);
# 608 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int vfprintf(struct __file *__stream, const char *__fmt, va_list __ap);





extern int vfprintf_P(struct __file *__stream, const char *__fmt, va_list __ap);






extern int fputc(int __c, struct __file *__stream);




extern int putc(int __c, struct __file *__stream);


extern int putchar(int __c);
# 649 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int printf(const char *__fmt, ...);





extern int printf_P(const char *__fmt, ...);







extern int vprintf(const char *__fmt, va_list __ap);





extern int sprintf(char *__s, const char *__fmt, ...);





extern int sprintf_P(char *__s, const char *__fmt, ...);
# 685 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int snprintf(char *__s, size_t __n, const char *__fmt, ...);





extern int snprintf_P(char *__s, size_t __n, const char *__fmt, ...);





extern int vsprintf(char *__s, const char *__fmt, va_list ap);





extern int vsprintf_P(char *__s, const char *__fmt, va_list ap);
# 713 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int vsnprintf(char *__s, size_t __n, const char *__fmt, va_list ap);





extern int vsnprintf_P(char *__s, size_t __n, const char *__fmt, va_list ap);




extern int fprintf(struct __file *__stream, const char *__fmt, ...);





extern int fprintf_P(struct __file *__stream, const char *__fmt, ...);






extern int fputs(const char *__str, struct __file *__stream);




extern int fputs_P(const char *__str, struct __file *__stream);





extern int puts(const char *__str);




extern int puts_P(const char *__str);
# 762 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern size_t fwrite(const void *__ptr, size_t __size, size_t __nmemb,
         struct __file *__stream);







extern int fgetc(struct __file *__stream);




extern int getc(struct __file *__stream);


extern int getchar(void);
# 810 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int ungetc(int __c, struct __file *__stream);
# 822 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern char *fgets(char *__str, int __size, struct __file *__stream);






extern char *gets(char *__str);
# 840 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern size_t fread(void *__ptr, size_t __size, size_t __nmemb,
        struct __file *__stream);




extern void clearerr(struct __file *__stream);
# 857 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int feof(struct __file *__stream);
# 868 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
extern int ferror(struct __file *__stream);






extern int vfscanf(struct __file *__stream, const char *__fmt, va_list __ap);




extern int vfscanf_P(struct __file *__stream, const char *__fmt, va_list __ap);







extern int fscanf(struct __file *__stream, const char *__fmt, ...);




extern int fscanf_P(struct __file *__stream, const char *__fmt, ...);






extern int scanf(const char *__fmt, ...);




extern int scanf_P(const char *__fmt, ...);







extern int vscanf(const char *__fmt, va_list __ap);







extern int sscanf(const char *__buf, const char *__fmt, ...);




extern int sscanf_P(const char *__buf, const char *__fmt, ...);
# 938 "c:/winavr-20100110/lib/gcc/../../avr/include/stdio.h" 3
static __inline__ int fflush(struct __file *stream __attribute__((unused)))
{
 return 0;
}
# 2 "hello.c" 2

int main(){
    printf("hello world\n");
    return 0;
}

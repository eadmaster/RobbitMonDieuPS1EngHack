#ifndef SYSCALLS_H
#define SYSCALLS_H

// PS1 BIOS Syscall - printf
// Uses syscall 0x3F (std_out_printf) via 0xA0 vector
int printf_syscall(const char* format, ...);

/* ---- File I/O ---- */
int  open_syscall(const char *filename, int accessmode);
int  lseek_syscall(int fd, int offset, int seektype);
int  read_syscall(int fd, void *dst, int length);
int  write_syscall(int fd, const void *src, int length);
int  close_syscall(int fd);

/* ---- Character I/O ---- */
int  getc_syscall(int fd);
int  putc_syscall(int ch, int fd);
int  todigit_syscall(int ch);

/* ---- String → number ---- */
unsigned long strtoul_syscall(const char *src, char **src_end, int base);
long          strtol_syscall(const char *src, char **src_end, int base);
int           atoi_syscall(const char *src);
long          atol_syscall(const char *src);
int           atob_syscall(const char *src, int *num_dst);

/* ---- String manipulation ---- */
char *strcat_syscall(char *dst, const char *src);
char *strncat_syscall(char *dst, const char *src, int maxlen);
int   strcmp_syscall(const char *a, const char *b);
int   strncmp_syscall(const char *a, const char *b, int maxlen);
char *strcpy_syscall(char *dst, const char *src);
char *strncpy_syscall(char *dst, const char *src, int maxlen);
int   strlen_syscall(const char *src);

#endif // SYSCALLS_H

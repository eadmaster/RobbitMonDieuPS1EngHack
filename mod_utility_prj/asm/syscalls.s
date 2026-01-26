.set noreorder

.align 2
.global printf_syscall
.type printf_syscall, @function
printf_syscall:
    li    $t2, 0xA0
    jr    $t2
    li    $t1, 0x3F


/* --- File I/O --- */

.align 2
.global open_syscall
.type open_syscall, @function
open_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x00      /* open */

.align 2
.global lseek_syscall
.type lseek_syscall, @function
lseek_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x01      /* lseek */

.align 2
.global read_syscall
.type read_syscall, @function
read_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x02      /* read */

.align 2
.global write_syscall
.type write_syscall, @function
write_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x03      /* write */

.align 2
.global close_syscall
.type close_syscall, @function
close_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x04      /* close */


/* --- Character I/O --- */

.align 2
.global getc_syscall
.type getc_syscall, @function
getc_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x08      /* getc */

.align 2
.global putc_syscall
.type putc_syscall, @function
putc_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x09      /* putc */

.align 2
.global todigit_syscall
.type todigit_syscall, @function
todigit_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x0A      /* todigit */


/* --- String → number --- */

.align 2
.global strtoul_syscall
.type strtoul_syscall, @function
strtoul_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x0C      /* strtoul */

.align 2
.global strtol_syscall
.type strtol_syscall, @function
strtol_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x0D      /* strtol */

.align 2
.global atoi_syscall
.type atoi_syscall, @function
atoi_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x10      /* atoi */

.align 2
.global atol_syscall
.type atol_syscall, @function
atol_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x11      /* atol */

.align 2
.global atob_syscall
.type atob_syscall, @function
atob_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x12      /* atob */


/* --- String manipulation --- */

.align 2
.global strcat_syscall
.type strcat_syscall, @function
strcat_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x15      /* strcat */

.align 2
.global strncat_syscall
.type strncat_syscall, @function
strncat_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x16      /* strncat */

.align 2
.global strcmp_syscall
.type strcmp_syscall, @function
strcmp_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x17      /* strcmp */

.align 2
.global strncmp_syscall
.type strncmp_syscall, @function
strncmp_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x18      /* strncmp */

.align 2
.global strcpy_syscall
.type strcpy_syscall, @function
strcpy_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x19      /* strcpy */

.align 2
.global strncpy_syscall
.type strncpy_syscall, @function
strncpy_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x1A      /* strncpy */

.align 2
.global strlen_syscall
.type strlen_syscall, @function
strlen_syscall:
    li  $t2, 0xA0
    jr  $t2
    li  $t1, 0x1B      /* strlen */



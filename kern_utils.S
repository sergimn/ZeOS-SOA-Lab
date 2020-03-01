#include <asm.h>

ENTRY(write_msr)
    push %ebp
    mov %esp, %ebp

    mov 0x8(%ebp), %ecx # MSR specifier
    mov $0x0, %edx       # High part of the value
    mov 0xc(%ebp), %eax # Low part of the value
    wrmsr

    pop %ebp
    ret


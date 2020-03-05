#include <asm.h>

ENTRY(write)
    pushl %ebp
    mov %esp, %ebp
    pushl %ecx # Needed so 'sysexit' runs with success
    pushl %edx # Same as above
    mov 0x08(%ebp), %ebx # fd
    mov 0x0c(%ebp), %ecx # buffer
    mov 0x10(%ebp), %edx # size

    mov $0x04, %eax # Tells that we will access the 4th position in the sys_call_table

    pushl $write_return # Fake dyn. link for the handler
    pushl %ebp # Same as above
    mov %esp, %ebp # Same as above
    sysenter

write_return:
    cmpl $0x0, %eax
    jg write_continue
    neg %eax
    mov %eax, errno
    mov $-1, %eax

write_continue:
    popl %ebp
    add $0x4, %esp # Handles the return addres in the stack. We could use a 'pop' instruction too
    popl %edx
    popl %ecx
    popl %ebp
    ret

ENTRY(gettime)
    pushl %ebp
    mov %esp, %ebp
    pushl %ecx # Needed so 'sysexit' runs with success
    pushl %edx # Same as above

    mov $0x0a, %eax # Tells that we will access the 10th position in the sys_call_table

    pushl $gettime_return # Fake dyn. link for the handler
    pushl %ebp # Same as above
    mov %esp, %ebp # Same as above
    sysenter

gettime_return:
    cmpl $0x0, %eax
    jg gettime_continue
    neg %eax
    mov %eax, errno
    mov $-1, %eax

gettime_continue:
    popl %ebp
    add $0x4, %esp # Handles the return addres in the stack. We could use a 'pop' instruction too
    ret

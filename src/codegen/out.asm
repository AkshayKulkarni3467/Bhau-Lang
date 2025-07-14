SECTION .data
global_x             dq 13

SECTION .bss

SECTION .text
global  main
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], 12
    .L0:
    mov QWORD [rbp - 16], 0
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 24], 0
    mov rax, [rbp - 8]
    dec rax
    mov [rbp - 24],rax
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 8], rax
    jmp .L0
    .L2:

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

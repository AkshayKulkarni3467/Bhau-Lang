SECTION .data
global_x             dq 12
global_y             dq 13
global_z             dq 14

SECTION .bss

SECTION .text
global  main
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], 0
    mov QWORD [rbp - 16], 100
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 32]
    cmp rax, 0
    jne .L2
    mov QWORD [rbp - 8], 14
    jmp .L3
    .L2:
    mov QWORD [rbp - 8], 13
    .L3:
    jmp .L1
    .L0:
    mov QWORD [rbp - 8], 12
    .L1:
    .L4:
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L5
    jmp .L6
    .L5:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 8], rax
    jmp .L4
    .L6:

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

SECTION .data
global_x             dq "hello i am akshay",0

SECTION .bss

SECTION .text
global  main
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], 0
    mov rax, global_x
    mov QWORD [rbp - 8], rax
    mov QWORD [rbp - 16], 0
    lea rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 24], rax
    
    mov byte [rbp - 32], 'h'
    mov byte [rbp - 31], 0
    mov QWORD [rbp - 40], 0
    lea rax, QWORD [rbp - 32]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    lea rax, QWORD [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 56], rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
star_de:
    push rbp
    mov  rbp, rsp
    sub  rsp, 96
    mov QWORD [rbp - 8], rdi
    .L0:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], '*'
    mov byte [rbp - 63], ' '
    mov byte [rbp - 62], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    mov QWORD [rbp - 88], 0
    mov rax, [rbp - 8]
    dec rax
    mov [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 8], rax
    jmp .L0
    .L2:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 0x0A
    mov byte [rbp - 39], 0
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 56],rax
    leave
    ret

plus_de:
    push rbp
    mov  rbp, rsp
    sub  rsp, 96
    mov QWORD [rbp - 8], rdi
    .L3:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], '+'
    mov byte [rbp - 63], ' '
    mov byte [rbp - 62], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    mov QWORD [rbp - 88], 0
    mov rax, [rbp - 8]
    dec rax
    mov [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 8], rax
    jmp .L3
    .L5:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 0x0A
    mov byte [rbp - 39], 0
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 56],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 192
    mov QWORD [rbp - 8], 0
    mov QWORD [rbp - 16], 0
    .L6:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 10
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L7
    jmp .L8
    .L7:
    .L9:
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 1
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    add rax,rbx
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 0
    jne .L10
    jmp .L11
    .L10:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 2
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cqo
    idiv rbx
    mov QWORD [rbp - 104],rdx
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    cmp rax, 0
    jne .L12
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 160], rax
    mov rdi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 0
    xor rax,rax
    call plus_de
    mov QWORD [rbp - 168],rax
    jmp .L13
    .L12:
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 176], rax
    mov rdi, QWORD [rbp - 176]
    mov QWORD [rbp - 184], 0
    xor rax,rax
    call star_de
    mov QWORD [rbp - 184],rax
    .L13:
    mov QWORD [rbp - 152], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 152],rax
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 16], rax
    jmp .L9
    .L11:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 96], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 8], rax
    jmp .L6
    .L8:

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

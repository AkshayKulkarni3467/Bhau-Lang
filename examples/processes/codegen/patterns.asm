SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
star_de:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    lea rax, [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov byte [rbp - 8], '*'
    mov byte [rbp - 7], ' '
    mov byte [rbp - 6], 0
    mov rdi, QWORD [rbp - 16]
    mov QWORD [rbp - 24], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 24],rax
    leave
    ret

int_num_de:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], rdi
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], '%'
    mov byte [rbp - 15], 'd'
    mov byte [rbp - 14], ' '
    mov byte [rbp - 13], 0
    mov rdi, QWORD [rbp - 24]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov rsi, QWORD [rbp - 32]
    mov QWORD [rbp - 40], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 40],rax
    leave
    ret

r_trig_stars:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L0:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 48], 1
    .L3:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call star_de
    mov QWORD [rbp - 112],rax
    mov QWORD [rbp - 120], 0
    mov rax, [rbp - 48]
    inc rax
    mov [rbp - 120],rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 48], rax
    jmp .L3
    .L5:
    mov QWORD [rbp - 48], 1
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 0x0A
    mov byte [rbp - 79], 0
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 96],rax
    mov QWORD [rbp - 104], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 104],rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 16], rax
    jmp .L0
    .L2:
    leave
    ret

inv_trig_stars:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    .L6:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 1
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setge al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L7
    jmp .L8
    .L7:
    mov QWORD [rbp - 48], 1
    .L9:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 0
    jne .L10
    jmp .L11
    .L10:
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call star_de
    mov QWORD [rbp - 112],rax
    mov QWORD [rbp - 120], 0
    mov rax, [rbp - 48]
    inc rax
    mov [rbp - 120],rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 48], rax
    jmp .L9
    .L11:
    mov QWORD [rbp - 48], 1
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 0x0A
    mov byte [rbp - 79], 0
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 96],rax
    mov QWORD [rbp - 104], 0
    mov rax, [rbp - 16]
    dec rax
    mov [rbp - 104],rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 16], rax
    jmp .L6
    .L8:
    leave
    ret

r_trig_num:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L12:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L13
    jmp .L14
    .L13:
    mov QWORD [rbp - 48], 1
    .L15:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 0
    jne .L16
    jmp .L17
    .L16:
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 112], rax
    mov rdi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call int_num_de
    mov QWORD [rbp - 120],rax
    mov QWORD [rbp - 128], 0
    mov rax, [rbp - 48]
    inc rax
    mov [rbp - 128],rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 48], rax
    jmp .L15
    .L17:
    mov QWORD [rbp - 48], 1
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 0x0A
    mov byte [rbp - 79], 0
    mov rdi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 96],rax
    mov QWORD [rbp - 104], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 104],rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 16], rax
    jmp .L12
    .L14:
    leave
    ret

print_all_patterns:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rdi, QWORD [rbp - 16]
    mov QWORD [rbp - 24], 0
    xor rax,rax
    call r_trig_stars
    mov QWORD [rbp - 24],rax
    lea rax, [rbp - 32]
    mov QWORD [rbp - 40], rax
    mov byte [rbp - 32], 0x0A
    mov byte [rbp - 31], 0
    mov rdi, QWORD [rbp - 40]
    mov QWORD [rbp - 48], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 48],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov rdi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call inv_trig_stars
    mov QWORD [rbp - 64],rax
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 0x0A
    mov byte [rbp - 71], 0
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov rdi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call r_trig_num
    mov QWORD [rbp - 104],rax
    lea rax, [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov byte [rbp - 112], 0x0A
    mov byte [rbp - 111], 0
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], 10
    mov rdi, QWORD [rbp - 8]
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call print_all_patterns
    mov QWORD [rbp - 16],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

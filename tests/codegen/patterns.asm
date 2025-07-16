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

r_trig_aligned:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L18:
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
    jne .L19
    jmp .L20
    .L19:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    .L21:
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
    setg al
    movzx rax,al
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 0
    jne .L22
    jmp .L23
    .L22:
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], ' '
    mov byte [rbp - 143], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    mov QWORD [rbp - 168], 0
    mov rax, [rbp - 48]
    dec rax
    mov [rbp - 168],rax
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 48], rax
    jmp .L21
    .L23:
    mov QWORD [rbp - 80], 1
    .L24:
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    cmp rax, 0
    jne .L25
    jmp .L26
    .L25:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], '*'
    mov byte [rbp - 175], 0
    mov rdi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    mov QWORD [rbp - 200], 0
    mov rax, [rbp - 80]
    inc rax
    mov [rbp - 200],rax
    mov rax, QWORD [rbp - 200]
    mov QWORD [rbp - 80], rax
    jmp .L24
    .L26:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 80], 1
    lea rax, [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov byte [rbp - 112], 0x0A
    mov byte [rbp - 111], 0
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    mov QWORD [rbp - 136], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 136],rax
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 16], rax
    jmp .L18
    .L20:
    leave
    ret

floyd_trig:
    push rbp
    mov  rbp, rsp
    sub  rsp, 160
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    mov QWORD [rbp - 24], 1
    .L27:
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 0
    jne .L28
    jmp .L29
    .L28:
    mov QWORD [rbp - 56], 1
    .L30:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L31
    jmp .L32
    .L31:
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 120], rax
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call int_num_de
    mov QWORD [rbp - 128],rax
    mov QWORD [rbp - 136], 0
    mov rax, [rbp - 24]
    inc rax
    mov [rbp - 136],rax
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 144], 0
    mov rax, [rbp - 56]
    inc rax
    mov [rbp - 144],rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 56], rax
    jmp .L30
    .L32:
    mov QWORD [rbp - 56], 1
    lea rax, [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov byte [rbp - 88], 0x0A
    mov byte [rbp - 87], 0
    mov rdi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    mov QWORD [rbp - 112], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 112],rax
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 16], rax
    jmp .L27
    .L29:
    leave
    ret

bin_trig:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L33:
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
    jne .L34
    jmp .L35
    .L34:
    mov QWORD [rbp - 48], 1
    .L36:
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
    jne .L37
    jmp .L38
    .L37:
    lea rax, [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov byte [rbp - 112], '%'
    mov byte [rbp - 111], 'd'
    mov byte [rbp - 110], ' '
    mov byte [rbp - 109], 0
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    add rax,rbx
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 168], 2
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    cqo
    idiv rbx
    mov QWORD [rbp - 152],rdx
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 176], rax
    mov rsi, QWORD [rbp - 176]
    mov QWORD [rbp - 184], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 184],rax
    mov QWORD [rbp - 192], 0
    mov rax, [rbp - 48]
    inc rax
    mov [rbp - 192],rax
    mov rax, QWORD [rbp - 192]
    mov QWORD [rbp - 48], rax
    jmp .L36
    .L38:
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
    jmp .L33
    .L35:
    leave
    ret

inv_num_trig:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    .L39:
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
    jne .L40
    jmp .L41
    .L40:
    mov QWORD [rbp - 48], 1
    .L42:
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
    jne .L43
    jmp .L44
    .L43:
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
    jmp .L42
    .L44:
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
    jmp .L39
    .L41:
    leave
    ret

pyramid:
    push rbp
    mov  rbp, rsp
    sub  rsp, 256
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L45:
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
    jne .L46
    jmp .L47
    .L46:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    .L48:
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
    setg al
    movzx rax,al
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 0
    jne .L49
    jmp .L50
    .L49:
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], ' '
    mov byte [rbp - 191], 0
    mov rdi, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 208],rax
    mov QWORD [rbp - 216], 0
    mov rax, [rbp - 48]
    dec rax
    mov [rbp - 216],rax
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 48], rax
    jmp .L48
    .L50:
    mov QWORD [rbp - 80], 1
    .L51:
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 2
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    imul rax,rbx
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 128], 1
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    sub rax,rbx
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 144]
    mov rbx, QWORD [rbp - 152]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    cmp rax, 0
    jne .L52
    jmp .L53
    .L52:
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], '*'
    mov byte [rbp - 223], 0
    mov rdi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 240],rax
    mov QWORD [rbp - 248], 0
    mov rax, [rbp - 80]
    inc rax
    mov [rbp - 248],rax
    mov rax, QWORD [rbp - 248]
    mov QWORD [rbp - 80], rax
    jmp .L51
    .L53:
    mov QWORD [rbp - 80], 1
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    lea rax, [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov byte [rbp - 160], 0x0A
    mov byte [rbp - 159], 0
    mov rdi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 176],rax
    mov QWORD [rbp - 184], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 184],rax
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 16], rax
    jmp .L45
    .L47:
    leave
    ret

pascal_trig:
    push rbp
    mov  rbp, rsp
    sub  rsp, 352
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    .L54:
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
    setl al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L55
    jmp .L56
    .L55:
    mov QWORD [rbp - 48], 1
    mov QWORD [rbp - 56], 1
    .L57:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    sub rax,rbx
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    cmp rax, 0
    jne .L58
    jmp .L59
    .L58:
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], ' '
    mov byte [rbp - 175], ' '
    mov byte [rbp - 174], 0
    mov rdi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    mov QWORD [rbp - 200], 0
    mov rax, [rbp - 56]
    inc rax
    mov [rbp - 200],rax
    mov rax, QWORD [rbp - 200]
    mov QWORD [rbp - 56], rax
    jmp .L57
    .L59:
    mov QWORD [rbp - 112], 0
    .L60:
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    cmp rax, 0
    jne .L61
    jmp .L62
    .L61:
    lea rax, [rbp - 208]
    mov QWORD [rbp - 216], rax
    mov byte [rbp - 208], '%'
    mov byte [rbp - 207], '4'
    mov byte [rbp - 206], 'd'
    mov byte [rbp - 205], 0
    mov rdi, QWORD [rbp - 216]
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 224], rax
    mov rsi, QWORD [rbp - 224]
    mov QWORD [rbp - 232], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 232],rax
    mov QWORD [rbp - 240], 0
    mov QWORD [rbp - 248], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 248], rax
    mov QWORD [rbp - 256], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 248]
    mov rbx, QWORD [rbp - 256]
    sub rax,rbx
    mov QWORD [rbp - 240], rax
    mov QWORD [rbp - 264], 0
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 48]
    mov QWORD [rbp - 272], rax
    mov QWORD [rbp - 280], 0
    mov rax, QWORD [rbp - 240]
    mov QWORD [rbp - 280], rax
    mov rax, QWORD [rbp - 272]
    mov rbx, QWORD [rbp - 280]
    imul rax,rbx
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 288], 0
    mov QWORD [rbp - 296], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 296], rax
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 304], 1
    mov rax, QWORD [rbp - 296]
    mov rbx, QWORD [rbp - 304]
    add rax,rbx
    mov QWORD [rbp - 288], rax
    mov QWORD [rbp - 312], 0
    mov QWORD [rbp - 320], 0
    mov rax, QWORD [rbp - 264]
    mov QWORD [rbp - 320], rax
    mov QWORD [rbp - 328], 0
    mov rax, QWORD [rbp - 288]
    mov QWORD [rbp - 328], rax
    mov rax, QWORD [rbp - 320]
    mov rbx, QWORD [rbp - 328]
    cqo
    idiv rbx
    mov QWORD [rbp - 312], rax
    mov rax, QWORD [rbp - 312]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 336], 0
    mov rax, [rbp - 112]
    inc rax
    mov [rbp - 336],rax
    mov rax, QWORD [rbp - 336]
    mov QWORD [rbp - 112], rax
    jmp .L60
    .L62:
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 56], 1
    mov QWORD [rbp - 48], 1
    lea rax, [rbp - 144]
    mov QWORD [rbp - 152], rax
    mov byte [rbp - 144], 0x0A
    mov byte [rbp - 143], 0
    mov rdi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    mov QWORD [rbp - 168], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 168],rax
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 16], rax
    jmp .L54
    .L56:
    leave
    ret

char_pattern:
    push rbp
    mov  rbp, rsp
    sub  rsp, 176
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 'A'
    mov QWORD [rbp - 24], 1
    .L63:
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 40]
    mov rbx, QWORD [rbp - 48]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 0
    jne .L64
    jmp .L65
    .L64:
    mov QWORD [rbp - 56], 1
    .L66:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L67
    jmp .L68
    .L67:
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], '%'
    mov byte [rbp - 119], 'c'
    mov byte [rbp - 118], ' '
    mov byte [rbp - 117], 0
    mov rdi, QWORD [rbp - 128]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 136], rax
    mov rsi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    mov QWORD [rbp - 152], 0
    mov rax, [rbp - 16]
    inc rax
    mov [rbp - 152],rax
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 16], rax
    mov QWORD [rbp - 160], 0
    mov rax, [rbp - 56]
    inc rax
    mov [rbp - 160],rax
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 56], rax
    jmp .L66
    .L68:
    mov QWORD [rbp - 56], 1
    lea rax, [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov byte [rbp - 88], 0x0A
    mov byte [rbp - 87], 0
    mov rdi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    mov QWORD [rbp - 112], 0
    mov rax, [rbp - 24]
    inc rax
    mov [rbp - 112],rax
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 24], rax
    jmp .L63
    .L65:
    leave
    ret

print_all_patterns:
    push rbp
    mov  rbp, rsp
    sub  rsp, 400
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
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov rdi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call r_trig_aligned
    mov QWORD [rbp - 144],rax
    lea rax, [rbp - 152]
    mov QWORD [rbp - 160], rax
    mov byte [rbp - 152], 0x0A
    mov byte [rbp - 151], 0
    mov rdi, QWORD [rbp - 160]
    mov QWORD [rbp - 168], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 168],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 176], rax
    mov rdi, QWORD [rbp - 176]
    mov QWORD [rbp - 184], 0
    xor rax,rax
    call floyd_trig
    mov QWORD [rbp - 184],rax
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 0x0A
    mov byte [rbp - 191], 0
    mov rdi, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 208],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 216], rax
    mov rdi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call bin_trig
    mov QWORD [rbp - 224],rax
    lea rax, [rbp - 232]
    mov QWORD [rbp - 240], rax
    mov byte [rbp - 232], 0x0A
    mov byte [rbp - 231], 0
    mov rdi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 256], rax
    mov rdi, QWORD [rbp - 256]
    mov QWORD [rbp - 264], 0
    xor rax,rax
    call inv_num_trig
    mov QWORD [rbp - 264],rax
    lea rax, [rbp - 272]
    mov QWORD [rbp - 280], rax
    mov byte [rbp - 272], 0x0A
    mov byte [rbp - 271], 0
    mov rdi, QWORD [rbp - 280]
    mov QWORD [rbp - 288], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 288],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 296], rax
    mov rdi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call pyramid
    mov QWORD [rbp - 304],rax
    lea rax, [rbp - 312]
    mov QWORD [rbp - 320], rax
    mov byte [rbp - 312], 0x0A
    mov byte [rbp - 311], 0
    mov rdi, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 328],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 336], rax
    mov rdi, QWORD [rbp - 336]
    mov QWORD [rbp - 344], 0
    xor rax,rax
    call pascal_trig
    mov QWORD [rbp - 344],rax
    lea rax, [rbp - 352]
    mov QWORD [rbp - 360], rax
    mov byte [rbp - 352], 0x0A
    mov byte [rbp - 351], 0
    mov rdi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 368],rax
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 376], rax
    mov rdi, QWORD [rbp - 376]
    mov QWORD [rbp - 384], 0
    xor rax,rax
    call char_pattern
    mov QWORD [rbp - 384],rax
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

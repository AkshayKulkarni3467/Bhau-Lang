SECTION .data
global_pi            dq 3.1414999961853027
global_e             dq 2.7179999351501465
global_greeting      dq "Hello from BhauLang!",0
global_flag          dq 1
global_z             dq 10
global_folded        dq 11
global_x             dq 5
global_c             dq 42
global_b             dq 42
global_a             dq 42

SECTION .bss

SECTION .text
global  main
extern printf
nested_conditions:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L0
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L2
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 'P'
    mov byte [rbp - 71], 'o'
    mov byte [rbp - 70], 's'
    mov byte [rbp - 69], 'i'
    mov byte [rbp - 68], 't'
    mov byte [rbp - 67], 'i'
    mov byte [rbp - 66], 'v'
    mov byte [rbp - 65], 'e'
    mov byte [rbp - 64], 0x0A
    mov byte [rbp - 63], 0
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 100
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    lea rax, [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov byte [rbp - 128], 'V'
    mov byte [rbp - 127], 'e'
    mov byte [rbp - 126], 'r'
    mov byte [rbp - 125], 'y'
    mov byte [rbp - 124], ' '
    mov byte [rbp - 123], 'l'
    mov byte [rbp - 122], 'a'
    mov byte [rbp - 121], 'r'
    mov byte [rbp - 120], 'g'
    mov byte [rbp - 119], 'e'
    mov byte [rbp - 118], 0x0A
    mov byte [rbp - 117], 0
    mov rdi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    .L5:
    jmp .L3
    .L2:
    lea rax, [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov byte [rbp - 160], 'N'
    mov byte [rbp - 159], 'e'
    mov byte [rbp - 158], 'g'
    mov byte [rbp - 157], 'a'
    mov byte [rbp - 156], 't'
    mov byte [rbp - 155], 'i'
    mov byte [rbp - 154], 'v'
    mov byte [rbp - 153], 'e'
    mov byte [rbp - 152], 0x0A
    mov byte [rbp - 151], 0
    mov rdi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 176],rax
    .L3:
    jmp .L1
    .L0:
    lea rax, [rbp - 184]
    mov QWORD [rbp - 192], rax
    mov byte [rbp - 184], 'Z'
    mov byte [rbp - 183], 'e'
    mov byte [rbp - 182], 'r'
    mov byte [rbp - 181], 'o'
    mov byte [rbp - 180], 0x0A
    mov byte [rbp - 179], 0
    mov rdi, QWORD [rbp - 192]
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 200],rax
    .L1:
    leave
    ret

switch_demo:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], rdi
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 1
    je .L7
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 2
    je .L8
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 32]
    cmp rax, 3
    je .L9
    jmp .L10
    .L7:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], 'O'
    mov byte [rbp - 39], 'n'
    mov byte [rbp - 38], 'e'
    mov byte [rbp - 37], 0x0A
    mov byte [rbp - 36], 0
    mov rdi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 56],rax
    .L8:
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'T'
    mov byte [rbp - 63], 'w'
    mov byte [rbp - 62], 'o'
    mov byte [rbp - 61], 0x0A
    mov byte [rbp - 60], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    .L9:
    lea rax, [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov byte [rbp - 88], 'T'
    mov byte [rbp - 87], 'h'
    mov byte [rbp - 86], 'r'
    mov byte [rbp - 85], 'e'
    mov byte [rbp - 84], 'e'
    mov byte [rbp - 83], 0x0A
    mov byte [rbp - 82], 0
    mov rdi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    .L10:
    lea rax, [rbp - 112]
    mov QWORD [rbp - 120], rax
    mov byte [rbp - 112], 'O'
    mov byte [rbp - 111], 't'
    mov byte [rbp - 110], 'h'
    mov byte [rbp - 109], 'e'
    mov byte [rbp - 108], 'r'
    mov byte [rbp - 107], 0x0A
    mov byte [rbp - 106], 0
    mov rdi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    .L6:
    leave
    ret

nested_loops:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov QWORD [rbp - 8], 0
    .L11:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 5
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L12
    jmp .L13
    .L12:
    mov QWORD [rbp - 40], 0
    .L14:
    mov QWORD [rbp - 48], 0
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 56], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 64], 3
    mov rax, QWORD [rbp - 56]
    mov rbx, QWORD [rbp - 64]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    cmp rax, 0
    jne .L15
    jmp .L16
    .L15:
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], '%'
    mov byte [rbp - 119], 'd'
    mov byte [rbp - 118], ' '
    mov byte [rbp - 117], 0
    mov rdi, QWORD [rbp - 128]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov rsi, QWORD [rbp - 136]
    mov QWORD [rbp - 144], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 144],rax
    lea rax, [rbp - 152]
    mov QWORD [rbp - 160], rax
    mov byte [rbp - 152], '%'
    mov byte [rbp - 151], 'd'
    mov byte [rbp - 150], ' '
    mov byte [rbp - 149], 0
    mov rdi, QWORD [rbp - 160]
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 168], rax
    mov rsi, QWORD [rbp - 168]
    mov QWORD [rbp - 176], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 176],rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 200], 1
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    add rax,rbx
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 40], rax
    jmp .L14
    .L16:
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 0x0A
    mov byte [rbp - 71], 0
    mov rdi, QWORD [rbp - 80]
    mov QWORD [rbp - 88], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 88],rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    add rax,rbx
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 8], rax
    jmp .L11
    .L13:
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], 42
    mov rdi, QWORD [rbp - 8]
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call nested_conditions
    mov QWORD [rbp - 16],rax
    mov QWORD [rbp - 24], 3
    mov rdi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call switch_demo
    mov QWORD [rbp - 32],rax
    mov QWORD [rbp - 40], 0
    xor rax,rax
    call nested_loops
    mov QWORD [rbp - 40],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
capital_vowels:
    push rbp
    mov  rbp, rsp
    sub  rsp, 384
    mov QWORD [rbp - 8], 'A'
    .L0:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 'Z'
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 'A'
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 'E'
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 120]
    mov rbx, QWORD [rbp - 128]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 144], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 152], 'I'
    mov rax, QWORD [rbp - 144]
    mov rbx, QWORD [rbp - 152]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 168]
    mov rbx, QWORD [rbp - 176]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 200], 'O'
    mov rax, QWORD [rbp - 192]
    mov rbx, QWORD [rbp - 200]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 208], 0
    mov QWORD [rbp - 216], 0
    mov rax, QWORD [rbp - 160]
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 224], rax
    mov rax, QWORD [rbp - 216]
    mov rbx, QWORD [rbp - 224]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 240], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 240], rax
    mov QWORD [rbp - 248], 0
    mov QWORD [rbp - 248], 'U'
    mov rax, QWORD [rbp - 240]
    mov rbx, QWORD [rbp - 248]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 232], rax
    mov QWORD [rbp - 256], 0
    mov QWORD [rbp - 264], 0
    mov rax, QWORD [rbp - 208]
    mov QWORD [rbp - 264], rax
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 232]
    mov QWORD [rbp - 272], rax
    mov rax, QWORD [rbp - 264]
    mov rbx, QWORD [rbp - 272]
    or rax,rbx
    test rax,rax
    setnz al
    movzx rax,al
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 256]
    cmp rax, 0
    jne .L3
    lea rax, [rbp - 288]
    mov QWORD [rbp - 296], rax
    mov byte [rbp - 288], '%'
    mov byte [rbp - 287], 'c'
    mov byte [rbp - 286], ' '
    mov byte [rbp - 285], 0
    mov rdi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 312], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 312], rax
    mov QWORD [rbp - 320], 0
    mov QWORD [rbp - 320], 32
    mov rax, QWORD [rbp - 312]
    mov rbx, QWORD [rbp - 320]
    add rax,rbx
    mov QWORD [rbp - 304], rax
    mov rax, QWORD [rbp - 304]
    mov QWORD [rbp - 328], rax
    mov rsi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 336],rax
    jmp .L4
    .L3:
    lea rax, [rbp - 344]
    mov QWORD [rbp - 352], rax
    mov byte [rbp - 344], '%'
    mov byte [rbp - 343], 'c'
    mov byte [rbp - 342], ' '
    mov byte [rbp - 341], 0
    mov rdi, QWORD [rbp - 352]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 360], rax
    mov rsi, QWORD [rbp - 360]
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 368],rax
    .L4:
    mov QWORD [rbp - 280], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 280],rax
    mov rax, QWORD [rbp - 280]
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

print_characters:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call capital_vowels
    mov QWORD [rbp - 8],rax
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], 0x0A
    mov byte [rbp - 15], 0
    mov rdi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 32],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 16
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_characters
    mov QWORD [rbp - 8],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

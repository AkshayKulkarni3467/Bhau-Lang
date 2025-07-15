SECTION .data
global_global        dq 99
global_pi            dq 3.1400001049041748
global_name          dq "BhauLang Tester",0
global_z             dq 42
global_y             dq 42
global_x             dq 42

SECTION .bss

SECTION .text
global  main
extern printf
extern strlen
extern scanf
complex:
    push rbp
    mov  rbp, rsp
    sub  rsp, 368
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], rsi
    mov QWORD [rbp - 24], rdx
    mov QWORD [rbp - 32], 0
    .L0:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    add rax,rbx
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L1
    jmp .L2
    .L1:
    mov QWORD [rbp - 112], 0
    .L3:
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 5
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 176], rax
    mov QWORD [rbp - 184], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 176]
    mov rbx, QWORD [rbp - 184]
    imul rax,rbx
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 208], rax
    mov rax, QWORD [rbp - 200]
    mov rbx, QWORD [rbp - 208]
    add rax,rbx
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 216], 0
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 192]
    mov QWORD [rbp - 224], rax
    mov QWORD [rbp - 232], 0
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 232], rax
    mov rax, QWORD [rbp - 224]
    mov rbx, QWORD [rbp - 232]
    sub rax,rbx
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 240], 0
    mov QWORD [rbp - 248], 0
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 248], rax
    mov QWORD [rbp - 256], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 248]
    mov rbx, QWORD [rbp - 256]
    add rax,rbx
    mov QWORD [rbp - 240], rax
    mov rax, QWORD [rbp - 240]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 264], 0
    mov QWORD [rbp - 272], 0
    mov rax, QWORD [rbp - 112]
    mov QWORD [rbp - 272], rax
    mov QWORD [rbp - 280], 0
    mov QWORD [rbp - 280], 1
    mov rax, QWORD [rbp - 272]
    mov rbx, QWORD [rbp - 280]
    add rax,rbx
    mov QWORD [rbp - 264], rax
    mov rax, QWORD [rbp - 264]
    mov QWORD [rbp - 112], rax
    jmp .L3
    .L5:
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 1
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    add rax,rbx
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 8], rax
    jmp .L0
    .L2:
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 96], rax
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 104], 100
    mov rax, QWORD [rbp - 96]
    mov rbx, QWORD [rbp - 104]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    cmp rax, 0
    jne .L6
    mov QWORD [rbp - 288], 0
    mov QWORD [rbp - 296], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 296], rax
    mov QWORD [rbp - 304], 0
    mov QWORD [rbp - 304], 100
    mov rax, QWORD [rbp - 296]
    mov rbx, QWORD [rbp - 304]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 288], rax
    mov rax, QWORD [rbp - 288]
    cmp rax, 0
    jne .L8
    mov QWORD [rbp - 312], 0
    mov rax, QWORD [rbp - 312]
    jmp .L9
    .L8:
    mov QWORD [rbp - 320], 0
    mov QWORD [rbp - 328], 0
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 328], rax
    mov QWORD [rbp - 336], 0
    mov QWORD [rbp - 336], 1
    mov rax, QWORD [rbp - 328]
    mov rbx, QWORD [rbp - 336]
    add rax,rbx
    mov QWORD [rbp - 320], rax
    mov rax, QWORD [rbp - 320]
    mov QWORD [rbp - 344], rax
    mov rax, QWORD [rbp - 344]
    .L9:
    jmp .L7
    .L6:
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 352], rax
    mov rax, QWORD [rbp - 352]
    .L7:
    leave
    ret

deeply_nested:
    push rbp
    mov  rbp, rsp
    sub  rsp, 256
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 1
    .L10:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 0
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L11
    jmp .L12
    .L11:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 72], 2
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    cqo
    idiv rbx
    mov QWORD [rbp - 56],rdx
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    cmp rax, 0
    jne .L13
    mov QWORD [rbp - 128], 0
    mov QWORD [rbp - 136], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 144], 3
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    cqo
    idiv rbx
    mov QWORD [rbp - 128],rdx
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    cmp rax, 0
    jne .L15
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 184], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 192], 1
    mov rax, QWORD [rbp - 184]
    mov rbx, QWORD [rbp - 192]
    add rax,rbx
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 16], rax
    jmp .L16
    .L15:
    mov QWORD [rbp - 200], 0
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 216], 0
    mov QWORD [rbp - 216], 3
    mov rax, QWORD [rbp - 208]
    mov rbx, QWORD [rbp - 216]
    add rax,rbx
    mov QWORD [rbp - 200], rax
    mov rax, QWORD [rbp - 200]
    mov QWORD [rbp - 16], rax
    .L16:
    jmp .L14
    .L13:
    mov QWORD [rbp - 224], 0
    mov QWORD [rbp - 232], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 232], rax
    mov QWORD [rbp - 240], 0
    mov QWORD [rbp - 240], 2
    mov rax, QWORD [rbp - 232]
    mov rbx, QWORD [rbp - 240]
    imul rax,rbx
    mov QWORD [rbp - 224], rax
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 16], rax
    .L14:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 1
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    sub rax,rbx
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    mov QWORD [rbp - 8], rax
    jmp .L10
    .L12:
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret

test_strings:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    lea rax, [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov byte [rbp - 8], 'H'
    mov byte [rbp - 7], 'e'
    mov byte [rbp - 6], 'l'
    mov byte [rbp - 5], 'l'
    mov byte [rbp - 4], 'o'
    mov byte [rbp - 3], 0
    lea rax, [rbp - 32]
    mov QWORD [rbp - 40], rax
    mov byte [rbp - 32], 'B'
    mov byte [rbp - 31], 'h'
    mov byte [rbp - 30], 'a'
    mov byte [rbp - 29], 'u'
    mov byte [rbp - 28], 'L'
    mov byte [rbp - 27], 'a'
    mov byte [rbp - 26], 'n'
    mov byte [rbp - 25], 'g'
    mov byte [rbp - 24], 0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'M'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 's'
    mov byte [rbp - 53], 's'
    mov byte [rbp - 52], 'a'
    mov byte [rbp - 51], 'g'
    mov byte [rbp - 50], 'e'
    mov byte [rbp - 49], ':'
    mov byte [rbp - 48], ' '
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 72],rax
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], '%'
    mov byte [rbp - 79], 's'
    mov byte [rbp - 78], 0x0A
    mov byte [rbp - 77], 0
    mov rdi, QWORD [rbp - 88]
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 96], rax
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    leave
    ret

mega_recursive:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L17
    jmp .L18
    .L17:
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 112]
    .L18:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    sub rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    mov rdi, QWORD [rbp - 64]
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call mega_recursive
    mov QWORD [rbp - 72],rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    imul rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    leave
    ret

nested_conditions:
    push rbp
    mov  rbp, rsp
    sub  rsp, 288
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
    setg al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L19
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
    jne .L21
    lea rax, [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov byte [rbp - 64], 'Z'
    mov byte [rbp - 63], 'e'
    mov byte [rbp - 62], 'r'
    mov byte [rbp - 61], 'o'
    mov byte [rbp - 60], 0x0A
    mov byte [rbp - 59], 0
    mov rdi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    jmp .L22
    .L21:
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'N'
    mov byte [rbp - 95], 'e'
    mov byte [rbp - 94], 'g'
    mov byte [rbp - 93], 'a'
    mov byte [rbp - 92], 't'
    mov byte [rbp - 91], 'i'
    mov byte [rbp - 90], 'v'
    mov byte [rbp - 89], 'e'
    mov byte [rbp - 88], 0x0A
    mov byte [rbp - 87], 0
    mov rdi, QWORD [rbp - 104]
    mov QWORD [rbp - 112], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 112],rax
    .L22:
    jmp .L20
    .L19:
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 10
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    cmp rax, 0
    jne .L23
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 100
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    cmp rax, 0
    jne .L25
    lea rax, [rbp - 184]
    mov QWORD [rbp - 192], rax
    mov byte [rbp - 184], 'L'
    mov byte [rbp - 183], 'a'
    mov byte [rbp - 182], 'r'
    mov byte [rbp - 181], 'g'
    mov byte [rbp - 180], 'e'
    mov byte [rbp - 179], ' '
    mov byte [rbp - 178], 'P'
    mov byte [rbp - 177], 'o'
    mov byte [rbp - 176], 's'
    mov byte [rbp - 175], 'i'
    mov byte [rbp - 174], 't'
    mov byte [rbp - 173], 'i'
    mov byte [rbp - 172], 'v'
    mov byte [rbp - 171], 'e'
    mov byte [rbp - 170], 0x0A
    mov byte [rbp - 169], 0
    mov rdi, QWORD [rbp - 192]
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 200],rax
    jmp .L26
    .L25:
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], 'T'
    mov byte [rbp - 223], 'w'
    mov byte [rbp - 222], 'o'
    mov byte [rbp - 221], ' '
    mov byte [rbp - 220], 'D'
    mov byte [rbp - 219], 'i'
    mov byte [rbp - 218], 'g'
    mov byte [rbp - 217], 'i'
    mov byte [rbp - 216], 't'
    mov byte [rbp - 215], ' '
    mov byte [rbp - 214], 'P'
    mov byte [rbp - 213], 'o'
    mov byte [rbp - 212], 's'
    mov byte [rbp - 211], 'i'
    mov byte [rbp - 210], 't'
    mov byte [rbp - 209], 'i'
    mov byte [rbp - 208], 'v'
    mov byte [rbp - 207], 'e'
    mov byte [rbp - 206], 0x0A
    mov byte [rbp - 205], 0
    mov rdi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 240],rax
    .L26:
    jmp .L24
    .L23:
    lea rax, [rbp - 264]
    mov QWORD [rbp - 272], rax
    mov byte [rbp - 264], 'S'
    mov byte [rbp - 263], 'i'
    mov byte [rbp - 262], 'n'
    mov byte [rbp - 261], 'g'
    mov byte [rbp - 260], 'l'
    mov byte [rbp - 259], 'e'
    mov byte [rbp - 258], ' '
    mov byte [rbp - 257], 'D'
    mov byte [rbp - 256], 'i'
    mov byte [rbp - 255], 'g'
    mov byte [rbp - 254], 'i'
    mov byte [rbp - 253], 't'
    mov byte [rbp - 252], ' '
    mov byte [rbp - 251], 'P'
    mov byte [rbp - 250], 'o'
    mov byte [rbp - 249], 's'
    mov byte [rbp - 248], 'i'
    mov byte [rbp - 247], 't'
    mov byte [rbp - 246], 'i'
    mov byte [rbp - 245], 'v'
    mov byte [rbp - 244], 'e'
    mov byte [rbp - 243], 0x0A
    mov byte [rbp - 242], 0
    mov rdi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 280],rax
    .L24:
    .L20:
    leave
    ret

loop_fun:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], 0
    mov QWORD [rbp - 16], 1
    .L27:
    mov QWORD [rbp - 24], 0
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 32], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 40], 10
    mov rax, QWORD [rbp - 32]
    mov rbx, QWORD [rbp - 40]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 24], rax
    mov rax, QWORD [rbp - 24]
    cmp rax, 0
    jne .L28
    jmp .L29
    .L28:
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 64], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 64], rax
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 64]
    mov rbx, QWORD [rbp - 72]
    add rax,rbx
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 8], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 1
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 16], rax
    jmp .L27
    .L29:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    leave
    ret

test_scope_shadowing:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], 5
    .L30:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 10
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L31
    jmp .L32
    .L31:
    mov QWORD [rbp - 72], 20
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 1
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    add rax,rbx
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    mov QWORD [rbp - 72], rax
    lea rax, [rbp - 104]
    mov QWORD [rbp - 112], rax
    mov byte [rbp - 104], '%'
    mov byte [rbp - 103], 'd'
    mov byte [rbp - 102], 0x0A
    mov byte [rbp - 101], 0
    mov rdi, QWORD [rbp - 112]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 120], rax
    mov rsi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    jmp .L32
    jmp .L30
    .L32:
    lea rax, [rbp - 40]
    mov QWORD [rbp - 48], rax
    mov byte [rbp - 40], '%'
    mov byte [rbp - 39], 'd'
    mov byte [rbp - 38], 0x0A
    mov byte [rbp - 37], 0
    mov rdi, QWORD [rbp - 48]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov rsi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 64],rax
    leave
    ret

test_big_exprs:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    mov QWORD [rbp - 8], 96
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 32], rax
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    imul rax,rbx
    mov QWORD [rbp - 16], rax
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    add rax,rbx
    mov QWORD [rbp - 40], rax
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 47
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    sub rax,rbx
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    leave
    ret

empty_else:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 1
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L33
    jmp .L34
    .L33:
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
    .L34:
    leave
    ret

test_all:
    push rbp
    mov  rbp, rsp
    sub  rsp, 432
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], 'C'
    mov byte [rbp - 15], 'o'
    mov byte [rbp - 14], 'm'
    mov byte [rbp - 13], 'p'
    mov byte [rbp - 12], 'l'
    mov byte [rbp - 11], 'e'
    mov byte [rbp - 10], 'x'
    mov byte [rbp - 9], ':'
    mov byte [rbp - 8], ' '
    mov byte [rbp - 7], 0
    mov rdi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 32],rax
    mov QWORD [rbp - 40], 1
    mov rdi, QWORD [rbp - 40]
    mov QWORD [rbp - 48], 3
    mov rsi, QWORD [rbp - 48]
    mov QWORD [rbp - 56], 2
    mov rdx, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call complex
    mov QWORD [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 72], rax
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], '%'
    mov byte [rbp - 79], 'd'
    mov byte [rbp - 78], 0x0A
    mov byte [rbp - 77], 0
    mov rdi, QWORD [rbp - 88]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 96], rax
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    mov QWORD [rbp - 112], 10
    mov rdi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call deeply_nested
    mov QWORD [rbp - 120],rax
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 128], rax
    lea rax, [rbp - 136]
    mov QWORD [rbp - 144], rax
    mov byte [rbp - 136], 'D'
    mov byte [rbp - 135], 'e'
    mov byte [rbp - 134], 'e'
    mov byte [rbp - 133], 'p'
    mov byte [rbp - 132], ':'
    mov byte [rbp - 131], ' '
    mov byte [rbp - 130], 0
    mov rdi, QWORD [rbp - 144]
    mov QWORD [rbp - 152], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 152],rax
    lea rax, [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov byte [rbp - 160], '%'
    mov byte [rbp - 159], 'd'
    mov byte [rbp - 158], 0x0A
    mov byte [rbp - 157], 0
    mov rdi, QWORD [rbp - 168]
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 176], rax
    mov rsi, QWORD [rbp - 176]
    mov QWORD [rbp - 184], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 184],rax
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call test_strings
    mov QWORD [rbp - 192],rax
    mov QWORD [rbp - 200], 5
    mov rdi, QWORD [rbp - 200]
    mov QWORD [rbp - 208], 0
    xor rax,rax
    call nested_conditions
    mov QWORD [rbp - 208],rax
    mov QWORD [rbp - 216], -5
    mov rdi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call nested_conditions
    mov QWORD [rbp - 224],rax
    mov QWORD [rbp - 232], 100
    mov rdi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call nested_conditions
    mov QWORD [rbp - 240],rax
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call loop_fun
    mov QWORD [rbp - 248],rax
    mov rax, QWORD [rbp - 248]
    mov QWORD [rbp - 256], rax
    lea rax, [rbp - 272]
    mov QWORD [rbp - 280], rax
    mov byte [rbp - 272], 'L'
    mov byte [rbp - 271], 'o'
    mov byte [rbp - 270], 'o'
    mov byte [rbp - 269], 'p'
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], 'F'
    mov byte [rbp - 266], 'u'
    mov byte [rbp - 265], 'n'
    mov byte [rbp - 264], ':'
    mov byte [rbp - 263], ' '
    mov byte [rbp - 262], 0
    mov rdi, QWORD [rbp - 280]
    mov QWORD [rbp - 288], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 288],rax
    lea rax, [rbp - 296]
    mov QWORD [rbp - 304], rax
    mov byte [rbp - 296], '%'
    mov byte [rbp - 295], 'd'
    mov byte [rbp - 294], 0x0A
    mov byte [rbp - 293], 0
    mov rdi, QWORD [rbp - 304]
    mov rax, QWORD [rbp - 256]
    mov QWORD [rbp - 312], rax
    mov rsi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call test_scope_shadowing
    mov QWORD [rbp - 328],rax
    lea rax, [rbp - 344]
    mov QWORD [rbp - 352], rax
    mov byte [rbp - 344], 'B'
    mov byte [rbp - 343], 'i'
    mov byte [rbp - 342], 'g'
    mov byte [rbp - 341], ' '
    mov byte [rbp - 340], 'e'
    mov byte [rbp - 339], 'x'
    mov byte [rbp - 338], 'p'
    mov byte [rbp - 337], 'r'
    mov byte [rbp - 336], ':'
    mov byte [rbp - 335], ' '
    mov byte [rbp - 334], 0
    mov rdi, QWORD [rbp - 352]
    mov QWORD [rbp - 360], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 360],rax
    mov QWORD [rbp - 368], 0
    xor rax,rax
    call test_big_exprs
    mov QWORD [rbp - 368],rax
    mov rax, QWORD [rbp - 368]
    mov QWORD [rbp - 376], rax
    lea rax, [rbp - 384]
    mov QWORD [rbp - 392], rax
    mov byte [rbp - 384], '%'
    mov byte [rbp - 383], 'd'
    mov byte [rbp - 382], 0x0A
    mov byte [rbp - 381], 0
    mov rdi, QWORD [rbp - 392]
    mov rax, QWORD [rbp - 376]
    mov QWORD [rbp - 400], rax
    mov rsi, QWORD [rbp - 400]
    mov QWORD [rbp - 408], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 408],rax
    mov QWORD [rbp - 416], 1
    mov rdi, QWORD [rbp - 416]
    mov QWORD [rbp - 424], 0
    xor rax,rax
    call empty_else
    mov QWORD [rbp - 424],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    lea rax, [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov byte [rbp - 8], '%'
    mov byte [rbp - 7], 's'
    mov byte [rbp - 6], 0x0A
    mov byte [rbp - 5], 0
    mov rdi, QWORD [rbp - 16]
    mov rax, global_name
    mov QWORD [rbp - 24], rax
    mov rsi, QWORD [rbp - 24]
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 32],rax
    mov QWORD [rbp - 40], 0
    xor rax,rax
    call test_all
    mov QWORD [rbp - 40],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

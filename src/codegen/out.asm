SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
func2:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], rdi
    mov QWORD [rbp - 16], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 16],rax
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 8], rax
    mov rax, QWORD [rbp - 8]
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 400
    lea rax, [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov byte [rbp - 128], 'T'
    mov byte [rbp - 127], 'h'
    mov byte [rbp - 126], 'i'
    mov byte [rbp - 125], 's'
    mov byte [rbp - 124], ' '
    mov byte [rbp - 123], 'i'
    mov byte [rbp - 122], 's'
    mov byte [rbp - 121], ' '
    mov byte [rbp - 120], 'h'
    mov byte [rbp - 119], 'e'
    mov byte [rbp - 118], 'l'
    mov byte [rbp - 117], 'l'
    mov byte [rbp - 116], 'o'
    mov byte [rbp - 115], ' '
    mov byte [rbp - 114], 'f'
    mov byte [rbp - 113], 'r'
    mov byte [rbp - 112], 'o'
    mov byte [rbp - 111], 'm'
    mov byte [rbp - 110], ' '
    mov byte [rbp - 109], 'b'
    mov byte [rbp - 108], 'h'
    mov byte [rbp - 107], 'a'
    mov byte [rbp - 106], 'u'
    mov byte [rbp - 105], 'l'
    mov byte [rbp - 104], 'a'
    mov byte [rbp - 103], 'n'
    mov byte [rbp - 102], 'g'
    mov byte [rbp - 101], 0x0A
    mov byte [rbp - 100], 'T'
    mov byte [rbp - 99], 'r'
    mov byte [rbp - 98], 'y'
    mov byte [rbp - 97], 'i'
    mov byte [rbp - 96], 'n'
    mov byte [rbp - 95], 'g'
    mov byte [rbp - 94], ' '
    mov byte [rbp - 93], 't'
    mov byte [rbp - 92], 'o'
    mov byte [rbp - 91], ' '
    mov byte [rbp - 90], 's'
    mov byte [rbp - 89], 'e'
    mov byte [rbp - 88], 'e'
    mov byte [rbp - 87], ' '
    mov byte [rbp - 86], 'h'
    mov byte [rbp - 85], 'o'
    mov byte [rbp - 84], 'w'
    mov byte [rbp - 83], ' '
    mov byte [rbp - 82], 'l'
    mov byte [rbp - 81], 'o'
    mov byte [rbp - 80], 'n'
    mov byte [rbp - 79], 'g'
    mov byte [rbp - 78], ' '
    mov byte [rbp - 77], 'a'
    mov byte [rbp - 76], ' '
    mov byte [rbp - 75], 's'
    mov byte [rbp - 74], 't'
    mov byte [rbp - 73], 'r'
    mov byte [rbp - 72], 'i'
    mov byte [rbp - 71], 'n'
    mov byte [rbp - 70], 'g'
    mov byte [rbp - 69], ' '
    mov byte [rbp - 68], 'c'
    mov byte [rbp - 67], 'a'
    mov byte [rbp - 66], 'n'
    mov byte [rbp - 65], ' '
    mov byte [rbp - 64], 'b'
    mov byte [rbp - 63], 'e'
    mov byte [rbp - 62], ' '
    mov byte [rbp - 61], 'i'
    mov byte [rbp - 60], 'n'
    mov byte [rbp - 59], ' '
    mov byte [rbp - 58], 't'
    mov byte [rbp - 57], 'h'
    mov byte [rbp - 56], 'i'
    mov byte [rbp - 55], 's'
    mov byte [rbp - 54], ' '
    mov byte [rbp - 53], 'l'
    mov byte [rbp - 52], 'a'
    mov byte [rbp - 51], 'n'
    mov byte [rbp - 50], 'g'
    mov byte [rbp - 49], 'u'
    mov byte [rbp - 48], 'a'
    mov byte [rbp - 47], 'g'
    mov byte [rbp - 46], 'e'
    mov byte [rbp - 45], ' '
    mov byte [rbp - 44], 'a'
    mov byte [rbp - 43], 'n'
    mov byte [rbp - 42], 'd'
    mov byte [rbp - 41], ' '
    mov byte [rbp - 40], 'd'
    mov byte [rbp - 39], 'o'
    mov byte [rbp - 38], 'e'
    mov byte [rbp - 37], 's'
    mov byte [rbp - 36], ' '
    mov byte [rbp - 35], 'i'
    mov byte [rbp - 34], 't'
    mov byte [rbp - 33], ' '
    mov byte [rbp - 32], 'b'
    mov byte [rbp - 31], 'u'
    mov byte [rbp - 30], 'g'
    mov byte [rbp - 29], ' '
    mov byte [rbp - 28], 'o'
    mov byte [rbp - 27], 'u'
    mov byte [rbp - 26], 't'
    mov byte [rbp - 25], 'i'
    mov byte [rbp - 24], 'f'
    mov byte [rbp - 23], ' '
    mov byte [rbp - 22], 's'
    mov byte [rbp - 21], 'i'
    mov byte [rbp - 20], 'z'
    mov byte [rbp - 19], 'e'
    mov byte [rbp - 18], ' '
    mov byte [rbp - 17], 'g'
    mov byte [rbp - 16], 'o'
    mov byte [rbp - 15], 'e'
    mov byte [rbp - 14], 's'
    mov byte [rbp - 13], ' '
    mov byte [rbp - 12], 'b'
    mov byte [rbp - 11], 'r'
    mov byte [rbp - 10], 'r'
    mov byte [rbp - 9], 'r'
    mov byte [rbp - 8], 'r'
    mov byte [rbp - 7], 0
    mov rax, 0x4028e147a0000000
    movq xmm0, rax
    movsd QWORD [rbp - 144], xmm0
    mov QWORD [rbp - 152], 0
    lea rax, QWORD [rbp - 136]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    lea rax, QWORD [rbp - 152]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    lea rax, QWORD [rbp - 160]
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 176], 0
    lea rax, QWORD [rbp - 168]
    mov QWORD [rbp - 176], rax
    mov QWORD [rbp - 184], 0
    lea rax, QWORD [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 192], rax
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 192]
    mov rax, QWORD [rax]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 200]
    mov rax, QWORD [rax]
    mov QWORD [rbp - 208], rax
    mov QWORD [rbp - 216], 0
    mov rax, QWORD [rbp - 208]
    mov rax, QWORD [rax]
    mov QWORD [rbp - 216], rax
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 216]
    mov rax, QWORD [rax]
    mov QWORD [rbp - 224], rax
    mov QWORD [rbp - 232], 0
    mov rax, QWORD [rbp - 224]
    mov rax, QWORD [rax]
    mov QWORD [rbp - 232], rax
    mov rax, QWORD [rbp - 232]
    mov QWORD [rbp - 240], rax
    lea rax, [rbp - 248]
    mov QWORD [rbp - 256], rax
    mov byte [rbp - 248], '%'
    mov byte [rbp - 247], '.'
    mov byte [rbp - 246], '1'
    mov byte [rbp - 245], '6'
    mov byte [rbp - 244], 'f'
    mov byte [rbp - 243], 0x0A
    mov byte [rbp - 242], 0
    mov rdi, QWORD [rbp - 256]
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 264], rax
    movq xmm0, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    mov rax, 1
    call printf
    mov QWORD [rbp - 272],rax
    lea rax, [rbp - 280]
    mov QWORD [rbp - 288], rax
    mov byte [rbp - 280], '%'
    mov byte [rbp - 279], 's'
    mov byte [rbp - 278], 0x0A
    mov byte [rbp - 277], 0
    mov rdi, QWORD [rbp - 288]
    mov rax, QWORD [rbp - 240]
    mov QWORD [rbp - 296], rax
    mov rsi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 304],rax
    mov QWORD [rbp - 312], 1
    mov rax, QWORD [rbp - 312]
    mov QWORD [rbp - 320], rax
    mov rdi, QWORD [rbp - 320]
    mov QWORD [rbp - 328], 0
    xor rax,rax
    call func2
    mov QWORD [rbp - 328],rax
    mov rax, QWORD [rbp - 328]
    mov QWORD [rbp - 336], rax
    lea rax, [rbp - 368]
    mov QWORD [rbp - 376], rax
    mov byte [rbp - 368], 'T'
    mov byte [rbp - 367], 'h'
    mov byte [rbp - 366], 'i'
    mov byte [rbp - 365], 's'
    mov byte [rbp - 364], ' '
    mov byte [rbp - 363], 'i'
    mov byte [rbp - 362], 's'
    mov byte [rbp - 361], ' '
    mov byte [rbp - 360], 'f'
    mov byte [rbp - 359], 'r'
    mov byte [rbp - 358], 'o'
    mov byte [rbp - 357], 'm'
    mov byte [rbp - 356], ' '
    mov byte [rbp - 355], 'f'
    mov byte [rbp - 354], 'u'
    mov byte [rbp - 353], 'n'
    mov byte [rbp - 352], 'c'
    mov byte [rbp - 351], '2'
    mov byte [rbp - 350], ':'
    mov byte [rbp - 349], ' '
    mov byte [rbp - 348], '%'
    mov byte [rbp - 347], 'd'
    mov byte [rbp - 346], 0x0A
    mov byte [rbp - 345], 0
    mov rdi, QWORD [rbp - 376]
    mov rax, QWORD [rbp - 336]
    mov QWORD [rbp - 384], rax
    mov rsi, QWORD [rbp - 384]
    mov QWORD [rbp - 392], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 392],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

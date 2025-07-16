SECTION .data
global_x             dq "declared in global",0

SECTION .bss

SECTION .text
global  main
extern printf
print_global:
    push rbp
    mov  rbp, rsp
    sub  rsp, 64
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'F'
    mov byte [rbp - 23], 'r'
    mov byte [rbp - 22], 'o'
    mov byte [rbp - 21], 'm'
    mov byte [rbp - 20], ' '
    mov byte [rbp - 19], 'p'
    mov byte [rbp - 18], 'r'
    mov byte [rbp - 17], 'i'
    mov byte [rbp - 16], 'n'
    mov byte [rbp - 15], 't'
    mov byte [rbp - 14], '_'
    mov byte [rbp - 13], 'g'
    mov byte [rbp - 12], 'l'
    mov byte [rbp - 11], 'o'
    mov byte [rbp - 10], 'b'
    mov byte [rbp - 9], 'a'
    mov byte [rbp - 8], 'l'
    mov byte [rbp - 7], ':'
    mov byte [rbp - 6], ' '
    mov byte [rbp - 5], '%'
    mov byte [rbp - 4], 's'
    mov byte [rbp - 3], 0x0A
    mov byte [rbp - 2], 0
    mov rdi, QWORD [rbp - 32]
    mov rax, global_x
    mov QWORD [rbp - 40], rax
    mov rsi, QWORD [rbp - 40]
    mov QWORD [rbp - 48], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 48],rax
    leave
    ret

print_infunc:
    push rbp
    mov  rbp, rsp
    sub  rsp, 96
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'd'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'c'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'a'
    mov byte [rbp - 19], 'r'
    mov byte [rbp - 18], 'e'
    mov byte [rbp - 17], 'd'
    mov byte [rbp - 16], ' '
    mov byte [rbp - 15], 'i'
    mov byte [rbp - 14], 'n'
    mov byte [rbp - 13], ' '
    mov byte [rbp - 12], 'f'
    mov byte [rbp - 11], 'u'
    mov byte [rbp - 10], 'n'
    mov byte [rbp - 9], 'c'
    mov byte [rbp - 8], 't'
    mov byte [rbp - 7], 'i'
    mov byte [rbp - 6], 'o'
    mov byte [rbp - 5], 'n'
    mov byte [rbp - 4], 0
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'F'
    mov byte [rbp - 55], 'r'
    mov byte [rbp - 54], 'o'
    mov byte [rbp - 53], 'm'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'p'
    mov byte [rbp - 50], 'r'
    mov byte [rbp - 49], 'i'
    mov byte [rbp - 48], 'n'
    mov byte [rbp - 47], 't'
    mov byte [rbp - 46], '_'
    mov byte [rbp - 45], 'i'
    mov byte [rbp - 44], 'n'
    mov byte [rbp - 43], 'f'
    mov byte [rbp - 42], 'u'
    mov byte [rbp - 41], 'n'
    mov byte [rbp - 40], 'c'
    mov byte [rbp - 39], ':'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], '%'
    mov byte [rbp - 36], 's'
    mov byte [rbp - 35], 0x0A
    mov byte [rbp - 34], 0
    mov rdi, QWORD [rbp - 64]
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 72], rax
    mov rsi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    leave
    ret

print_inblock:
    push rbp
    mov  rbp, rsp
    sub  rsp, 128
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'd'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'c'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'a'
    mov byte [rbp - 19], 'r'
    mov byte [rbp - 18], 'e'
    mov byte [rbp - 17], 'd'
    mov byte [rbp - 16], ' '
    mov byte [rbp - 15], 'i'
    mov byte [rbp - 14], 'n'
    mov byte [rbp - 13], ' '
    mov byte [rbp - 12], 'f'
    mov byte [rbp - 11], 'u'
    mov byte [rbp - 10], 'n'
    mov byte [rbp - 9], 'c'
    mov byte [rbp - 8], ' '
    mov byte [rbp - 7], 's'
    mov byte [rbp - 6], 'c'
    mov byte [rbp - 5], 'o'
    mov byte [rbp - 4], 'p'
    mov byte [rbp - 3], 'e'
    mov byte [rbp - 2], 0
    mov rax, 1
    cmp rax, 0
    jne .L0
    jmp .L1
    .L0:
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'd'
    mov byte [rbp - 55], 'e'
    mov byte [rbp - 54], 'c'
    mov byte [rbp - 53], 'l'
    mov byte [rbp - 52], 'a'
    mov byte [rbp - 51], 'r'
    mov byte [rbp - 50], 'e'
    mov byte [rbp - 49], 'd'
    mov byte [rbp - 48], ' '
    mov byte [rbp - 47], 'i'
    mov byte [rbp - 46], 'n'
    mov byte [rbp - 45], ' '
    mov byte [rbp - 44], 'b'
    mov byte [rbp - 43], 'l'
    mov byte [rbp - 42], 'o'
    mov byte [rbp - 41], 'c'
    mov byte [rbp - 40], 'k'
    mov byte [rbp - 39], ' '
    mov byte [rbp - 38], 's'
    mov byte [rbp - 37], 'c'
    mov byte [rbp - 36], 'o'
    mov byte [rbp - 35], 'p'
    mov byte [rbp - 34], 'e'
    mov byte [rbp - 33], 0
    lea rax, [rbp - 96]
    mov QWORD [rbp - 104], rax
    mov byte [rbp - 96], 'F'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'o'
    mov byte [rbp - 93], 'm'
    mov byte [rbp - 92], ' '
    mov byte [rbp - 91], 'p'
    mov byte [rbp - 90], 'r'
    mov byte [rbp - 89], 'i'
    mov byte [rbp - 88], 'n'
    mov byte [rbp - 87], 't'
    mov byte [rbp - 86], '_'
    mov byte [rbp - 85], 'i'
    mov byte [rbp - 84], 'n'
    mov byte [rbp - 83], 'b'
    mov byte [rbp - 82], 'l'
    mov byte [rbp - 81], 'o'
    mov byte [rbp - 80], 'c'
    mov byte [rbp - 79], 'k'
    mov byte [rbp - 78], ':'
    mov byte [rbp - 77], ' '
    mov byte [rbp - 76], '%'
    mov byte [rbp - 75], 's'
    mov byte [rbp - 74], 0x0A
    mov byte [rbp - 73], 0
    mov rdi, QWORD [rbp - 104]
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 112], rax
    mov rsi, QWORD [rbp - 112]
    mov QWORD [rbp - 120], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 120],rax
    .L1:
    leave
    ret

print_access_from_outer_block:
    push rbp
    mov  rbp, rsp
    sub  rsp, 112
    lea rax, [rbp - 24]
    mov QWORD [rbp - 32], rax
    mov byte [rbp - 24], 'd'
    mov byte [rbp - 23], 'e'
    mov byte [rbp - 22], 'c'
    mov byte [rbp - 21], 'l'
    mov byte [rbp - 20], 'a'
    mov byte [rbp - 19], 'r'
    mov byte [rbp - 18], 'd'
    mov byte [rbp - 17], ' '
    mov byte [rbp - 16], 'i'
    mov byte [rbp - 15], 'n'
    mov byte [rbp - 14], ' '
    mov byte [rbp - 13], 'o'
    mov byte [rbp - 12], 'u'
    mov byte [rbp - 11], 't'
    mov byte [rbp - 10], 'e'
    mov byte [rbp - 9], 'r'
    mov byte [rbp - 8], ' '
    mov byte [rbp - 7], 'b'
    mov byte [rbp - 6], 'l'
    mov byte [rbp - 5], 'o'
    mov byte [rbp - 4], 'c'
    mov byte [rbp - 3], 'k'
    mov byte [rbp - 2], 0
    mov rax, 1
    cmp rax, 0
    jne .L2
    jmp .L3
    .L2:
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 'F'
    mov byte [rbp - 79], 'r'
    mov byte [rbp - 78], 'o'
    mov byte [rbp - 77], 'm'
    mov byte [rbp - 76], 'e'
    mov byte [rbp - 75], ' '
    mov byte [rbp - 74], 'p'
    mov byte [rbp - 73], 'r'
    mov byte [rbp - 72], 'i'
    mov byte [rbp - 71], 'n'
    mov byte [rbp - 70], 't'
    mov byte [rbp - 69], '_'
    mov byte [rbp - 68], 'a'
    mov byte [rbp - 67], 'c'
    mov byte [rbp - 66], 'c'
    mov byte [rbp - 65], 'e'
    mov byte [rbp - 64], 's'
    mov byte [rbp - 63], 's'
    mov byte [rbp - 62], '_'
    mov byte [rbp - 61], 'f'
    mov byte [rbp - 60], 'r'
    mov byte [rbp - 59], 'o'
    mov byte [rbp - 58], 'm'
    mov byte [rbp - 57], '_'
    mov byte [rbp - 56], 'o'
    mov byte [rbp - 55], 'u'
    mov byte [rbp - 54], 't'
    mov byte [rbp - 53], 'e'
    mov byte [rbp - 52], 'r'
    mov byte [rbp - 51], '_'
    mov byte [rbp - 50], 'b'
    mov byte [rbp - 49], 'l'
    mov byte [rbp - 48], 'o'
    mov byte [rbp - 47], 'c'
    mov byte [rbp - 46], 'k'
    mov byte [rbp - 45], ':'
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], '%'
    mov byte [rbp - 42], 's'
    mov byte [rbp - 41], 0x0A
    mov byte [rbp - 40], 0
    mov rdi, QWORD [rbp - 88]
    mov rax, QWORD [rbp - 32]
    mov QWORD [rbp - 96], rax
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    .L3:
    leave
    ret

print_nestblocks:
    push rbp
    mov  rbp, rsp
    sub  rsp, 256
    lea rax, [rbp - 8]
    mov QWORD [rbp - 16], rax
    mov byte [rbp - 8], 'b'
    mov byte [rbp - 7], 'l'
    mov byte [rbp - 6], 'o'
    mov byte [rbp - 5], 'c'
    mov byte [rbp - 4], 'k'
    mov byte [rbp - 3], ' '
    mov byte [rbp - 2], '1'
    mov byte [rbp - 1], 0
    mov rax, 1
    cmp rax, 0
    jne .L4
    jmp .L5
    .L4:
    lea rax, [rbp - 88]
    mov QWORD [rbp - 96], rax
    mov byte [rbp - 88], 'b'
    mov byte [rbp - 87], 'l'
    mov byte [rbp - 86], 'o'
    mov byte [rbp - 85], 'c'
    mov byte [rbp - 84], 'k'
    mov byte [rbp - 83], ' '
    mov byte [rbp - 82], '2'
    mov byte [rbp - 81], 0
    mov rax, 1
    cmp rax, 0
    jne .L6
    jmp .L7
    .L6:
    lea rax, [rbp - 168]
    mov QWORD [rbp - 176], rax
    mov byte [rbp - 168], 'b'
    mov byte [rbp - 167], 'l'
    mov byte [rbp - 166], 'o'
    mov byte [rbp - 165], 'c'
    mov byte [rbp - 164], 'k'
    mov byte [rbp - 163], ' '
    mov byte [rbp - 162], '3'
    mov byte [rbp - 161], 0
    lea rax, [rbp - 216]
    mov QWORD [rbp - 224], rax
    mov byte [rbp - 216], 'F'
    mov byte [rbp - 215], 'r'
    mov byte [rbp - 214], 'o'
    mov byte [rbp - 213], 'm'
    mov byte [rbp - 212], ' '
    mov byte [rbp - 211], 'p'
    mov byte [rbp - 210], 'r'
    mov byte [rbp - 209], 'i'
    mov byte [rbp - 208], 'n'
    mov byte [rbp - 207], 't'
    mov byte [rbp - 206], '_'
    mov byte [rbp - 205], 'n'
    mov byte [rbp - 204], 'e'
    mov byte [rbp - 203], 's'
    mov byte [rbp - 202], 't'
    mov byte [rbp - 201], 'b'
    mov byte [rbp - 200], 'l'
    mov byte [rbp - 199], 'o'
    mov byte [rbp - 198], 'c'
    mov byte [rbp - 197], 'k'
    mov byte [rbp - 196], 's'
    mov byte [rbp - 195], ','
    mov byte [rbp - 194], ' '
    mov byte [rbp - 193], 'B'
    mov byte [rbp - 192], 'l'
    mov byte [rbp - 191], 'o'
    mov byte [rbp - 190], 'c'
    mov byte [rbp - 189], 'k'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], '3'
    mov byte [rbp - 186], ' '
    mov byte [rbp - 185], ':'
    mov byte [rbp - 184], ' '
    mov byte [rbp - 183], '%'
    mov byte [rbp - 182], 's'
    mov byte [rbp - 181], 0x0A
    mov byte [rbp - 180], 0
    mov rdi, QWORD [rbp - 224]
    mov rax, QWORD [rbp - 176]
    mov QWORD [rbp - 232], rax
    mov rsi, QWORD [rbp - 232]
    mov QWORD [rbp - 240], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 240],rax
    .L7:
    lea rax, [rbp - 136]
    mov QWORD [rbp - 144], rax
    mov byte [rbp - 136], 'F'
    mov byte [rbp - 135], 'r'
    mov byte [rbp - 134], 'o'
    mov byte [rbp - 133], 'm'
    mov byte [rbp - 132], ' '
    mov byte [rbp - 131], 'p'
    mov byte [rbp - 130], 'r'
    mov byte [rbp - 129], 'i'
    mov byte [rbp - 128], 'n'
    mov byte [rbp - 127], 't'
    mov byte [rbp - 126], '_'
    mov byte [rbp - 125], 'n'
    mov byte [rbp - 124], 'e'
    mov byte [rbp - 123], 's'
    mov byte [rbp - 122], 't'
    mov byte [rbp - 121], 'b'
    mov byte [rbp - 120], 'l'
    mov byte [rbp - 119], 'o'
    mov byte [rbp - 118], 'c'
    mov byte [rbp - 117], 'k'
    mov byte [rbp - 116], 's'
    mov byte [rbp - 115], ','
    mov byte [rbp - 114], ' '
    mov byte [rbp - 113], 'B'
    mov byte [rbp - 112], 'l'
    mov byte [rbp - 111], 'o'
    mov byte [rbp - 110], 'c'
    mov byte [rbp - 109], 'k'
    mov byte [rbp - 108], ' '
    mov byte [rbp - 107], '2'
    mov byte [rbp - 106], ' '
    mov byte [rbp - 105], ':'
    mov byte [rbp - 104], ' '
    mov byte [rbp - 103], '%'
    mov byte [rbp - 102], 's'
    mov byte [rbp - 101], 0x0A
    mov byte [rbp - 100], 0
    mov rdi, QWORD [rbp - 144]
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 152], rax
    mov rsi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    .L5:
    lea rax, [rbp - 56]
    mov QWORD [rbp - 64], rax
    mov byte [rbp - 56], 'F'
    mov byte [rbp - 55], 'r'
    mov byte [rbp - 54], 'o'
    mov byte [rbp - 53], 'm'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'p'
    mov byte [rbp - 50], 'r'
    mov byte [rbp - 49], 'i'
    mov byte [rbp - 48], 'n'
    mov byte [rbp - 47], 't'
    mov byte [rbp - 46], '_'
    mov byte [rbp - 45], 'n'
    mov byte [rbp - 44], 'e'
    mov byte [rbp - 43], 's'
    mov byte [rbp - 42], 't'
    mov byte [rbp - 41], 'b'
    mov byte [rbp - 40], 'l'
    mov byte [rbp - 39], 'o'
    mov byte [rbp - 38], 'c'
    mov byte [rbp - 37], 'k'
    mov byte [rbp - 36], 's'
    mov byte [rbp - 35], ','
    mov byte [rbp - 34], ' '
    mov byte [rbp - 33], 'B'
    mov byte [rbp - 32], 'l'
    mov byte [rbp - 31], 'o'
    mov byte [rbp - 30], 'c'
    mov byte [rbp - 29], 'k'
    mov byte [rbp - 28], ' '
    mov byte [rbp - 27], '1'
    mov byte [rbp - 26], ' '
    mov byte [rbp - 25], ':'
    mov byte [rbp - 24], ' '
    mov byte [rbp - 23], '%'
    mov byte [rbp - 22], 's'
    mov byte [rbp - 21], 0x0A
    mov byte [rbp - 20], 0
    mov rdi, QWORD [rbp - 64]
    mov rax, QWORD [rbp - 16]
    mov QWORD [rbp - 72], rax
    mov rsi, QWORD [rbp - 72]
    mov QWORD [rbp - 80], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 80],rax
    leave
    ret

print_funcvsblockscope:
    push rbp
    mov  rbp, rsp
    sub  rsp, 208
    mov rax, 1
    cmp rax, 0
    jne .L8
    jmp .L9
    .L8:
    lea rax, [rbp - 120]
    mov QWORD [rbp - 128], rax
    mov byte [rbp - 120], 'b'
    mov byte [rbp - 119], 'l'
    mov byte [rbp - 118], 'o'
    mov byte [rbp - 117], 'c'
    mov byte [rbp - 116], 'k'
    mov byte [rbp - 115], ' '
    mov byte [rbp - 114], 's'
    mov byte [rbp - 113], 'c'
    mov byte [rbp - 112], 'o'
    mov byte [rbp - 111], 'p'
    mov byte [rbp - 110], 'e'
    mov byte [rbp - 109], 0
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], 'F'
    mov byte [rbp - 175], 'r'
    mov byte [rbp - 174], 'o'
    mov byte [rbp - 173], 'm'
    mov byte [rbp - 172], ' '
    mov byte [rbp - 171], 'p'
    mov byte [rbp - 170], 'r'
    mov byte [rbp - 169], 'i'
    mov byte [rbp - 168], 'n'
    mov byte [rbp - 167], 't'
    mov byte [rbp - 166], '_'
    mov byte [rbp - 165], 'f'
    mov byte [rbp - 164], 'u'
    mov byte [rbp - 163], 'n'
    mov byte [rbp - 162], 'c'
    mov byte [rbp - 161], 'v'
    mov byte [rbp - 160], 's'
    mov byte [rbp - 159], 'b'
    mov byte [rbp - 158], 'l'
    mov byte [rbp - 157], 'o'
    mov byte [rbp - 156], 'c'
    mov byte [rbp - 155], 'k'
    mov byte [rbp - 154], 's'
    mov byte [rbp - 153], 'c'
    mov byte [rbp - 152], 'o'
    mov byte [rbp - 151], 'p'
    mov byte [rbp - 150], 'e'
    mov byte [rbp - 149], ','
    mov byte [rbp - 148], ' '
    mov byte [rbp - 147], 'B'
    mov byte [rbp - 146], 'l'
    mov byte [rbp - 145], 'o'
    mov byte [rbp - 144], 'c'
    mov byte [rbp - 143], 'k'
    mov byte [rbp - 142], ' '
    mov byte [rbp - 141], 's'
    mov byte [rbp - 140], 'c'
    mov byte [rbp - 139], 'o'
    mov byte [rbp - 138], 'p'
    mov byte [rbp - 137], 'e'
    mov byte [rbp - 136], ' '
    mov byte [rbp - 135], ':'
    mov byte [rbp - 134], ' '
    mov byte [rbp - 133], '%'
    mov byte [rbp - 132], 's'
    mov byte [rbp - 131], 0x0A
    mov byte [rbp - 130], 0
    mov rdi, QWORD [rbp - 184]
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 192], rax
    mov rsi, QWORD [rbp - 192]
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 200],rax
    .L9:
    lea rax, [rbp - 16]
    mov QWORD [rbp - 24], rax
    mov byte [rbp - 16], 'f'
    mov byte [rbp - 15], 'u'
    mov byte [rbp - 14], 'n'
    mov byte [rbp - 13], 'c'
    mov byte [rbp - 12], 't'
    mov byte [rbp - 11], 'i'
    mov byte [rbp - 10], 'o'
    mov byte [rbp - 9], 'n'
    mov byte [rbp - 8], ' '
    mov byte [rbp - 7], 's'
    mov byte [rbp - 6], 'c'
    mov byte [rbp - 5], 'o'
    mov byte [rbp - 4], 'p'
    mov byte [rbp - 3], 'e'
    mov byte [rbp - 2], 0
    lea rax, [rbp - 80]
    mov QWORD [rbp - 88], rax
    mov byte [rbp - 80], 'F'
    mov byte [rbp - 79], 'r'
    mov byte [rbp - 78], 'o'
    mov byte [rbp - 77], 'm'
    mov byte [rbp - 76], ' '
    mov byte [rbp - 75], 'p'
    mov byte [rbp - 74], 'r'
    mov byte [rbp - 73], 'i'
    mov byte [rbp - 72], 'n'
    mov byte [rbp - 71], 't'
    mov byte [rbp - 70], '_'
    mov byte [rbp - 69], 'f'
    mov byte [rbp - 68], 'u'
    mov byte [rbp - 67], 'n'
    mov byte [rbp - 66], 'c'
    mov byte [rbp - 65], 'v'
    mov byte [rbp - 64], 's'
    mov byte [rbp - 63], 'b'
    mov byte [rbp - 62], 'l'
    mov byte [rbp - 61], 'o'
    mov byte [rbp - 60], 'c'
    mov byte [rbp - 59], 'k'
    mov byte [rbp - 58], 's'
    mov byte [rbp - 57], 'c'
    mov byte [rbp - 56], 'o'
    mov byte [rbp - 55], 'p'
    mov byte [rbp - 54], 'e'
    mov byte [rbp - 53], ','
    mov byte [rbp - 52], 'F'
    mov byte [rbp - 51], 'u'
    mov byte [rbp - 50], 'n'
    mov byte [rbp - 49], 'c'
    mov byte [rbp - 48], 't'
    mov byte [rbp - 47], 'i'
    mov byte [rbp - 46], 'o'
    mov byte [rbp - 45], 'n'
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], 's'
    mov byte [rbp - 42], 'c'
    mov byte [rbp - 41], 'o'
    mov byte [rbp - 40], 'p'
    mov byte [rbp - 39], 'e'
    mov byte [rbp - 38], ' '
    mov byte [rbp - 37], ':'
    mov byte [rbp - 36], ' '
    mov byte [rbp - 35], '%'
    mov byte [rbp - 34], 's'
    mov byte [rbp - 33], 0x0A
    mov byte [rbp - 32], 0
    mov rdi, QWORD [rbp - 88]
    mov rax, QWORD [rbp - 24]
    mov QWORD [rbp - 96], rax
    mov rsi, QWORD [rbp - 96]
    mov QWORD [rbp - 104], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 104],rax
    leave
    ret

return_localvalue:
    push rbp
    mov  rbp, rsp
    sub  rsp, 32
    mov QWORD [rbp - 8], 1
    mov QWORD [rbp - 16], 1
    mov rax, QWORD [rbp - 16]
    leave
    ret
main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 144
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_global
    mov QWORD [rbp - 8],rax
    mov QWORD [rbp - 16], 0
    xor rax,rax
    call print_infunc
    mov QWORD [rbp - 16],rax
    mov QWORD [rbp - 24], 0
    xor rax,rax
    call print_inblock
    mov QWORD [rbp - 24],rax
    mov QWORD [rbp - 32], 0
    xor rax,rax
    call print_access_from_outer_block
    mov QWORD [rbp - 32],rax
    mov QWORD [rbp - 40], 0
    xor rax,rax
    call print_nestblocks
    mov QWORD [rbp - 40],rax
    mov QWORD [rbp - 48], 0
    xor rax,rax
    call print_funcvsblockscope
    mov QWORD [rbp - 48],rax
    mov QWORD [rbp - 56], 0
    xor rax,rax
    call return_localvalue
    mov QWORD [rbp - 56],rax
    mov rax, QWORD [rbp - 56]
    mov QWORD [rbp - 64], rax
    lea rax, [rbp - 104]
    mov QWORD [rbp - 112], rax
    mov byte [rbp - 104], 'F'
    mov byte [rbp - 103], 'r'
    mov byte [rbp - 102], 'o'
    mov byte [rbp - 101], 'm'
    mov byte [rbp - 100], ' '
    mov byte [rbp - 99], 'r'
    mov byte [rbp - 98], 'e'
    mov byte [rbp - 97], 't'
    mov byte [rbp - 96], 'u'
    mov byte [rbp - 95], 'r'
    mov byte [rbp - 94], 'n'
    mov byte [rbp - 93], '_'
    mov byte [rbp - 92], 'l'
    mov byte [rbp - 91], 'o'
    mov byte [rbp - 90], 'c'
    mov byte [rbp - 89], 'a'
    mov byte [rbp - 88], 'l'
    mov byte [rbp - 87], 'v'
    mov byte [rbp - 86], 'a'
    mov byte [rbp - 85], 'l'
    mov byte [rbp - 84], 'u'
    mov byte [rbp - 83], 'e'
    mov byte [rbp - 82], ','
    mov byte [rbp - 81], ' '
    mov byte [rbp - 80], 'V'
    mov byte [rbp - 79], 'a'
    mov byte [rbp - 78], 'l'
    mov byte [rbp - 77], 'u'
    mov byte [rbp - 76], 'e'
    mov byte [rbp - 75], ' '
    mov byte [rbp - 74], ':'
    mov byte [rbp - 73], ' '
    mov byte [rbp - 72], '%'
    mov byte [rbp - 71], 'd'
    mov byte [rbp - 70], 0x0A
    mov byte [rbp - 69], 0
    mov rdi, QWORD [rbp - 112]
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 120], rax
    mov rsi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

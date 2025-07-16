SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
deep_nesting:
    push rbp
    mov  rbp, rsp
    sub  rsp, 480
    mov QWORD [rbp - 8], 1
    .L0:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
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
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 2
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cqo
    idiv rbx
    mov QWORD [rbp - 40],rdx
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L3
    lea rax, [rbp - 136]
    mov QWORD [rbp - 144], rax
    mov byte [rbp - 136], 'F'
    mov byte [rbp - 135], 'r'
    mov byte [rbp - 134], 'o'
    mov byte [rbp - 133], 'm'
    mov byte [rbp - 132], ' '
    mov byte [rbp - 131], 'd'
    mov byte [rbp - 130], 'e'
    mov byte [rbp - 129], 'e'
    mov byte [rbp - 128], 'p'
    mov byte [rbp - 127], '_'
    mov byte [rbp - 126], 'n'
    mov byte [rbp - 125], 'e'
    mov byte [rbp - 124], 's'
    mov byte [rbp - 123], 't'
    mov byte [rbp - 122], 'i'
    mov byte [rbp - 121], 'n'
    mov byte [rbp - 120], 'g'
    mov byte [rbp - 119], ','
    mov byte [rbp - 118], ' '
    mov byte [rbp - 117], 'e'
    mov byte [rbp - 116], 'l'
    mov byte [rbp - 115], 's'
    mov byte [rbp - 114], 'e'
    mov byte [rbp - 113], ' '
    mov byte [rbp - 112], 'b'
    mov byte [rbp - 111], 'l'
    mov byte [rbp - 110], 'o'
    mov byte [rbp - 109], 'c'
    mov byte [rbp - 108], 'k'
    mov byte [rbp - 107], ' '
    mov byte [rbp - 106], 'w'
    mov byte [rbp - 105], 'h'
    mov byte [rbp - 104], 'e'
    mov byte [rbp - 103], 'n'
    mov byte [rbp - 102], ' '
    mov byte [rbp - 101], 'i'
    mov byte [rbp - 100], ' '
    mov byte [rbp - 99], '='
    mov byte [rbp - 98], ' '
    mov byte [rbp - 97], '%'
    mov byte [rbp - 96], 'd'
    mov byte [rbp - 95], 0x0A
    mov byte [rbp - 94], 0
    mov rdi, QWORD [rbp - 144]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov rsi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    jmp .L4
    .L3:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 168], rax
    .L5:
    mov QWORD [rbp - 176], 0
    mov QWORD [rbp - 184], 0
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 184], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 192], 0
    mov rax, QWORD [rbp - 184]
    mov rbx, QWORD [rbp - 192]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 176]
    cmp rax, 0
    jne .L6
    jmp .L7
    .L6:
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 200], rax
    mov rax, QWORD [rbp - 200]
    cmp rax, 1
    je .L9
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 208], rax
    mov rax, QWORD [rbp - 208]
    cmp rax, 2
    je .L10
    jmp .L11
    .L9:
    lea rax, [rbp - 272]
    mov QWORD [rbp - 280], rax
    mov byte [rbp - 272], 'F'
    mov byte [rbp - 271], 'r'
    mov byte [rbp - 270], 'o'
    mov byte [rbp - 269], 'm'
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], 'd'
    mov byte [rbp - 266], 'e'
    mov byte [rbp - 265], 'e'
    mov byte [rbp - 264], 'p'
    mov byte [rbp - 263], '_'
    mov byte [rbp - 262], 'n'
    mov byte [rbp - 261], 'e'
    mov byte [rbp - 260], 's'
    mov byte [rbp - 259], 't'
    mov byte [rbp - 258], 'i'
    mov byte [rbp - 257], 'n'
    mov byte [rbp - 256], 'g'
    mov byte [rbp - 255], ','
    mov byte [rbp - 254], ' '
    mov byte [rbp - 253], 'c'
    mov byte [rbp - 252], 'h'
    mov byte [rbp - 251], 'o'
    mov byte [rbp - 250], 'i'
    mov byte [rbp - 249], 'c'
    mov byte [rbp - 248], 'e'
    mov byte [rbp - 247], ' '
    mov byte [rbp - 246], '='
    mov byte [rbp - 245], ' '
    mov byte [rbp - 244], '1'
    mov byte [rbp - 243], ','
    mov byte [rbp - 242], ' '
    mov byte [rbp - 241], 'w'
    mov byte [rbp - 240], 'h'
    mov byte [rbp - 239], 'e'
    mov byte [rbp - 238], 'n'
    mov byte [rbp - 237], ' '
    mov byte [rbp - 236], 'i'
    mov byte [rbp - 235], ' '
    mov byte [rbp - 234], '='
    mov byte [rbp - 233], ' '
    mov byte [rbp - 232], '%'
    mov byte [rbp - 231], 'd'
    mov byte [rbp - 230], ','
    mov byte [rbp - 229], ' '
    mov byte [rbp - 228], 'j'
    mov byte [rbp - 227], ' '
    mov byte [rbp - 226], '='
    mov byte [rbp - 225], ' '
    mov byte [rbp - 224], '%'
    mov byte [rbp - 223], 'd'
    mov byte [rbp - 222], 0x0A
    mov byte [rbp - 221], 0
    mov rdi, QWORD [rbp - 280]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 288], rax
    mov rsi, QWORD [rbp - 288]
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 296], rax
    mov rdx, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 304],rax
    jmp .L8
    .L10:
    lea rax, [rbp - 360]
    mov QWORD [rbp - 368], rax
    mov byte [rbp - 360], 'F'
    mov byte [rbp - 359], 'r'
    mov byte [rbp - 358], 'o'
    mov byte [rbp - 357], 'm'
    mov byte [rbp - 356], ' '
    mov byte [rbp - 355], 'd'
    mov byte [rbp - 354], 'e'
    mov byte [rbp - 353], 'e'
    mov byte [rbp - 352], 'p'
    mov byte [rbp - 351], '_'
    mov byte [rbp - 350], 'n'
    mov byte [rbp - 349], 'e'
    mov byte [rbp - 348], 's'
    mov byte [rbp - 347], 't'
    mov byte [rbp - 346], 'i'
    mov byte [rbp - 345], 'n'
    mov byte [rbp - 344], 'g'
    mov byte [rbp - 343], ','
    mov byte [rbp - 342], ' '
    mov byte [rbp - 341], 'c'
    mov byte [rbp - 340], 'h'
    mov byte [rbp - 339], 'o'
    mov byte [rbp - 338], 'i'
    mov byte [rbp - 337], 'c'
    mov byte [rbp - 336], 'e'
    mov byte [rbp - 335], ' '
    mov byte [rbp - 334], '='
    mov byte [rbp - 333], ' '
    mov byte [rbp - 332], '2'
    mov byte [rbp - 331], ','
    mov byte [rbp - 330], ' '
    mov byte [rbp - 329], 'w'
    mov byte [rbp - 328], 'h'
    mov byte [rbp - 327], 'e'
    mov byte [rbp - 326], 'n'
    mov byte [rbp - 325], ' '
    mov byte [rbp - 324], 'i'
    mov byte [rbp - 323], ' '
    mov byte [rbp - 322], '='
    mov byte [rbp - 321], ' '
    mov byte [rbp - 320], '%'
    mov byte [rbp - 319], 'd'
    mov byte [rbp - 318], ','
    mov byte [rbp - 317], 'j'
    mov byte [rbp - 316], ' '
    mov byte [rbp - 315], '='
    mov byte [rbp - 314], ' '
    mov byte [rbp - 313], '%'
    mov byte [rbp - 312], 'd'
    mov byte [rbp - 311], 0x0A
    mov byte [rbp - 310], 0
    mov rdi, QWORD [rbp - 368]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 376], rax
    mov rsi, QWORD [rbp - 376]
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 384], rax
    mov rdx, QWORD [rbp - 384]
    mov QWORD [rbp - 392], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 392],rax
    jmp .L8
    .L11:
    lea rax, [rbp - 448]
    mov QWORD [rbp - 456], rax
    mov byte [rbp - 448], 'F'
    mov byte [rbp - 447], 'r'
    mov byte [rbp - 446], 'o'
    mov byte [rbp - 445], 'm'
    mov byte [rbp - 444], ' '
    mov byte [rbp - 443], 'd'
    mov byte [rbp - 442], 'e'
    mov byte [rbp - 441], 'e'
    mov byte [rbp - 440], 'p'
    mov byte [rbp - 439], '_'
    mov byte [rbp - 438], 'n'
    mov byte [rbp - 437], 'e'
    mov byte [rbp - 436], 's'
    mov byte [rbp - 435], 't'
    mov byte [rbp - 434], 'i'
    mov byte [rbp - 433], 'n'
    mov byte [rbp - 432], 'g'
    mov byte [rbp - 431], ','
    mov byte [rbp - 430], ' '
    mov byte [rbp - 429], 'c'
    mov byte [rbp - 428], 'h'
    mov byte [rbp - 427], 'o'
    mov byte [rbp - 426], 'i'
    mov byte [rbp - 425], 'c'
    mov byte [rbp - 424], 'e'
    mov byte [rbp - 423], ' '
    mov byte [rbp - 422], '='
    mov byte [rbp - 421], ' '
    mov byte [rbp - 420], 'd'
    mov byte [rbp - 419], 'e'
    mov byte [rbp - 418], 'f'
    mov byte [rbp - 417], 'a'
    mov byte [rbp - 416], 'u'
    mov byte [rbp - 415], 'l'
    mov byte [rbp - 414], 't'
    mov byte [rbp - 413], ','
    mov byte [rbp - 412], ' '
    mov byte [rbp - 411], 'w'
    mov byte [rbp - 410], 'h'
    mov byte [rbp - 409], 'e'
    mov byte [rbp - 408], 'n'
    mov byte [rbp - 407], ' '
    mov byte [rbp - 406], 'i'
    mov byte [rbp - 405], ' '
    mov byte [rbp - 404], '='
    mov byte [rbp - 403], ' '
    mov byte [rbp - 402], '%'
    mov byte [rbp - 401], 'd'
    mov byte [rbp - 400], 0x0A
    mov byte [rbp - 399], 0
    mov rdi, QWORD [rbp - 456]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 464], rax
    mov rsi, QWORD [rbp - 464]
    mov QWORD [rbp - 472], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 472],rax
    jmp .L8
    .L8:
    mov QWORD [rbp - 216], 0
    mov rax, [rbp - 168]
    dec rax
    mov [rbp - 216],rax
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 168], rax
    jmp .L5
    .L7:
    .L4:
    mov QWORD [rbp - 88], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 8], rax
    jmp .L0
    .L2:
    leave
    ret

while_if_while:
    push rbp
    mov  rbp, rsp
    sub  rsp, 336
    mov QWORD [rbp - 8], 1
    .L12:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 2
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L13
    jmp .L14
    .L13:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L15
    jmp .L16
    .L15:
    mov QWORD [rbp - 72], 0
    .L17:
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 88], rax
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 96], 3
    mov rax, QWORD [rbp - 88]
    mov rbx, QWORD [rbp - 96]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    cmp rax, 0
    jne .L18
    jmp .L19
    .L18:
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    cmp rax, 0
    je .L21
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 112], rax
    mov rax, QWORD [rbp - 112]
    cmp rax, 1
    je .L22
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 120], rax
    mov rax, QWORD [rbp - 120]
    cmp rax, 2
    je .L23
    jmp .L24
    .L21:
    lea rax, [rbp - 168]
    mov QWORD [rbp - 176], rax
    mov byte [rbp - 168], 'F'
    mov byte [rbp - 167], 'r'
    mov byte [rbp - 166], 'o'
    mov byte [rbp - 165], 'm'
    mov byte [rbp - 164], ' '
    mov byte [rbp - 163], 'w'
    mov byte [rbp - 162], 'h'
    mov byte [rbp - 161], 'i'
    mov byte [rbp - 160], 'l'
    mov byte [rbp - 159], 'e'
    mov byte [rbp - 158], '_'
    mov byte [rbp - 157], 'i'
    mov byte [rbp - 156], 'f'
    mov byte [rbp - 155], '_'
    mov byte [rbp - 154], 'w'
    mov byte [rbp - 153], 'h'
    mov byte [rbp - 152], 'i'
    mov byte [rbp - 151], 'l'
    mov byte [rbp - 150], 'e'
    mov byte [rbp - 149], ','
    mov byte [rbp - 148], ' '
    mov byte [rbp - 147], 'i'
    mov byte [rbp - 146], ' '
    mov byte [rbp - 145], 'V'
    mov byte [rbp - 144], 'a'
    mov byte [rbp - 143], 'l'
    mov byte [rbp - 142], 'u'
    mov byte [rbp - 141], 'e'
    mov byte [rbp - 140], ' '
    mov byte [rbp - 139], ':'
    mov byte [rbp - 138], ' '
    mov byte [rbp - 137], '%'
    mov byte [rbp - 136], 'd'
    mov byte [rbp - 135], 0x0A
    mov byte [rbp - 134], 0
    mov rdi, QWORD [rbp - 176]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 184], rax
    mov rsi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    jmp .L20
    .L22:
    lea rax, [rbp - 232]
    mov QWORD [rbp - 240], rax
    mov byte [rbp - 232], 'F'
    mov byte [rbp - 231], 'r'
    mov byte [rbp - 230], 'o'
    mov byte [rbp - 229], 'm'
    mov byte [rbp - 228], ' '
    mov byte [rbp - 227], 'w'
    mov byte [rbp - 226], 'h'
    mov byte [rbp - 225], 'i'
    mov byte [rbp - 224], 'l'
    mov byte [rbp - 223], 'e'
    mov byte [rbp - 222], '_'
    mov byte [rbp - 221], 'i'
    mov byte [rbp - 220], 'f'
    mov byte [rbp - 219], '_'
    mov byte [rbp - 218], 'w'
    mov byte [rbp - 217], 'h'
    mov byte [rbp - 216], 'i'
    mov byte [rbp - 215], 'l'
    mov byte [rbp - 214], 'e'
    mov byte [rbp - 213], ','
    mov byte [rbp - 212], ' '
    mov byte [rbp - 211], 'i'
    mov byte [rbp - 210], ' '
    mov byte [rbp - 209], 'V'
    mov byte [rbp - 208], 'a'
    mov byte [rbp - 207], 'l'
    mov byte [rbp - 206], 'u'
    mov byte [rbp - 205], 'e'
    mov byte [rbp - 204], ' '
    mov byte [rbp - 203], ':'
    mov byte [rbp - 202], ' '
    mov byte [rbp - 201], '%'
    mov byte [rbp - 200], 'd'
    mov byte [rbp - 199], 0x0A
    mov byte [rbp - 198], 0
    mov rdi, QWORD [rbp - 240]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 248], rax
    mov rsi, QWORD [rbp - 248]
    mov QWORD [rbp - 256], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 256],rax
    jmp .L20
    .L23:
    lea rax, [rbp - 296]
    mov QWORD [rbp - 304], rax
    mov byte [rbp - 296], 'F'
    mov byte [rbp - 295], 'r'
    mov byte [rbp - 294], 'o'
    mov byte [rbp - 293], 'm'
    mov byte [rbp - 292], ' '
    mov byte [rbp - 291], 'w'
    mov byte [rbp - 290], 'h'
    mov byte [rbp - 289], 'i'
    mov byte [rbp - 288], 'l'
    mov byte [rbp - 287], 'e'
    mov byte [rbp - 286], '_'
    mov byte [rbp - 285], 'i'
    mov byte [rbp - 284], 'f'
    mov byte [rbp - 283], '_'
    mov byte [rbp - 282], 'w'
    mov byte [rbp - 281], 'h'
    mov byte [rbp - 280], 'i'
    mov byte [rbp - 279], 'l'
    mov byte [rbp - 278], 'e'
    mov byte [rbp - 277], ','
    mov byte [rbp - 276], ' '
    mov byte [rbp - 275], 'i'
    mov byte [rbp - 274], ' '
    mov byte [rbp - 273], 'V'
    mov byte [rbp - 272], 'a'
    mov byte [rbp - 271], 'l'
    mov byte [rbp - 270], 'u'
    mov byte [rbp - 269], 'e'
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], ':'
    mov byte [rbp - 266], ' '
    mov byte [rbp - 265], '%'
    mov byte [rbp - 264], 'd'
    mov byte [rbp - 263], 0x0A
    mov byte [rbp - 262], 0
    mov rdi, QWORD [rbp - 304]
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 312], rax
    mov rsi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    jmp .L20
    .L24:
    .L20:
    mov QWORD [rbp - 128], 0
    mov rax, [rbp - 72]
    inc rax
    mov [rbp - 128],rax
    mov rax, QWORD [rbp - 128]
    mov QWORD [rbp - 72], rax
    jmp .L17
    .L19:
    .L16:
    mov QWORD [rbp - 64], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 8], rax
    jmp .L12
    .L14:
    leave
    ret

if_in_switch:
    push rbp
    mov  rbp, rsp
    sub  rsp, 400
    mov QWORD [rbp - 8], 0
    .L25:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L26
    jmp .L27
    .L26:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    add rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 1
    je .L29
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 80], rax
    mov rax, QWORD [rbp - 80]
    cmp rax, 2
    je .L30
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 88], rax
    mov rax, QWORD [rbp - 88]
    cmp rax, 3
    je .L31
    jmp .L32
    .L29:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 64]
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
    mov QWORD [rbp - 144], 1
    mov rax, QWORD [rbp - 136]
    mov rbx, QWORD [rbp - 144]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    cmp rax, 0
    jne .L33
    jmp .L34
    .L33:
    lea rax, [rbp - 272]
    mov QWORD [rbp - 280], rax
    mov byte [rbp - 272], 'F'
    mov byte [rbp - 271], 'r'
    mov byte [rbp - 270], 'o'
    mov byte [rbp - 269], 'm'
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], 'i'
    mov byte [rbp - 266], 'f'
    mov byte [rbp - 265], '_'
    mov byte [rbp - 264], 'i'
    mov byte [rbp - 263], 'n'
    mov byte [rbp - 262], '_'
    mov byte [rbp - 261], 's'
    mov byte [rbp - 260], 'w'
    mov byte [rbp - 259], 'i'
    mov byte [rbp - 258], 't'
    mov byte [rbp - 257], 'c'
    mov byte [rbp - 256], 'h'
    mov byte [rbp - 255], ','
    mov byte [rbp - 254], ' '
    mov byte [rbp - 253], 'i'
    mov byte [rbp - 252], ' '
    mov byte [rbp - 251], 'V'
    mov byte [rbp - 250], 'a'
    mov byte [rbp - 249], 'l'
    mov byte [rbp - 248], 'u'
    mov byte [rbp - 247], 'e'
    mov byte [rbp - 246], ' '
    mov byte [rbp - 245], ':'
    mov byte [rbp - 244], ' '
    mov byte [rbp - 243], '%'
    mov byte [rbp - 242], 'd'
    mov byte [rbp - 241], 0x0A
    mov byte [rbp - 240], 0
    mov rdi, QWORD [rbp - 280]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 288], rax
    mov rsi, QWORD [rbp - 288]
    mov QWORD [rbp - 296], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 296],rax
    .L34:
    jmp .L28
    .L30:
    .L35:
    mov QWORD [rbp - 152], 0
    mov QWORD [rbp - 160], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 160], rax
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 168], 0
    mov rax, QWORD [rbp - 160]
    mov rbx, QWORD [rbp - 168]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 152], rax
    mov rax, QWORD [rbp - 152]
    cmp rax, 0
    jne .L36
    jmp .L37
    .L36:
    lea rax, [rbp - 336]
    mov QWORD [rbp - 344], rax
    mov byte [rbp - 336], 'F'
    mov byte [rbp - 335], 'r'
    mov byte [rbp - 334], 'o'
    mov byte [rbp - 333], 'm'
    mov byte [rbp - 332], ' '
    mov byte [rbp - 331], 'i'
    mov byte [rbp - 330], 'f'
    mov byte [rbp - 329], '_'
    mov byte [rbp - 328], 'i'
    mov byte [rbp - 327], 'n'
    mov byte [rbp - 326], '_'
    mov byte [rbp - 325], 's'
    mov byte [rbp - 324], 'w'
    mov byte [rbp - 323], 'i'
    mov byte [rbp - 322], 't'
    mov byte [rbp - 321], 'c'
    mov byte [rbp - 320], 'h'
    mov byte [rbp - 319], ','
    mov byte [rbp - 318], ' '
    mov byte [rbp - 317], 'i'
    mov byte [rbp - 316], ' '
    mov byte [rbp - 315], 'V'
    mov byte [rbp - 314], 'a'
    mov byte [rbp - 313], 'l'
    mov byte [rbp - 312], 'u'
    mov byte [rbp - 311], 'e'
    mov byte [rbp - 310], ' '
    mov byte [rbp - 309], ':'
    mov byte [rbp - 308], ' '
    mov byte [rbp - 307], '%'
    mov byte [rbp - 306], 'd'
    mov byte [rbp - 305], 0x0A
    mov byte [rbp - 304], 0
    mov rdi, QWORD [rbp - 344]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 352], rax
    mov rsi, QWORD [rbp - 352]
    mov QWORD [rbp - 360], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 360],rax
    mov QWORD [rbp - 368], 0
    mov QWORD [rbp - 376], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 376], rax
    mov QWORD [rbp - 384], 0
    mov QWORD [rbp - 384], 1
    mov rax, QWORD [rbp - 376]
    mov rbx, QWORD [rbp - 384]
    sub rax,rbx
    mov QWORD [rbp - 368], rax
    mov rax, QWORD [rbp - 368]
    mov QWORD [rbp - 64], rax
    jmp .L35
    .L37:
    jmp .L28
    .L31:
    lea rax, [rbp - 208]
    mov QWORD [rbp - 216], rax
    mov byte [rbp - 208], 'F'
    mov byte [rbp - 207], 'r'
    mov byte [rbp - 206], 'o'
    mov byte [rbp - 205], 'm'
    mov byte [rbp - 204], ' '
    mov byte [rbp - 203], 'i'
    mov byte [rbp - 202], 'f'
    mov byte [rbp - 201], '_'
    mov byte [rbp - 200], 'i'
    mov byte [rbp - 199], 'n'
    mov byte [rbp - 198], '_'
    mov byte [rbp - 197], 's'
    mov byte [rbp - 196], 'w'
    mov byte [rbp - 195], 'i'
    mov byte [rbp - 194], 't'
    mov byte [rbp - 193], 'c'
    mov byte [rbp - 192], 'h'
    mov byte [rbp - 191], ','
    mov byte [rbp - 190], ' '
    mov byte [rbp - 189], 'i'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], 'V'
    mov byte [rbp - 186], 'a'
    mov byte [rbp - 185], 'l'
    mov byte [rbp - 184], 'u'
    mov byte [rbp - 183], 'e'
    mov byte [rbp - 182], ' '
    mov byte [rbp - 181], ':'
    mov byte [rbp - 180], ' '
    mov byte [rbp - 179], '%'
    mov byte [rbp - 178], 'd'
    mov byte [rbp - 177], 0x0A
    mov byte [rbp - 176], 0
    mov rdi, QWORD [rbp - 216]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 224], rax
    mov rsi, QWORD [rbp - 224]
    mov QWORD [rbp - 232], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 232],rax
    jmp .L28
    .L32:
    .L28:
    mov QWORD [rbp - 96], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 8], rax
    jmp .L25
    .L27:
    leave
    ret

switch_in_if:
    push rbp
    mov  rbp, rsp
    sub  rsp, 352
    mov QWORD [rbp - 8], 3
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
    jne .L38
    lea rax, [rbp - 72]
    mov QWORD [rbp - 80], rax
    mov byte [rbp - 72], 'F'
    mov byte [rbp - 71], 'r'
    mov byte [rbp - 70], 'o'
    mov byte [rbp - 69], 'm'
    mov byte [rbp - 68], ' '
    mov byte [rbp - 67], 's'
    mov byte [rbp - 66], 'w'
    mov byte [rbp - 65], 'i'
    mov byte [rbp - 64], 't'
    mov byte [rbp - 63], 'c'
    mov byte [rbp - 62], 'h'
    mov byte [rbp - 61], '_'
    mov byte [rbp - 60], 'i'
    mov byte [rbp - 59], 'n'
    mov byte [rbp - 58], '_'
    mov byte [rbp - 57], 'i'
    mov byte [rbp - 56], 'f'
    mov byte [rbp - 55], ','
    mov byte [rbp - 54], ' '
    mov byte [rbp - 53], 'a'
    mov byte [rbp - 52], ' '
    mov byte [rbp - 51], 'V'
    mov byte [rbp - 50], 'a'
    mov byte [rbp - 49], 'l'
    mov byte [rbp - 48], 'u'
    mov byte [rbp - 47], 'e'
    mov byte [rbp - 46], ' '
    mov byte [rbp - 45], ':'
    mov byte [rbp - 44], ' '
    mov byte [rbp - 43], '%'
    mov byte [rbp - 42], 'd'
    mov byte [rbp - 41], 0x0A
    mov byte [rbp - 40], 0
    mov rdi, QWORD [rbp - 80]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 88], rax
    mov rsi, QWORD [rbp - 88]
    mov QWORD [rbp - 96], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 96],rax
    jmp .L39
    .L38:
    .L40:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 0
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    cmp rax, 0
    jne .L41
    jmp .L42
    .L41:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    cmp rax, 1
    je .L44
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    cmp rax, 2
    je .L45
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    cmp rax, 3
    je .L46
    jmp .L47
    .L44:
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'F'
    mov byte [rbp - 191], 'r'
    mov byte [rbp - 190], 'o'
    mov byte [rbp - 189], 'm'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], 's'
    mov byte [rbp - 186], 'w'
    mov byte [rbp - 185], 'i'
    mov byte [rbp - 184], 't'
    mov byte [rbp - 183], 'c'
    mov byte [rbp - 182], 'h'
    mov byte [rbp - 181], '_'
    mov byte [rbp - 180], 'i'
    mov byte [rbp - 179], 'n'
    mov byte [rbp - 178], '_'
    mov byte [rbp - 177], 'i'
    mov byte [rbp - 176], 'f'
    mov byte [rbp - 175], ','
    mov byte [rbp - 174], ' '
    mov byte [rbp - 173], 'a'
    mov byte [rbp - 172], ' '
    mov byte [rbp - 171], 'V'
    mov byte [rbp - 170], 'a'
    mov byte [rbp - 169], 'l'
    mov byte [rbp - 168], 'u'
    mov byte [rbp - 167], 'e'
    mov byte [rbp - 166], ' '
    mov byte [rbp - 165], ':'
    mov byte [rbp - 164], ' '
    mov byte [rbp - 163], '%'
    mov byte [rbp - 162], 'd'
    mov byte [rbp - 161], 0x0A
    mov byte [rbp - 160], 0
    mov rdi, QWORD [rbp - 200]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 208], rax
    mov rsi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    jmp .L43
    .L45:
    lea rax, [rbp - 256]
    mov QWORD [rbp - 264], rax
    mov byte [rbp - 256], 'F'
    mov byte [rbp - 255], 'r'
    mov byte [rbp - 254], 'o'
    mov byte [rbp - 253], 'm'
    mov byte [rbp - 252], ' '
    mov byte [rbp - 251], 's'
    mov byte [rbp - 250], 'w'
    mov byte [rbp - 249], 'i'
    mov byte [rbp - 248], 't'
    mov byte [rbp - 247], 'c'
    mov byte [rbp - 246], 'h'
    mov byte [rbp - 245], '_'
    mov byte [rbp - 244], 'i'
    mov byte [rbp - 243], 'n'
    mov byte [rbp - 242], '_'
    mov byte [rbp - 241], 'i'
    mov byte [rbp - 240], 'f'
    mov byte [rbp - 239], ','
    mov byte [rbp - 238], ' '
    mov byte [rbp - 237], 'a'
    mov byte [rbp - 236], ' '
    mov byte [rbp - 235], 'V'
    mov byte [rbp - 234], 'a'
    mov byte [rbp - 233], 'l'
    mov byte [rbp - 232], 'u'
    mov byte [rbp - 231], 'e'
    mov byte [rbp - 230], ' '
    mov byte [rbp - 229], ':'
    mov byte [rbp - 228], ' '
    mov byte [rbp - 227], '%'
    mov byte [rbp - 226], 'd'
    mov byte [rbp - 225], 0x0A
    mov byte [rbp - 224], 0
    mov rdi, QWORD [rbp - 264]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 272], rax
    mov rsi, QWORD [rbp - 272]
    mov QWORD [rbp - 280], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 280],rax
    jmp .L43
    .L46:
    lea rax, [rbp - 320]
    mov QWORD [rbp - 328], rax
    mov byte [rbp - 320], 'F'
    mov byte [rbp - 319], 'r'
    mov byte [rbp - 318], 'o'
    mov byte [rbp - 317], 'm'
    mov byte [rbp - 316], ' '
    mov byte [rbp - 315], 's'
    mov byte [rbp - 314], 'w'
    mov byte [rbp - 313], 'i'
    mov byte [rbp - 312], 't'
    mov byte [rbp - 311], 'c'
    mov byte [rbp - 310], 'h'
    mov byte [rbp - 309], '_'
    mov byte [rbp - 308], 'i'
    mov byte [rbp - 307], 'n'
    mov byte [rbp - 306], '_'
    mov byte [rbp - 305], 'i'
    mov byte [rbp - 304], 'f'
    mov byte [rbp - 303], ','
    mov byte [rbp - 302], ' '
    mov byte [rbp - 301], 'a'
    mov byte [rbp - 300], ' '
    mov byte [rbp - 299], 'V'
    mov byte [rbp - 298], 'a'
    mov byte [rbp - 297], 'l'
    mov byte [rbp - 296], 'u'
    mov byte [rbp - 295], 'e'
    mov byte [rbp - 294], ' '
    mov byte [rbp - 293], ':'
    mov byte [rbp - 292], ' '
    mov byte [rbp - 291], '%'
    mov byte [rbp - 290], 'd'
    mov byte [rbp - 289], 0x0A
    mov byte [rbp - 288], 0
    mov rdi, QWORD [rbp - 328]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 336], rax
    mov rsi, QWORD [rbp - 336]
    mov QWORD [rbp - 344], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 344],rax
    jmp .L43
    .L47:
    .L43:
    mov QWORD [rbp - 152], 0
    mov rax, [rbp - 8]
    dec rax
    mov [rbp - 152],rax
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 8], rax
    jmp .L40
    .L42:
    .L39:
    leave
    ret

reuse_loop_counters:
    push rbp
    mov  rbp, rsp
    sub  rsp, 336
    mov QWORD [rbp - 8], 1
    .L48:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 2
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L49
    jmp .L50
    .L49:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 2
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    imul rax,rbx
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 64], rax
    .L51:
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 0
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 0
    jne .L52
    jmp .L53
    .L52:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 64]
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
    jne .L54
    lea rax, [rbp - 200]
    mov QWORD [rbp - 208], rax
    mov byte [rbp - 200], 'F'
    mov byte [rbp - 199], 'r'
    mov byte [rbp - 198], 'o'
    mov byte [rbp - 197], 'm'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], 'r'
    mov byte [rbp - 194], 'e'
    mov byte [rbp - 193], 'u'
    mov byte [rbp - 192], 's'
    mov byte [rbp - 191], 'e'
    mov byte [rbp - 190], '_'
    mov byte [rbp - 189], 'l'
    mov byte [rbp - 188], 'o'
    mov byte [rbp - 187], 'o'
    mov byte [rbp - 186], 'p'
    mov byte [rbp - 185], '_'
    mov byte [rbp - 184], 'c'
    mov byte [rbp - 183], 'o'
    mov byte [rbp - 182], 'u'
    mov byte [rbp - 181], 'n'
    mov byte [rbp - 180], 't'
    mov byte [rbp - 179], 'e'
    mov byte [rbp - 178], 'r'
    mov byte [rbp - 177], 's'
    mov byte [rbp - 176], ','
    mov byte [rbp - 175], ' '
    mov byte [rbp - 174], 'k'
    mov byte [rbp - 173], ' '
    mov byte [rbp - 172], 'V'
    mov byte [rbp - 171], 'a'
    mov byte [rbp - 170], 'l'
    mov byte [rbp - 169], 'u'
    mov byte [rbp - 168], 'e'
    mov byte [rbp - 167], ' '
    mov byte [rbp - 166], ':'
    mov byte [rbp - 165], ' '
    mov byte [rbp - 164], '%'
    mov byte [rbp - 163], 'd'
    mov byte [rbp - 162], 0x0A
    mov byte [rbp - 161], 0
    mov rdi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    mov QWORD [rbp - 224], 0
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 224], rax
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 232], 10
    mov rax, QWORD [rbp - 224]
    mov rbx, QWORD [rbp - 232]
    imul rax,rbx
    mov QWORD [rbp - 216], rax
    mov rax, QWORD [rbp - 216]
    mov QWORD [rbp - 240], rax
    mov rsi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    jmp .L55
    .L54:
    lea rax, [rbp - 296]
    mov QWORD [rbp - 304], rax
    mov byte [rbp - 296], 'F'
    mov byte [rbp - 295], 'r'
    mov byte [rbp - 294], 'o'
    mov byte [rbp - 293], 'm'
    mov byte [rbp - 292], ' '
    mov byte [rbp - 291], 'r'
    mov byte [rbp - 290], 'e'
    mov byte [rbp - 289], 'u'
    mov byte [rbp - 288], 's'
    mov byte [rbp - 287], 'e'
    mov byte [rbp - 286], '_'
    mov byte [rbp - 285], 'l'
    mov byte [rbp - 284], 'o'
    mov byte [rbp - 283], 'o'
    mov byte [rbp - 282], 'p'
    mov byte [rbp - 281], '_'
    mov byte [rbp - 280], 'c'
    mov byte [rbp - 279], 'o'
    mov byte [rbp - 278], 'u'
    mov byte [rbp - 277], 'n'
    mov byte [rbp - 276], 't'
    mov byte [rbp - 275], 'e'
    mov byte [rbp - 274], 'r'
    mov byte [rbp - 273], 's'
    mov byte [rbp - 272], ','
    mov byte [rbp - 271], ' '
    mov byte [rbp - 270], 'k'
    mov byte [rbp - 269], ' '
    mov byte [rbp - 268], 'V'
    mov byte [rbp - 267], 'a'
    mov byte [rbp - 266], 'l'
    mov byte [rbp - 265], 'u'
    mov byte [rbp - 264], 'e'
    mov byte [rbp - 263], ' '
    mov byte [rbp - 262], ':'
    mov byte [rbp - 261], ' '
    mov byte [rbp - 260], '%'
    mov byte [rbp - 259], 'd'
    mov byte [rbp - 258], 0x0A
    mov byte [rbp - 257], 0
    mov rdi, QWORD [rbp - 304]
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 312], rax
    mov rsi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    .L55:
    mov QWORD [rbp - 152], 0
    mov rax, [rbp - 64]
    dec rax
    mov [rbp - 152],rax
    mov rax, QWORD [rbp - 152]
    mov QWORD [rbp - 64], rax
    jmp .L51
    .L53:
    mov QWORD [rbp - 96], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 96],rax
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 8], rax
    jmp .L48
    .L50:
    leave
    ret

recursively_growing_blocks:
    push rbp
    mov  rbp, rsp
    sub  rsp, 320
    mov QWORD [rbp - 8], 0
    .L56:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L57
    jmp .L58
    .L57:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 1
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L59
    lea rax, [rbp - 104]
    mov QWORD [rbp - 112], rax
    mov byte [rbp - 104], 'F'
    mov byte [rbp - 103], 'r'
    mov byte [rbp - 102], 'o'
    mov byte [rbp - 101], 'm'
    mov byte [rbp - 100], ' '
    mov byte [rbp - 99], 'g'
    mov byte [rbp - 98], 'r'
    mov byte [rbp - 97], 'o'
    mov byte [rbp - 96], 'w'
    mov byte [rbp - 95], 'i'
    mov byte [rbp - 94], 'n'
    mov byte [rbp - 93], 'g'
    mov byte [rbp - 92], '_'
    mov byte [rbp - 91], 'b'
    mov byte [rbp - 90], 'l'
    mov byte [rbp - 89], 'o'
    mov byte [rbp - 88], 'c'
    mov byte [rbp - 87], 'k'
    mov byte [rbp - 86], 's'
    mov byte [rbp - 85], ','
    mov byte [rbp - 84], ' '
    mov byte [rbp - 83], 'i'
    mov byte [rbp - 82], ' '
    mov byte [rbp - 81], 'V'
    mov byte [rbp - 80], 'a'
    mov byte [rbp - 79], 'l'
    mov byte [rbp - 78], 'u'
    mov byte [rbp - 77], 'e'
    mov byte [rbp - 76], ' '
    mov byte [rbp - 75], ':'
    mov byte [rbp - 74], ' '
    mov byte [rbp - 73], '%'
    mov byte [rbp - 72], 'd'
    mov byte [rbp - 71], 0x0A
    mov byte [rbp - 70], 0
    mov rdi, QWORD [rbp - 112]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 120], rax
    mov rsi, QWORD [rbp - 120]
    mov QWORD [rbp - 128], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 128],rax
    jmp .L60
    .L59:
    mov QWORD [rbp - 136], 0
    .L61:
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 1
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    cmp rax, 0
    jne .L62
    jmp .L63
    .L62:
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 168], rax
    mov rax, QWORD [rbp - 168]
    cmp rax, 0
    je .L65
    mov rax, QWORD [rbp - 136]
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 176]
    cmp rax, 1
    je .L66
    jmp .L67
    .L65:
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], 'F'
    mov byte [rbp - 223], 'r'
    mov byte [rbp - 222], 'o'
    mov byte [rbp - 221], 'm'
    mov byte [rbp - 220], ' '
    mov byte [rbp - 219], 'g'
    mov byte [rbp - 218], 'r'
    mov byte [rbp - 217], 'o'
    mov byte [rbp - 216], 'w'
    mov byte [rbp - 215], 'i'
    mov byte [rbp - 214], 'n'
    mov byte [rbp - 213], 'g'
    mov byte [rbp - 212], '_'
    mov byte [rbp - 211], 'b'
    mov byte [rbp - 210], 'l'
    mov byte [rbp - 209], 'o'
    mov byte [rbp - 208], 'c'
    mov byte [rbp - 207], 'k'
    mov byte [rbp - 206], 's'
    mov byte [rbp - 205], ','
    mov byte [rbp - 204], ' '
    mov byte [rbp - 203], 'i'
    mov byte [rbp - 202], ' '
    mov byte [rbp - 201], 'V'
    mov byte [rbp - 200], 'a'
    mov byte [rbp - 199], 'l'
    mov byte [rbp - 198], 'u'
    mov byte [rbp - 197], 'e'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], ':'
    mov byte [rbp - 194], ' '
    mov byte [rbp - 193], '%'
    mov byte [rbp - 192], 'd'
    mov byte [rbp - 191], 0x0A
    mov byte [rbp - 190], 0
    mov rdi, QWORD [rbp - 232]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 240], rax
    mov rsi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    jmp .L64
    .L66:
    lea rax, [rbp - 288]
    mov QWORD [rbp - 296], rax
    mov byte [rbp - 288], 'F'
    mov byte [rbp - 287], 'r'
    mov byte [rbp - 286], 'o'
    mov byte [rbp - 285], 'm'
    mov byte [rbp - 284], ' '
    mov byte [rbp - 283], 'g'
    mov byte [rbp - 282], 'r'
    mov byte [rbp - 281], 'o'
    mov byte [rbp - 280], 'w'
    mov byte [rbp - 279], 'i'
    mov byte [rbp - 278], 'n'
    mov byte [rbp - 277], 'g'
    mov byte [rbp - 276], '_'
    mov byte [rbp - 275], 'b'
    mov byte [rbp - 274], 'l'
    mov byte [rbp - 273], 'o'
    mov byte [rbp - 272], 'c'
    mov byte [rbp - 271], 'k'
    mov byte [rbp - 270], 's'
    mov byte [rbp - 269], ','
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], 'i'
    mov byte [rbp - 266], ' '
    mov byte [rbp - 265], 'V'
    mov byte [rbp - 264], 'a'
    mov byte [rbp - 263], 'l'
    mov byte [rbp - 262], 'u'
    mov byte [rbp - 261], 'e'
    mov byte [rbp - 260], ' '
    mov byte [rbp - 259], ':'
    mov byte [rbp - 258], ' '
    mov byte [rbp - 257], '%'
    mov byte [rbp - 256], 'd'
    mov byte [rbp - 255], 0x0A
    mov byte [rbp - 254], 0
    mov rdi, QWORD [rbp - 296]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 304], rax
    mov rsi, QWORD [rbp - 304]
    mov QWORD [rbp - 312], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 312],rax
    jmp .L64
    .L67:
    .L64:
    mov QWORD [rbp - 184], 0
    mov rax, [rbp - 136]
    inc rax
    mov [rbp - 184],rax
    mov rax, QWORD [rbp - 184]
    mov QWORD [rbp - 136], rax
    jmp .L61
    .L63:
    .L60:
    mov QWORD [rbp - 64], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 8], rax
    jmp .L56
    .L58:
    leave
    ret

mixed_control_flow:
    push rbp
    mov  rbp, rsp
    sub  rsp, 480
    mov QWORD [rbp - 8], 1
    .L68:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L69
    jmp .L70
    .L69:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 2
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L71
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 1
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 72], rax
    mov rax, QWORD [rbp - 72]
    cmp rax, 0
    jne .L73
    lea rax, [rbp - 128]
    mov QWORD [rbp - 136], rax
    mov byte [rbp - 128], 'F'
    mov byte [rbp - 127], 'r'
    mov byte [rbp - 126], 'o'
    mov byte [rbp - 125], 'm'
    mov byte [rbp - 124], ' '
    mov byte [rbp - 123], 'm'
    mov byte [rbp - 122], 'i'
    mov byte [rbp - 121], 'x'
    mov byte [rbp - 120], 'e'
    mov byte [rbp - 119], 'd'
    mov byte [rbp - 118], '_'
    mov byte [rbp - 117], 'c'
    mov byte [rbp - 116], 'o'
    mov byte [rbp - 115], 'n'
    mov byte [rbp - 114], 't'
    mov byte [rbp - 113], 'r'
    mov byte [rbp - 112], 'o'
    mov byte [rbp - 111], 'l'
    mov byte [rbp - 110], '_'
    mov byte [rbp - 109], 'f'
    mov byte [rbp - 108], 'l'
    mov byte [rbp - 107], 'o'
    mov byte [rbp - 106], 'w'
    mov byte [rbp - 105], ','
    mov byte [rbp - 104], ' '
    mov byte [rbp - 103], 'x'
    mov byte [rbp - 102], ' '
    mov byte [rbp - 101], 'V'
    mov byte [rbp - 100], 'a'
    mov byte [rbp - 99], 'l'
    mov byte [rbp - 98], 'u'
    mov byte [rbp - 97], 'e'
    mov byte [rbp - 96], ' '
    mov byte [rbp - 95], ':'
    mov byte [rbp - 94], ' '
    mov byte [rbp - 93], '%'
    mov byte [rbp - 92], 'd'
    mov byte [rbp - 91], 0x0A
    mov byte [rbp - 90], 0
    mov rdi, QWORD [rbp - 136]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 144], rax
    mov rsi, QWORD [rbp - 144]
    mov QWORD [rbp - 152], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 152],rax
    jmp .L74
    .L73:
    lea rax, [rbp - 192]
    mov QWORD [rbp - 200], rax
    mov byte [rbp - 192], 'F'
    mov byte [rbp - 191], 'r'
    mov byte [rbp - 190], 'o'
    mov byte [rbp - 189], 'm'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], 'm'
    mov byte [rbp - 186], 'i'
    mov byte [rbp - 185], 'x'
    mov byte [rbp - 184], 'e'
    mov byte [rbp - 183], 'd'
    mov byte [rbp - 182], '_'
    mov byte [rbp - 181], 'c'
    mov byte [rbp - 180], 'o'
    mov byte [rbp - 179], 'n'
    mov byte [rbp - 178], 't'
    mov byte [rbp - 177], 'r'
    mov byte [rbp - 176], 'o'
    mov byte [rbp - 175], 'l'
    mov byte [rbp - 174], '_'
    mov byte [rbp - 173], 'f'
    mov byte [rbp - 172], 'l'
    mov byte [rbp - 171], 'o'
    mov byte [rbp - 170], 'w'
    mov byte [rbp - 169], ','
    mov byte [rbp - 168], ' '
    mov byte [rbp - 167], 'x'
    mov byte [rbp - 166], ' '
    mov byte [rbp - 165], 'V'
    mov byte [rbp - 164], 'a'
    mov byte [rbp - 163], 'l'
    mov byte [rbp - 162], 'u'
    mov byte [rbp - 161], 'e'
    mov byte [rbp - 160], ' '
    mov byte [rbp - 159], ':'
    mov byte [rbp - 158], ' '
    mov byte [rbp - 157], '%'
    mov byte [rbp - 156], 'd'
    mov byte [rbp - 155], 0x0A
    mov byte [rbp - 154], 0
    mov rdi, QWORD [rbp - 200]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 208], rax
    mov rsi, QWORD [rbp - 208]
    mov QWORD [rbp - 216], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 216],rax
    .L74:
    jmp .L72
    .L71:
    mov QWORD [rbp - 224], 3
    .L75:
    mov QWORD [rbp - 232], 0
    mov QWORD [rbp - 240], 0
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 240], rax
    mov QWORD [rbp - 248], 0
    mov QWORD [rbp - 248], 0
    mov rax, QWORD [rbp - 240]
    mov rbx, QWORD [rbp - 248]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 232], rax
    mov rax, QWORD [rbp - 232]
    cmp rax, 0
    jne .L76
    jmp .L77
    .L76:
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 256]
    cmp rax, 1
    je .L79
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 264], rax
    mov rax, QWORD [rbp - 264]
    cmp rax, 2
    je .L80
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 272], rax
    mov rax, QWORD [rbp - 272]
    cmp rax, 3
    je .L81
    jmp .L82
    .L79:
    lea rax, [rbp - 320]
    mov QWORD [rbp - 328], rax
    mov byte [rbp - 320], 'F'
    mov byte [rbp - 319], 'r'
    mov byte [rbp - 318], 'o'
    mov byte [rbp - 317], 'm'
    mov byte [rbp - 316], ' '
    mov byte [rbp - 315], 'm'
    mov byte [rbp - 314], 'i'
    mov byte [rbp - 313], 'x'
    mov byte [rbp - 312], 'e'
    mov byte [rbp - 311], 'd'
    mov byte [rbp - 310], '_'
    mov byte [rbp - 309], 'c'
    mov byte [rbp - 308], 'o'
    mov byte [rbp - 307], 'n'
    mov byte [rbp - 306], 't'
    mov byte [rbp - 305], 'r'
    mov byte [rbp - 304], 'o'
    mov byte [rbp - 303], 'l'
    mov byte [rbp - 302], '_'
    mov byte [rbp - 301], 'f'
    mov byte [rbp - 300], 'l'
    mov byte [rbp - 299], 'o'
    mov byte [rbp - 298], 'w'
    mov byte [rbp - 297], ','
    mov byte [rbp - 296], ' '
    mov byte [rbp - 295], 'y'
    mov byte [rbp - 294], ' '
    mov byte [rbp - 293], 'V'
    mov byte [rbp - 292], 'a'
    mov byte [rbp - 291], 'l'
    mov byte [rbp - 290], 'u'
    mov byte [rbp - 289], 'e'
    mov byte [rbp - 288], ' '
    mov byte [rbp - 287], ':'
    mov byte [rbp - 286], ' '
    mov byte [rbp - 285], '%'
    mov byte [rbp - 284], 'd'
    mov byte [rbp - 283], 0x0A
    mov byte [rbp - 282], 0
    mov rdi, QWORD [rbp - 328]
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 336], rax
    mov rsi, QWORD [rbp - 336]
    mov QWORD [rbp - 344], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 344],rax
    jmp .L78
    .L80:
    lea rax, [rbp - 384]
    mov QWORD [rbp - 392], rax
    mov byte [rbp - 384], 'F'
    mov byte [rbp - 383], 'r'
    mov byte [rbp - 382], 'o'
    mov byte [rbp - 381], 'm'
    mov byte [rbp - 380], ' '
    mov byte [rbp - 379], 'm'
    mov byte [rbp - 378], 'i'
    mov byte [rbp - 377], 'x'
    mov byte [rbp - 376], 'e'
    mov byte [rbp - 375], 'd'
    mov byte [rbp - 374], '_'
    mov byte [rbp - 373], 'c'
    mov byte [rbp - 372], 'o'
    mov byte [rbp - 371], 'n'
    mov byte [rbp - 370], 't'
    mov byte [rbp - 369], 'r'
    mov byte [rbp - 368], 'o'
    mov byte [rbp - 367], 'l'
    mov byte [rbp - 366], '_'
    mov byte [rbp - 365], 'f'
    mov byte [rbp - 364], 'l'
    mov byte [rbp - 363], 'o'
    mov byte [rbp - 362], 'w'
    mov byte [rbp - 361], ','
    mov byte [rbp - 360], ' '
    mov byte [rbp - 359], 'y'
    mov byte [rbp - 358], ' '
    mov byte [rbp - 357], 'V'
    mov byte [rbp - 356], 'a'
    mov byte [rbp - 355], 'l'
    mov byte [rbp - 354], 'u'
    mov byte [rbp - 353], 'e'
    mov byte [rbp - 352], ' '
    mov byte [rbp - 351], ':'
    mov byte [rbp - 350], ' '
    mov byte [rbp - 349], '%'
    mov byte [rbp - 348], 'd'
    mov byte [rbp - 347], 0x0A
    mov byte [rbp - 346], 0
    mov rdi, QWORD [rbp - 392]
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 400], rax
    mov rsi, QWORD [rbp - 400]
    mov QWORD [rbp - 408], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 408],rax
    jmp .L78
    .L81:
    lea rax, [rbp - 448]
    mov QWORD [rbp - 456], rax
    mov byte [rbp - 448], 'F'
    mov byte [rbp - 447], 'r'
    mov byte [rbp - 446], 'o'
    mov byte [rbp - 445], 'm'
    mov byte [rbp - 444], ' '
    mov byte [rbp - 443], 'm'
    mov byte [rbp - 442], 'i'
    mov byte [rbp - 441], 'x'
    mov byte [rbp - 440], 'e'
    mov byte [rbp - 439], 'd'
    mov byte [rbp - 438], '_'
    mov byte [rbp - 437], 'c'
    mov byte [rbp - 436], 'o'
    mov byte [rbp - 435], 'n'
    mov byte [rbp - 434], 't'
    mov byte [rbp - 433], 'r'
    mov byte [rbp - 432], 'o'
    mov byte [rbp - 431], 'l'
    mov byte [rbp - 430], '_'
    mov byte [rbp - 429], 'f'
    mov byte [rbp - 428], 'l'
    mov byte [rbp - 427], 'o'
    mov byte [rbp - 426], 'w'
    mov byte [rbp - 425], ','
    mov byte [rbp - 424], ' '
    mov byte [rbp - 423], 'y'
    mov byte [rbp - 422], ' '
    mov byte [rbp - 421], 'V'
    mov byte [rbp - 420], 'a'
    mov byte [rbp - 419], 'l'
    mov byte [rbp - 418], 'u'
    mov byte [rbp - 417], 'e'
    mov byte [rbp - 416], ' '
    mov byte [rbp - 415], ':'
    mov byte [rbp - 414], ' '
    mov byte [rbp - 413], '%'
    mov byte [rbp - 412], 'd'
    mov byte [rbp - 411], 0x0A
    mov byte [rbp - 410], 0
    mov rdi, QWORD [rbp - 456]
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 464], rax
    mov rsi, QWORD [rbp - 464]
    mov QWORD [rbp - 472], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 472],rax
    jmp .L78
    .L82:
    .L78:
    mov QWORD [rbp - 280], 0
    mov rax, [rbp - 224]
    dec rax
    mov [rbp - 280],rax
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 224], rax
    jmp .L75
    .L77:
    .L72:
    mov QWORD [rbp - 64], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 8], rax
    jmp .L68
    .L70:
    leave
    ret

while_if_switch:
    push rbp
    mov  rbp, rsp
    sub  rsp, 336
    mov QWORD [rbp - 8], 0
    .L83:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 4
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L84
    jmp .L85
    .L84:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 2
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cqo
    idiv rbx
    mov QWORD [rbp - 40],rdx
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L86
    lea rax, [rbp - 136]
    mov QWORD [rbp - 144], rax
    mov byte [rbp - 136], 'F'
    mov byte [rbp - 135], 'r'
    mov byte [rbp - 134], 'o'
    mov byte [rbp - 133], 'm'
    mov byte [rbp - 132], ' '
    mov byte [rbp - 131], 'w'
    mov byte [rbp - 130], 'h'
    mov byte [rbp - 129], 'i'
    mov byte [rbp - 128], 'l'
    mov byte [rbp - 127], 'e'
    mov byte [rbp - 126], '_'
    mov byte [rbp - 125], 'i'
    mov byte [rbp - 124], 'f'
    mov byte [rbp - 123], '_'
    mov byte [rbp - 122], 's'
    mov byte [rbp - 121], 'w'
    mov byte [rbp - 120], 'i'
    mov byte [rbp - 119], 't'
    mov byte [rbp - 118], 'c'
    mov byte [rbp - 117], 'h'
    mov byte [rbp - 116], ' '
    mov byte [rbp - 115], '<'
    mov byte [rbp - 114], 'e'
    mov byte [rbp - 113], 'l'
    mov byte [rbp - 112], 's'
    mov byte [rbp - 111], 'e'
    mov byte [rbp - 110], '>'
    mov byte [rbp - 109], ','
    mov byte [rbp - 108], ' '
    mov byte [rbp - 107], 'i'
    mov byte [rbp - 106], ' '
    mov byte [rbp - 105], 'V'
    mov byte [rbp - 104], 'a'
    mov byte [rbp - 103], 'l'
    mov byte [rbp - 102], 'u'
    mov byte [rbp - 101], 'e'
    mov byte [rbp - 100], ' '
    mov byte [rbp - 99], ':'
    mov byte [rbp - 98], ' '
    mov byte [rbp - 97], '%'
    mov byte [rbp - 96], 'd'
    mov byte [rbp - 95], 0x0A
    mov byte [rbp - 94], 0
    mov rdi, QWORD [rbp - 144]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 152], rax
    mov rsi, QWORD [rbp - 152]
    mov QWORD [rbp - 160], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 160],rax
    jmp .L87
    .L86:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 168], rax
    mov rax, QWORD [rbp - 168]
    cmp rax, 0
    je .L89
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 176], rax
    mov rax, QWORD [rbp - 176]
    cmp rax, 2
    je .L90
    jmp .L91
    .L89:
    lea rax, [rbp - 224]
    mov QWORD [rbp - 232], rax
    mov byte [rbp - 224], 'F'
    mov byte [rbp - 223], 'r'
    mov byte [rbp - 222], 'o'
    mov byte [rbp - 221], 'm'
    mov byte [rbp - 220], ' '
    mov byte [rbp - 219], 'w'
    mov byte [rbp - 218], 'h'
    mov byte [rbp - 217], 'i'
    mov byte [rbp - 216], 'l'
    mov byte [rbp - 215], 'e'
    mov byte [rbp - 214], '_'
    mov byte [rbp - 213], 'i'
    mov byte [rbp - 212], 'f'
    mov byte [rbp - 211], '_'
    mov byte [rbp - 210], 's'
    mov byte [rbp - 209], 'w'
    mov byte [rbp - 208], 'i'
    mov byte [rbp - 207], 't'
    mov byte [rbp - 206], 'c'
    mov byte [rbp - 205], 'h'
    mov byte [rbp - 204], ' '
    mov byte [rbp - 203], '<'
    mov byte [rbp - 202], 'i'
    mov byte [rbp - 201], 'f'
    mov byte [rbp - 200], '>'
    mov byte [rbp - 199], ','
    mov byte [rbp - 198], ' '
    mov byte [rbp - 197], 'i'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], 'V'
    mov byte [rbp - 194], 'a'
    mov byte [rbp - 193], 'l'
    mov byte [rbp - 192], 'u'
    mov byte [rbp - 191], 'e'
    mov byte [rbp - 190], ' '
    mov byte [rbp - 189], ':'
    mov byte [rbp - 188], ' '
    mov byte [rbp - 187], '%'
    mov byte [rbp - 186], 'd'
    mov byte [rbp - 185], 0x0A
    mov byte [rbp - 184], 0
    mov rdi, QWORD [rbp - 232]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 240], rax
    mov rsi, QWORD [rbp - 240]
    mov QWORD [rbp - 248], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 248],rax
    jmp .L88
    .L90:
    lea rax, [rbp - 296]
    mov QWORD [rbp - 304], rax
    mov byte [rbp - 296], 'F'
    mov byte [rbp - 295], 'r'
    mov byte [rbp - 294], 'o'
    mov byte [rbp - 293], 'm'
    mov byte [rbp - 292], ' '
    mov byte [rbp - 291], 'w'
    mov byte [rbp - 290], 'h'
    mov byte [rbp - 289], 'i'
    mov byte [rbp - 288], 'l'
    mov byte [rbp - 287], 'e'
    mov byte [rbp - 286], '_'
    mov byte [rbp - 285], 'i'
    mov byte [rbp - 284], 'f'
    mov byte [rbp - 283], '_'
    mov byte [rbp - 282], 's'
    mov byte [rbp - 281], 'w'
    mov byte [rbp - 280], 'i'
    mov byte [rbp - 279], 't'
    mov byte [rbp - 278], 'c'
    mov byte [rbp - 277], 'h'
    mov byte [rbp - 276], ' '
    mov byte [rbp - 275], '<'
    mov byte [rbp - 274], 'i'
    mov byte [rbp - 273], 'f'
    mov byte [rbp - 272], '>'
    mov byte [rbp - 271], ','
    mov byte [rbp - 270], ' '
    mov byte [rbp - 269], 'i'
    mov byte [rbp - 268], ' '
    mov byte [rbp - 267], 'V'
    mov byte [rbp - 266], 'a'
    mov byte [rbp - 265], 'l'
    mov byte [rbp - 264], 'u'
    mov byte [rbp - 263], 'e'
    mov byte [rbp - 262], ' '
    mov byte [rbp - 261], ':'
    mov byte [rbp - 260], ' '
    mov byte [rbp - 259], '%'
    mov byte [rbp - 258], 'd'
    mov byte [rbp - 257], 0x0A
    mov byte [rbp - 256], 0
    mov rdi, QWORD [rbp - 304]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 312], rax
    mov rsi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    jmp .L88
    .L91:
    .L88:
    .L87:
    mov QWORD [rbp - 88], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 8], rax
    jmp .L83
    .L85:
    leave
    ret

while_switch_if:
    push rbp
    mov  rbp, rsp
    sub  rsp, 416
    mov QWORD [rbp - 8], 1
    .L92:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L93
    jmp .L94
    .L93:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 1
    je .L96
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov rax, QWORD [rbp - 48]
    cmp rax, 2
    je .L97
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 56], rax
    mov rax, QWORD [rbp - 56]
    cmp rax, 3
    je .L98
    jmp .L99
    .L96:
    mov QWORD [rbp - 72], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 80], rax
    mov QWORD [rbp - 88], 0
    mov QWORD [rbp - 88], 2
    mov rax, QWORD [rbp - 80]
    mov rbx, QWORD [rbp - 88]
    cqo
    idiv rbx
    mov QWORD [rbp - 72],rdx
    mov QWORD [rbp - 96], 0
    mov QWORD [rbp - 104], 0
    mov rax, QWORD [rbp - 72]
    mov QWORD [rbp - 104], rax
    mov QWORD [rbp - 112], 0
    mov QWORD [rbp - 112], 1
    mov rax, QWORD [rbp - 104]
    mov rbx, QWORD [rbp - 112]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 96], rax
    mov rax, QWORD [rbp - 96]
    cmp rax, 0
    jne .L100
    jmp .L101
    .L100:
    lea rax, [rbp - 248]
    mov QWORD [rbp - 256], rax
    mov byte [rbp - 248], 'F'
    mov byte [rbp - 247], 'r'
    mov byte [rbp - 246], 'o'
    mov byte [rbp - 245], 'm'
    mov byte [rbp - 244], ' '
    mov byte [rbp - 243], 'w'
    mov byte [rbp - 242], 'h'
    mov byte [rbp - 241], 'i'
    mov byte [rbp - 240], 'l'
    mov byte [rbp - 239], 'e'
    mov byte [rbp - 238], '_'
    mov byte [rbp - 237], 's'
    mov byte [rbp - 236], 'w'
    mov byte [rbp - 235], 'i'
    mov byte [rbp - 234], 't'
    mov byte [rbp - 233], 'c'
    mov byte [rbp - 232], 'h'
    mov byte [rbp - 231], '_'
    mov byte [rbp - 230], 'i'
    mov byte [rbp - 229], 'f'
    mov byte [rbp - 228], ','
    mov byte [rbp - 227], ' '
    mov byte [rbp - 226], 'i'
    mov byte [rbp - 225], ' '
    mov byte [rbp - 224], 'V'
    mov byte [rbp - 223], 'a'
    mov byte [rbp - 222], 'l'
    mov byte [rbp - 221], 'u'
    mov byte [rbp - 220], 'e'
    mov byte [rbp - 219], ' '
    mov byte [rbp - 218], ':'
    mov byte [rbp - 217], ' '
    mov byte [rbp - 216], '%'
    mov byte [rbp - 215], 'd'
    mov byte [rbp - 214], 0x0A
    mov byte [rbp - 213], 0
    mov rdi, QWORD [rbp - 256]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 264], rax
    mov rsi, QWORD [rbp - 264]
    mov QWORD [rbp - 272], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 272],rax
    .L101:
    jmp .L95
    .L97:
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 128], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 128], rax
    mov QWORD [rbp - 136], 0
    mov QWORD [rbp - 136], 2
    mov rax, QWORD [rbp - 128]
    mov rbx, QWORD [rbp - 136]
    imul rax,rbx
    mov QWORD [rbp - 120], rax
    mov QWORD [rbp - 144], 0
    mov QWORD [rbp - 152], 0
    mov rax, QWORD [rbp - 120]
    mov QWORD [rbp - 152], rax
    mov QWORD [rbp - 160], 0
    mov QWORD [rbp - 160], 4
    mov rax, QWORD [rbp - 152]
    mov rbx, QWORD [rbp - 160]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 144], rax
    mov rax, QWORD [rbp - 144]
    cmp rax, 0
    jne .L102
    jmp .L103
    .L102:
    lea rax, [rbp - 312]
    mov QWORD [rbp - 320], rax
    mov byte [rbp - 312], 'F'
    mov byte [rbp - 311], 'r'
    mov byte [rbp - 310], 'o'
    mov byte [rbp - 309], 'm'
    mov byte [rbp - 308], ' '
    mov byte [rbp - 307], 'w'
    mov byte [rbp - 306], 'h'
    mov byte [rbp - 305], 'i'
    mov byte [rbp - 304], 'l'
    mov byte [rbp - 303], 'e'
    mov byte [rbp - 302], '_'
    mov byte [rbp - 301], 's'
    mov byte [rbp - 300], 'w'
    mov byte [rbp - 299], 'i'
    mov byte [rbp - 298], 't'
    mov byte [rbp - 297], 'c'
    mov byte [rbp - 296], 'h'
    mov byte [rbp - 295], '_'
    mov byte [rbp - 294], 'i'
    mov byte [rbp - 293], 'f'
    mov byte [rbp - 292], ','
    mov byte [rbp - 291], ' '
    mov byte [rbp - 290], 'i'
    mov byte [rbp - 289], ' '
    mov byte [rbp - 288], 'V'
    mov byte [rbp - 287], 'a'
    mov byte [rbp - 286], 'l'
    mov byte [rbp - 285], 'u'
    mov byte [rbp - 284], 'e'
    mov byte [rbp - 283], ' '
    mov byte [rbp - 282], ':'
    mov byte [rbp - 281], ' '
    mov byte [rbp - 280], '%'
    mov byte [rbp - 279], 'd'
    mov byte [rbp - 278], 0x0A
    mov byte [rbp - 277], 0
    mov rdi, QWORD [rbp - 320]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 328], rax
    mov rsi, QWORD [rbp - 328]
    mov QWORD [rbp - 336], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 336],rax
    .L103:
    jmp .L95
    .L98:
    mov QWORD [rbp - 168], 0
    mov QWORD [rbp - 176], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 176], rax
    mov QWORD [rbp - 184], 0
    mov QWORD [rbp - 184], 1
    mov rax, QWORD [rbp - 176]
    mov rbx, QWORD [rbp - 184]
    sub rax,rbx
    mov QWORD [rbp - 168], rax
    mov QWORD [rbp - 192], 0
    mov QWORD [rbp - 200], 0
    mov rax, QWORD [rbp - 168]
    mov QWORD [rbp - 200], rax
    mov QWORD [rbp - 208], 0
    mov QWORD [rbp - 208], 0
    mov rax, QWORD [rbp - 200]
    mov rbx, QWORD [rbp - 208]
    cmp rax,rbx
    setg al
    movzx rax,al
    mov QWORD [rbp - 192], rax
    mov rax, QWORD [rbp - 192]
    cmp rax, 0
    jne .L104
    jmp .L105
    .L104:
    lea rax, [rbp - 376]
    mov QWORD [rbp - 384], rax
    mov byte [rbp - 376], 'F'
    mov byte [rbp - 375], 'r'
    mov byte [rbp - 374], 'o'
    mov byte [rbp - 373], 'm'
    mov byte [rbp - 372], ' '
    mov byte [rbp - 371], 'w'
    mov byte [rbp - 370], 'h'
    mov byte [rbp - 369], 'i'
    mov byte [rbp - 368], 'l'
    mov byte [rbp - 367], 'e'
    mov byte [rbp - 366], '_'
    mov byte [rbp - 365], 's'
    mov byte [rbp - 364], 'w'
    mov byte [rbp - 363], 'i'
    mov byte [rbp - 362], 't'
    mov byte [rbp - 361], 'c'
    mov byte [rbp - 360], 'h'
    mov byte [rbp - 359], '_'
    mov byte [rbp - 358], 'i'
    mov byte [rbp - 357], 'f'
    mov byte [rbp - 356], ','
    mov byte [rbp - 355], ' '
    mov byte [rbp - 354], 'i'
    mov byte [rbp - 353], ' '
    mov byte [rbp - 352], 'V'
    mov byte [rbp - 351], 'a'
    mov byte [rbp - 350], 'l'
    mov byte [rbp - 349], 'u'
    mov byte [rbp - 348], 'e'
    mov byte [rbp - 347], ' '
    mov byte [rbp - 346], ':'
    mov byte [rbp - 345], ' '
    mov byte [rbp - 344], '%'
    mov byte [rbp - 343], 'd'
    mov byte [rbp - 342], 0x0A
    mov byte [rbp - 341], 0
    mov rdi, QWORD [rbp - 384]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 392], rax
    mov rsi, QWORD [rbp - 392]
    mov QWORD [rbp - 400], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 400],rax
    .L105:
    jmp .L95
    .L99:
    .L95:
    mov QWORD [rbp - 64], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 8], rax
    jmp .L92
    .L94:
    leave
    ret

while_if_while_switch:
    push rbp
    mov  rbp, rsp
    sub  rsp, 384
    mov QWORD [rbp - 8], 1
    .L106:
    mov QWORD [rbp - 16], 0
    mov QWORD [rbp - 24], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 24], rax
    mov QWORD [rbp - 32], 0
    mov QWORD [rbp - 32], 3
    mov rax, QWORD [rbp - 24]
    mov rbx, QWORD [rbp - 32]
    cmp rax,rbx
    setle al
    movzx rax,al
    mov QWORD [rbp - 16], rax
    mov rax, QWORD [rbp - 16]
    cmp rax, 0
    jne .L107
    jmp .L108
    .L107:
    mov QWORD [rbp - 40], 0
    mov QWORD [rbp - 48], 0
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 48], rax
    mov QWORD [rbp - 56], 0
    mov QWORD [rbp - 56], 2
    mov rax, QWORD [rbp - 48]
    mov rbx, QWORD [rbp - 56]
    cqo
    idiv rbx
    mov QWORD [rbp - 40],rdx
    mov QWORD [rbp - 64], 0
    mov QWORD [rbp - 72], 0
    mov rax, QWORD [rbp - 40]
    mov QWORD [rbp - 72], rax
    mov QWORD [rbp - 80], 0
    mov QWORD [rbp - 80], 0
    mov rax, QWORD [rbp - 72]
    mov rbx, QWORD [rbp - 80]
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 64], rax
    mov rax, QWORD [rbp - 64]
    cmp rax, 0
    jne .L109
    mov QWORD [rbp - 96], 0
    .L111:
    mov QWORD [rbp - 104], 0
    mov QWORD [rbp - 112], 0
    mov rax, QWORD [rbp - 96]
    mov QWORD [rbp - 112], rax
    mov QWORD [rbp - 120], 0
    mov QWORD [rbp - 120], 1
    mov rax, QWORD [rbp - 112]
    mov rbx, QWORD [rbp - 120]
    cmp rax,rbx
    setl al
    movzx rax,al
    mov QWORD [rbp - 104], rax
    mov rax, QWORD [rbp - 104]
    cmp rax, 0
    jne .L112
    jmp .L113
    .L112:
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 128], rax
    mov rax, QWORD [rbp - 128]
    cmp rax, 1
    je .L115
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 136], rax
    mov rax, QWORD [rbp - 136]
    cmp rax, 3
    je .L116
    jmp .L117
    .L115:
    lea rax, [rbp - 200]
    mov QWORD [rbp - 208], rax
    mov byte [rbp - 200], 'F'
    mov byte [rbp - 199], 'r'
    mov byte [rbp - 198], 'o'
    mov byte [rbp - 197], 'm'
    mov byte [rbp - 196], ' '
    mov byte [rbp - 195], 'w'
    mov byte [rbp - 194], 'h'
    mov byte [rbp - 193], 'i'
    mov byte [rbp - 192], 'l'
    mov byte [rbp - 191], 'e'
    mov byte [rbp - 190], '_'
    mov byte [rbp - 189], 'i'
    mov byte [rbp - 188], 'f'
    mov byte [rbp - 187], '_'
    mov byte [rbp - 186], 'w'
    mov byte [rbp - 185], 'h'
    mov byte [rbp - 184], 'i'
    mov byte [rbp - 183], 'l'
    mov byte [rbp - 182], 'e'
    mov byte [rbp - 181], '_'
    mov byte [rbp - 180], 's'
    mov byte [rbp - 179], 'w'
    mov byte [rbp - 178], 'i'
    mov byte [rbp - 177], 't'
    mov byte [rbp - 176], 'c'
    mov byte [rbp - 175], 'h'
    mov byte [rbp - 174], ' '
    mov byte [rbp - 173], '<'
    mov byte [rbp - 172], 'e'
    mov byte [rbp - 171], 'l'
    mov byte [rbp - 170], 's'
    mov byte [rbp - 169], 'e'
    mov byte [rbp - 168], '>'
    mov byte [rbp - 167], ','
    mov byte [rbp - 166], ' '
    mov byte [rbp - 165], 'i'
    mov byte [rbp - 164], ' '
    mov byte [rbp - 163], 'V'
    mov byte [rbp - 162], 'a'
    mov byte [rbp - 161], 'l'
    mov byte [rbp - 160], 'u'
    mov byte [rbp - 159], 'e'
    mov byte [rbp - 158], ' '
    mov byte [rbp - 157], ':'
    mov byte [rbp - 156], ' '
    mov byte [rbp - 155], '%'
    mov byte [rbp - 154], 'd'
    mov byte [rbp - 153], 0x0A
    mov byte [rbp - 152], 0
    mov rdi, QWORD [rbp - 208]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 216], rax
    mov rsi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 224],rax
    jmp .L114
    .L116:
    lea rax, [rbp - 280]
    mov QWORD [rbp - 288], rax
    mov byte [rbp - 280], 'F'
    mov byte [rbp - 279], 'r'
    mov byte [rbp - 278], 'o'
    mov byte [rbp - 277], 'm'
    mov byte [rbp - 276], ' '
    mov byte [rbp - 275], 'w'
    mov byte [rbp - 274], 'h'
    mov byte [rbp - 273], 'i'
    mov byte [rbp - 272], 'l'
    mov byte [rbp - 271], 'e'
    mov byte [rbp - 270], '_'
    mov byte [rbp - 269], 'i'
    mov byte [rbp - 268], 'f'
    mov byte [rbp - 267], '_'
    mov byte [rbp - 266], 'w'
    mov byte [rbp - 265], 'h'
    mov byte [rbp - 264], 'i'
    mov byte [rbp - 263], 'l'
    mov byte [rbp - 262], 'e'
    mov byte [rbp - 261], '_'
    mov byte [rbp - 260], 's'
    mov byte [rbp - 259], 'w'
    mov byte [rbp - 258], 'i'
    mov byte [rbp - 257], 't'
    mov byte [rbp - 256], 'c'
    mov byte [rbp - 255], 'h'
    mov byte [rbp - 254], ' '
    mov byte [rbp - 253], '<'
    mov byte [rbp - 252], 'e'
    mov byte [rbp - 251], 'l'
    mov byte [rbp - 250], 's'
    mov byte [rbp - 249], 'e'
    mov byte [rbp - 248], '>'
    mov byte [rbp - 247], ','
    mov byte [rbp - 246], ' '
    mov byte [rbp - 245], 'i'
    mov byte [rbp - 244], ' '
    mov byte [rbp - 243], 'V'
    mov byte [rbp - 242], 'a'
    mov byte [rbp - 241], 'l'
    mov byte [rbp - 240], 'u'
    mov byte [rbp - 239], 'e'
    mov byte [rbp - 238], ' '
    mov byte [rbp - 237], ':'
    mov byte [rbp - 236], ' '
    mov byte [rbp - 235], '%'
    mov byte [rbp - 234], 'd'
    mov byte [rbp - 233], 0x0A
    mov byte [rbp - 232], 0
    mov rdi, QWORD [rbp - 288]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 296], rax
    mov rsi, QWORD [rbp - 296]
    mov QWORD [rbp - 304], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 304],rax
    jmp .L114
    .L117:
    .L114:
    mov QWORD [rbp - 144], 0
    mov rax, [rbp - 96]
    inc rax
    mov [rbp - 144],rax
    mov rax, QWORD [rbp - 144]
    mov QWORD [rbp - 96], rax
    jmp .L111
    .L113:
    jmp .L110
    .L109:
    lea rax, [rbp - 352]
    mov QWORD [rbp - 360], rax
    mov byte [rbp - 352], 'F'
    mov byte [rbp - 351], 'r'
    mov byte [rbp - 350], 'o'
    mov byte [rbp - 349], 'm'
    mov byte [rbp - 348], ' '
    mov byte [rbp - 347], 'w'
    mov byte [rbp - 346], 'h'
    mov byte [rbp - 345], 'i'
    mov byte [rbp - 344], 'l'
    mov byte [rbp - 343], 'e'
    mov byte [rbp - 342], '_'
    mov byte [rbp - 341], 'i'
    mov byte [rbp - 340], 'f'
    mov byte [rbp - 339], '_'
    mov byte [rbp - 338], 'w'
    mov byte [rbp - 337], 'h'
    mov byte [rbp - 336], 'i'
    mov byte [rbp - 335], 'l'
    mov byte [rbp - 334], 'e'
    mov byte [rbp - 333], '_'
    mov byte [rbp - 332], 's'
    mov byte [rbp - 331], 'w'
    mov byte [rbp - 330], 'i'
    mov byte [rbp - 329], 't'
    mov byte [rbp - 328], 'c'
    mov byte [rbp - 327], 'h'
    mov byte [rbp - 326], ' '
    mov byte [rbp - 325], '<'
    mov byte [rbp - 324], 'i'
    mov byte [rbp - 323], 'f'
    mov byte [rbp - 322], '>'
    mov byte [rbp - 321], ','
    mov byte [rbp - 320], ' '
    mov byte [rbp - 319], 'i'
    mov byte [rbp - 318], ' '
    mov byte [rbp - 317], 'V'
    mov byte [rbp - 316], 'a'
    mov byte [rbp - 315], 'l'
    mov byte [rbp - 314], 'u'
    mov byte [rbp - 313], 'e'
    mov byte [rbp - 312], ' '
    mov byte [rbp - 311], ':'
    mov byte [rbp - 310], ' '
    mov byte [rbp - 309], '%'
    mov byte [rbp - 308], 'd'
    mov byte [rbp - 307], 0x0A
    mov byte [rbp - 306], 0
    mov rdi, QWORD [rbp - 360]
    mov rax, QWORD [rbp - 8]
    mov QWORD [rbp - 368], rax
    mov rsi, QWORD [rbp - 368]
    mov QWORD [rbp - 376], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 376],rax
    .L110:
    mov QWORD [rbp - 88], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 88],rax
    mov rax, QWORD [rbp - 88]
    mov QWORD [rbp - 8], rax
    jmp .L106
    .L108:
    leave
    ret

print_control_flow:
    push rbp
    mov  rbp, rsp
    sub  rsp, 336
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call deep_nesting
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
    mov QWORD [rbp - 40], 0
    xor rax,rax
    call while_if_while
    mov QWORD [rbp - 40],rax
    lea rax, [rbp - 48]
    mov QWORD [rbp - 56], rax
    mov byte [rbp - 48], 0x0A
    mov byte [rbp - 47], 0
    mov rdi, QWORD [rbp - 56]
    mov QWORD [rbp - 64], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 64],rax
    mov QWORD [rbp - 72], 0
    xor rax,rax
    call if_in_switch
    mov QWORD [rbp - 72],rax
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
    xor rax,rax
    call switch_in_if
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
    mov QWORD [rbp - 136], 0
    xor rax,rax
    call reuse_loop_counters
    mov QWORD [rbp - 136],rax
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
    xor rax,rax
    call recursively_growing_blocks
    mov QWORD [rbp - 168],rax
    lea rax, [rbp - 176]
    mov QWORD [rbp - 184], rax
    mov byte [rbp - 176], 0x0A
    mov byte [rbp - 175], 0
    mov rdi, QWORD [rbp - 184]
    mov QWORD [rbp - 192], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 192],rax
    mov QWORD [rbp - 200], 0
    xor rax,rax
    call mixed_control_flow
    mov QWORD [rbp - 200],rax
    lea rax, [rbp - 208]
    mov QWORD [rbp - 216], rax
    mov byte [rbp - 208], 0x0A
    mov byte [rbp - 207], 0
    mov rdi, QWORD [rbp - 216]
    mov QWORD [rbp - 224], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 224],rax
    mov QWORD [rbp - 232], 0
    xor rax,rax
    call while_if_switch
    mov QWORD [rbp - 232],rax
    lea rax, [rbp - 240]
    mov QWORD [rbp - 248], rax
    mov byte [rbp - 240], 0x0A
    mov byte [rbp - 239], 0
    mov rdi, QWORD [rbp - 248]
    mov QWORD [rbp - 256], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 256],rax
    mov QWORD [rbp - 264], 0
    xor rax,rax
    call while_switch_if
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
    mov QWORD [rbp - 296], 0
    xor rax,rax
    call while_if_while_switch
    mov QWORD [rbp - 296],rax
    lea rax, [rbp - 304]
    mov QWORD [rbp - 312], rax
    mov byte [rbp - 304], 0x0A
    mov byte [rbp - 303], 0
    mov rdi, QWORD [rbp - 312]
    mov QWORD [rbp - 320], 0
    xor rax,rax
    call printf
    mov QWORD [rbp - 320],rax
    leave
    ret

main:
    push rbp
    mov  rbp, rsp
    sub  rsp, 16
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call print_control_flow
    mov QWORD [rbp - 8],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

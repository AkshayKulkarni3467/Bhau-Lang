SECTION .data

SECTION .bss

SECTION .text
global  main
extern printf
mixed_control_flow:
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
    cmp rax,rbx
    sete al
    movzx rax,al
    mov QWORD [rbp - 40], rax
    mov rax, QWORD [rbp - 40]
    cmp rax, 0
    jne .L3
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
    jne .L5
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
    jmp .L6
    .L5:
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
    .L6:
    jmp .L4
    .L3:
    mov QWORD [rbp - 224], 3
    .L7:
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
    jne .L8
    jmp .L9
    .L8:
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 256], rax
    mov rax, QWORD [rbp - 256]
    cmp rax, 1
    je .L11
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 264], rax
    mov rax, QWORD [rbp - 264]
    cmp rax, 2
    je .L12
    mov rax, QWORD [rbp - 224]
    mov QWORD [rbp - 272], rax
    mov rax, QWORD [rbp - 272]
    cmp rax, 3
    je .L13
    jmp .L14
    .L11:
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
    jmp .L10
    .L12:
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
    jmp .L10
    .L13:
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
    jmp .L10
    .L14:
    .L10:
    mov QWORD [rbp - 280], 0
    mov rax, [rbp - 224]
    dec rax
    mov [rbp - 280],rax
    mov rax, QWORD [rbp - 280]
    mov QWORD [rbp - 224], rax
    jmp .L7
    .L9:
    .L4:
    mov QWORD [rbp - 64], 0
    mov rax, [rbp - 8]
    inc rax
    mov [rbp - 64],rax
    mov rax, QWORD [rbp - 64]
    mov QWORD [rbp - 8], rax
    jmp .L0
    .L2:
    leave
    ret

print_control_flow:
    push rbp
    mov  rbp, rsp
    sub  rsp, 48
    mov QWORD [rbp - 8], 0
    xor rax,rax
    call mixed_control_flow
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
    call print_control_flow
    mov QWORD [rbp - 8],rax

    xor rax, rax
    leave
    ret

SECTION .note.GNU-stack

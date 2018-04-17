;程序源代码(myos.asm)
org 7c00h           ;BIOS把引导扇区加载到0:7c00h处，并开始执行
OffSetOfUserPrg1 equ 8100h

Start:
    ; 初始化段寄存器
    mov ax, cs                  ; 置其他段寄存器值与CS相同
    mov ds, ax                  ; 数据段

    ; 清空屏幕
    mov ax, 0003h  
    int 10h    
    
    mov bp, Message             ; bp=串偏移地址
    mov ax, ds                  ; es = ds
    mov es, ax          
    mov cx, MessageLength       ; cx = 串长 
    mov ax, 1301h               ; 功能和光标位置
    mov bx, 0007h               ; 页号和黑底白字
    mov dx, 0000h               ; 行号和列号
    int 10h

Input:
    ; 阻塞等待输入
    mov ah, 0                   ; 输入
    int 16h                     ; 16号中断

    ; 检查是否在1~3之间，不是则重新输入
    mov ah, 0
    cmp ax, '0'                 ; <= 0 重新输入
    jbe Input
    cmp ax, '3'                 ; >3 重新输入
    ja Input

    sub ax, '0'         
    add ax, 1
    mov cl, al                  ; 获取要读取的扇区号

LoadnEx:
    ; 读取软盘内容到内存的ES:BX处
    mov ax, cs                  ; 段地址，存放数据的内存基地址
    mov es, ax                  ; 设置段地址
    mov bx, OffSetOfUserPrg1    ; 存放数据的内存偏移地址
    mov ah, 2                   ; 功能号
    mov al, 3                   ; 读取3个扇区
    mov ch, 0                   ; 柱面号
    ; mov cl, 4                   ; 起始扇区号，起始编号为1
    mov dh, 0                   ; 磁头号0
    mov dl, 0                   ; 驱动器号，0光驱
    int 13h

    jmp OffSetOfUserPrg1

AfterRun:
    jmp $

Message:
    db 'MyOS is running...', 0ah, 0dh, '1->Hello | 2-> ReadInt | 3-> Triangle', 0ah, 0dh, '>>> '
MessageLength equ ($-Message)
    times 510-($-$$) db 0
    db 0x55, 0xaa
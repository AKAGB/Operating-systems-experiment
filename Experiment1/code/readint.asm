; 功能：读取一个整数并输出相应个数的*号
org 8100h           
Start:
    mov ax, cs          ; 初始化段寄存器
    mov ds, ax          ; 数据段

    ; 清空屏幕
    mov ah, 0           
    mov al, 03h         ; 80x25 彩色方式
    int 10h             ; 10号中断

    ; 显示初始信息
    mov ax, cs          
    mov es, ax          ; ES=CS
    mov bp, Message     ; ES:BP为字符串地址
    mov ax, 1301h       ; 显示字符串，光标跟随移动
    mov bx, 0007
    mov cx, MessageLength   ;串长
    mov dx, 0           ; 行号列号均为0
    int 10h

Input:
    ; 读取一个1-9的整数，不在范围内的均重新输入
    mov ah, 0
    int 16h

    ; 检查输入
    mov ah, 0
    cmp ax, '0'
    jbe Input
    cmp ax, '9'
    ja Input
    
    push ax
    ;在光标位置显示输入数字
    mov ah,0eh ;0eh号调用
    mov bl,07h ;白底黑字
    int 10h ;屏幕中断
    ;换行与回车
    mov ah,0eh ;0eh号调用
    mov al,0ah ;显示换行
    int 10h ;屏幕中断
    mov al,0dh ;显示回车
    int 10h ;屏幕中断

    pop ax
    mov ah, 0
    sub ax, '0'
    push ax

loop1:
    mov ah, 0eh                 ; 输出字符
    mov al, '*'
    mov bl, 07h
    int 10h
    pop ax
    sub ax, 1
    push ax
    cmp ax, 0
    ja loop1
    mov ah,0eh 
    mov al,0ah 
    int 10h 
    mov al,0dh 
    int 10h 

Return:
    ; 输出返回提示信息
    mov bp, ReturnMsg           ; ES:BP为字符串地址
    mov ax, 1301h               ; 显示字符串，光标跟随移动
    mov bx, 0007
    mov cx, ReturnMsgLength     ;串长
    mov dx, 0200h               ; 行号=2 列号=0
    int 10h

ReadESC:
    ; 读取esc
    mov ah, 0
    int 16h

    ; 检查输入
    mov ah, 0
    cmp ax, 1bh
    jne ReadESC

    ; 返回第0扇区
    mov ax, ZeroSector
    jmp ax

Message:
    db 'Please input a number(1 to 9): '
MessageLength equ ($-Message)

ReturnMsg:
    db 'Enter esc to return.'
ReturnMsgLength equ ($-ReturnMsg)

ZeroSector equ 7c00h
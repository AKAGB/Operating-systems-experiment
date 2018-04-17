org  8100h
main:

;初始化段寄存器
mov	ax, cs	       ; 置其他段寄存器值与CS相同
mov	ds, ax	       ; 数据段
mov	ax, ds		 ; ES:BP = 串地址
mov	es, ax		 ; 置ES=DS

mov ax, 0003h
int 10h

mov	bp, Message		 ; BP=当前串的偏移地址
mov	ax, ds		 ; ES:BP = 串地址
mov	es, ax		 ; 置ES=DS
mov	cx, MessageLength  ; CX = 串长（=9）
mov	ax, 1301h		 ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
mov	bx, 0007h		 ; 页号为0(BH = 0) 黑底白字(BL = 07h)
mov dh, 0		       ; 行号=0
mov	dl, 0			 ; 列号=0
int	10h			 ; BIOS的10h功能：显示一行字符

Input:
;读入键盘输入
;ah = 0, int 16h:阻塞式读取键盘输入
mov ah,0 ;　　 0号调用
int 16h ;　　　 输入字串

;键盘输入的返回结果在AL
mov ah,0
cmp ax, 1bh
je LoadBoot
cmp ax,'0' ;和'0'比较
jbe Input
cmp ax,'9' ;和'9'比较
ja Input


;下面要把输入的数字显示出来，先把ax的内容存起来
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

;显示完输入数字，重新取回ax
pop ax

sub ax,'0' ;减去'0'
push ax
push ax

cmp ax,0
jbe Escape

loop1:
;在光标位置显示*
mov ah,0eh ;0eh号调用
mov al,'*' ;显示*
mov bl,07h ;白底黑字
int 10h ;屏幕中断

;循环变量减一
pop ax
sub ax,1
push ax

;当循环变量大于0时继续循环
cmp ax,0
ja loop1
pop ax

;换行与回车
mov ah,0eh ;0eh号调用
mov al,0ah ;显示换行
int 10h ;屏幕中断
mov al,0dh ;显示回车
int 10h ;屏幕中断

;循环变量减一
pop ax
sub ax,1
push ax
push ax

;当循环变量大于0时继续循环
cmp ax,0
ja loop1

Escape:
    mov ah, 0               ; 阻塞输入
    int 16h
    mov ah, 0                ; 检查输入是否为esc，不是则继续等待输入
    cmp ax, 1bh
    jne Escape

LoadBoot:
    ; 返回第0扇区
    mov ax, ZeroSector
    jmp ax

Message:
      db 'Input a Number(esc to return): ', 0ah, 0dh
MessageLength equ ($-Message)

ZeroSector equ 7c00h
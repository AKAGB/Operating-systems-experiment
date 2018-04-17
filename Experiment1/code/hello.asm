;程序源代码（hello.asm）
org  8100h		
Start:
    ; 初始化段寄存器
	mov	ax, cs	       ; 置其他段寄存器值与CS相同
	mov	ds, ax	       ; 数据段

    ; 清空屏幕
    mov ax, 0003h  
    int 10h    
	
    mov	bp, Message		    ; BP=当前串的偏移地址
	mov	ax, ds		        ; ES:BP = 串地址
	mov	es, ax		        ; 置ES=DS
	mov	cx, MessageLength   ; CX = 串长（=9）
	mov	ax, 1301h		    ; AH = 13h（功能号）、AL = 01h（光标置于串尾）
	mov	bx, 0007h		    ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov dh, 0		        ; 行号=0
	mov	dl, 0			    ; 列号=0
	int	10h			        ; BIOS的10h功能：显示一行字符

Escape:
    mov ah, 0               ; 阻塞输入
    int 16h
    mov ah, 0                ; 检查输入是否为esc，不是则继续等待输入
    cmp ax, 1bh
    jne Escape

    ; 返回第0扇区
    mov ax, ZeroSector
    jmp ax

Message:
      db 'Hello, world.', 0ah, 0dh, 'Enter esc to return.'
MessageLength equ ($-Message)

ZeroSector equ 7c00h
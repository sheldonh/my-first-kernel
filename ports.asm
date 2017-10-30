bits 32

section .text

global rport
global wport

rport:
	mov edx, [esp + 4]
	in al, dx
	ret

wport:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

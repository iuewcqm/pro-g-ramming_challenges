%include "misc.asm"

section .data
fizz:	db "Fizz", 0x0
buzz:	db "Buzz", 0x0

section .text
	global _start

_start:
	pop esi
	mov esi, 0
	mov edi, 0
	mov ecx, 0

next_number:
	inc ecx

.check_fizz:
	mov edx, 0
	mov eax, ecx
	mov ebx, 3
	div ebx
	mov edi, edx
	cmp edi, 0
	jne .check_buzz
	mov eax, fizz
	call sprint

.check_buzz:
	mov edx, 0
	mov eax, ecx
	mov ebx, 5
	div ebx
	mov esi, edx
	cmp esi, 0
	jne .check_int
	mov eax, buzz
	call sprint

.check_int:
	cmp edi, 0
	je .continue
	cmp esi, 0
	je .continue
	mov eax, ecx
	call iprint

.continue:
	mov eax, 0xA
	push eax
	mov eax, esp
	call sprint
	pop eax
	cmp ecx, r8d
	jne next_number

	mov eax, 1
	mov ebx, 0
	int 128

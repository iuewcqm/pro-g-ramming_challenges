iprint:
	push eax
	push ecx
	push edx
	push esi
	mov ecx, 0

.divideloop:
	inc ecx
	mov edx, 0
	mov esi, 10
	idiv esi
	add edx, 48
	push edx
	cmp eax, 0
	jnz .divideloop

.printloop:
	dec ecx
	mov eax, esp
	call sprint
	pop eax
	cmp ecx, 0
	jnz .printloop

	pop esi
	pop edx
	pop ecx
	pop eax
	ret


strlen:
	push ebx
	mov ebx, eax

.nextchar:	
	cmp byte[eax], 0
	jz .finished
	inc eax
	jmp .nextchar

.finished:
	sub eax, ebx
	pop ebx
	ret


sprint:
	push edx
	push ecx
	push ebx
	push eax

	call strlen

	mov edx, eax
	pop eax

	mov ecx, eax

	mov eax, 4
	mov ebx, 1
	int 0x80

	pop ebx
	pop ecx
	pop edx
	ret

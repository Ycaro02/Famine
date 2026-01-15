BITS 32

; Macro to save and restore registers
%include "include/asm/32bits_macro.s"

section .text
	global decrypt_data_32

decrypt_data_32:
	save_registers

	call	_get_eip		; Get the current address

	; Here 42424242 and 42 are placeholders, the real values are set when we inject the payload
	; 42424242 is the offset to sub to the current instruction pointer to get start of text section

	sub 	edi, 0x42424242	; need to sub the data ptr set by the main
	mov		esi, 0x42		; data_len
	mov		ecx, 0x42		; key_len

	;;; SAVE KEY_LEN AND INJECT BOOL HERE
	push 	ecx				; push the key_len to save it on the stack
	push	0x0				; push the boolean to check if we need to execute the command

	; Get the current address + 5 cause the call instruction is 5 bytes long
	; 1 byte for the call instruction and 4 bytes for his argument
	call	$ + 0x5			; Get the current address + 5 cause the call instruction is 5 bytes long
	pop		edx				; Get back the address of the message push by the call instruction
	;; HARDCODED LEN HERE
	add		edx, 0x108 		; need to add the offset of the key label 0x60 (96) 

_decrypt_data_start:
	xor		ebx, ebx				; data_idx = 0
	xor		eax, eax				; key_idx

_decrypt_char:
	cmp		ebx, esi				; if data_idx >= data_len
	jge		_end_decrypt_data
	
	push	esi						; save data_len
	movzx	esi, byte [edx + eax]	; esi = key[key_idx]
	push	eax						; save key_idx
	movzx	eax, byte [edi + ebx]	; rax = data[data_idx]
	xor		eax, esi				; data[data_idx] ^ key[key_idx]
	mov 	byte [edi + ebx], al	; data[data_idx] = data[data_idx] ^ key[key_idx]
	
	pop		eax						; restore key_idx
	pop		esi						; restore data_len
	
	inc		ebx						; i++
	inc		eax						; key_idx++
	cmp		eax, ecx				; if key_idx >= key_len
	jge		_reset_key_idx
	jmp		_decrypt_char

_reset_key_idx:
	xor		eax, eax				; key_idx = 0
	jmp		_decrypt_char

_end_decrypt_data:
	mov		eax, 0x4	; write
	mov		ebx, 0x1	; fd 1
	mov		edx, 0xe	; len of woody
	call	$ + 0x5
	pop		ecx			; Get back the address of the message push by the call instruction

	;; HARDCODED LEN HERE
	add		ecx, 0xBA	; ecx + 0x25 (37) to get the real message addr
	int		0x80		; exec syscall, interrupt 0x80

	;;; RESTORE BOOL AND KEYLEN HERE
	pop		eax			; get back the injected int
	
	cmp 	eax, 0x1		; cmp injected int with 1 (CMD_EXEC)
	je		_exec_label
	cmp		eax, 0x2		; cmp injected int with 2 (CMD_CUSTOM_MSG)
	je		_print_custom_msg
	jmp		_restore_starting_point		; else just restore the starting point

_exec_label:
	; 1. Create a new process with fork
	mov     eax, 0x2                	; fork syscall number
	int     0x80
	test	eax, eax               		; test if rax is 0 (child process) or not (parent process)
	jnz		_parent_process				; else just to the parent process code


_child_process:
	; 2. Execute a command in the child process
	; build argv
	; lea		ebx, [rel path_sh]		; ebx = argv
	pop 	edx ; get back the key len
	push	edx ; push the key len to restore the stack


	push	ebp
	mov		ebp, esp
	sub		esp, 0x60


	call 	$ + 0x5
	pop		eax								; Get back the address of the message push by the call instruction
	add		eax, 0x3D						; 26
	mov 	ebx, eax

	lea 	ecx, [esp+0x30]					; ecx = arg1
	mov		[ecx], ebx						; argv[0] = path_sh

	call 	$ + 0x5
	pop		eax								; Get back the address of the message push by the call instruction
	add  	eax, 0x34						; Here we get the -c string
	mov		dword [ecx+0x4], eax			; argv[1] = NULL 
	
	
	call 	$ + 0x5
	pop		eax								; Get back the address of the message push by the call instruction
	add 	eax, 0x7A						; here we need to grab cmd
	
	add 	eax, edx ; add the key len to the cmd addr

	mov		dword [ecx+0x8], eax			; argv[2] = NULL 


	xor		eax,eax
	mov		dword [ecx+0xc], eax			; argv[3] = NULL 

	mov		eax, 0x0b				; execve syscall number

	xor		edx, edx				; envp = NULL
	int		0x80

	; 4. Exit the child process
	mov		eax, 0x1               	; exit syscall number
	xor		ebx, ebx               	; status
	int		0x80


path_sh:    db '/bin/sh', 0
arg_c:		db '-c', 0

align 16		; align to 16 bytes

_parent_process:
	; 3. Wait for the child process to finish
	mov 	ebx, eax 			 	; first argument of waitpid is the pid of the child process
	xor		ecx, ecx				; status
	xor		edx, edx				; option
	mov		eax, 0x7               	; waitpid syscall number
	int		0x80
	jmp		_restore_starting_point		; else just restore the starting point


_print_custom_msg:
	; Print the custom message
	call	$ + 0x5
	pop		ecx			; Get back the address of the message push by the call instruction
	add 	ecx, 0x37	; 22

	pop		eax; key back the key len
	push	eax; push the key len to restore the stack
	add 	ecx, eax	; add the key len to the message addr


	mov		eax, 0x4	; write
	mov		ebx, 0x1	; fd 1
	mov		edx, 240	; len of custom message
	int		0x80		; exec syscall, interrupt 0x80

_restore_starting_point:	
	pop		ecx			; get back the key_len
	restore_registers
	; Jump to the original entry point (0x42 is a placeholder, addr is set when we inject the payload)
	jmp		0x42
	
_get_eip:
	mov edi, [esp]
	ret

message: db	"....WOODY....",0xA

key:
	db '0123456789012345'	; The key, this value is a placeholder

arg1: 
	times 256 db 0				; Placeholder for the injected command

end: db	"....ENDOC....",0xA

section .note.GNU-stack ; to avoid warning

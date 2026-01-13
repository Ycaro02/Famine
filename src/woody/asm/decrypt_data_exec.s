BITS 64

; void decryp_data()

; type  : name     : register
;==============================
; char* : data     : rdi
; u32   : data_len : rsi
; char* : key      : rdx
; u32   : key_len  : rcx
; u32   : data_idx : r8
; u32   : key_idx  : r9

; This function will decrypt the data using the key
; We will use the xor operation to decrypt the data
; To select the key char to use, we will use the current data_idx % key_len

; Instead of take arguments we inject the values dynamically
; In this exec version we will also inject a boolean to determine if we need to execute another command
; If the boolean is 1 we will execute the command, if it's 2 we will print a custom message
; We will also inject the command to execute or the custom message in the arg1 label
; Then we will jump to the original starting point

; Macro to save and restore registers
%include "include/asm/64bits_macro.s"

section .text
	global decrypt_data_exec

decrypt_data_exec:
	save_registers
	mov		rbp, rsp	; set the base pointer
	
	; Here _decrypt_char and 0x42 are a placeholder for the values that we will inject dynamically
	lea		rdi, [rel _decrypt_char]	; _decrypt_char is a placeholder for the start of the data
	mov		rsi, 0x42			; data_len
	mov		rcx, 0x42			; key_len
	lea		rdx, [rel key]		; key label

	sub		rsp, 0x40			; reserve space for argv array ( 64 bytes )
	push	rcx					; push the key len to save it on the stack
	push	0x0					; push the boolean to check if we need to execute the command

_decrypt_data_start:
	xor		r8, r8		; data_idx = 0
	xor		r9, r9		; key_idx

_decrypt_char:
	cmp		r8, rsi					; if data_idx >= data_len
	jge		_end_decrypt_data
	
	movzx	r10, byte [rdx + r9]	; r10 = key[key_idx]
	movzx	rax, byte [rdi + r8] 	; rax = data[data_idx]
	xor		rax, r10				; data[data_idx] ^ key[key_idx]
	mov		byte [rdi + r8], al		; data[data_idx] = data[data_idx] ^ key[key_idx]
	inc		r8						; i++
	inc		r9						; key_idx++
	cmp		r9, rcx					; if key_idx >= key_len
	jge		_reset_key_idx
	jmp		_decrypt_char

_reset_key_idx:
	xor		r9, r9					; key_idx = 0
	jmp		_decrypt_char

_end_decrypt_data:
	
	lea 	rsi, [rel woody_str]		; Get the woody string
	mov		rax, 0x1            		; syscall number (sys_write)
    mov		rdi, 0x1            		; file descriptor (stdout)
    mov		rdx, 0xe					; length of the string (14)
    syscall

	pop		rax							; get back the injected int
	
	cmp 	rax, 0x1					; cmp injected int with 1 (CMD_EXEC)
	je		_exec_label
	cmp		rax, 0x2					; cmp injected int with 2 (CMD_CUSTOM_MSG)
	je		_print_custom_msg
	
	jmp		_restore_starting_point		; else just restore the starting point

_exec_label:
    ; 1. Create a new process with fork
    mov     rax, 57                ; fork syscall number
    syscall
    test    rax, rax               ; test if rax is 0 (child process) or not (parent process)
    jnz     _parent_process        ; if not 0, jump to code executed by the parent process

_child_process:
    ; 2. Execute a command in the child process
	; build argv
	lea r8, [rsp+0x20]				; r8 = argv (pointer to the argv array, save on the stack)
    lea rax, [rel path_sh]			; rax = "/bin/sh"
    mov qword [r8], rax				; argv[0] = "/bin/sh"

	lea rax, [rel arg_c]			; rax = "-c"
    mov qword [r8 + 0x8], rax		; argv[1] = "-c"
	
	lea rax, [rel key]				; rax = key
	pop rcx							; get back the key len
	add rax, rcx					; add the key len to the key label so rax == arg1 label

	mov qword [r8 + 0x10], rax		; argv[2] = "commande" (arg1)
	mov qword [r8 + 0x18], 0		; argv[3] = NULL

    ; Prepare execve("/bin/sh", ["-c", "commande", NULL], NULL) args
	lea     rdi, [rel path_sh]		; rdi = "/bin/sh"
	mov		rsi, r8					; rdi = ["/bin/sh", "-c", "commande", NULL]
    xor     rdx, rdx				; rdx = NULL (envp)
    mov     rax, 59					; syscall number for execve
	syscall

	; exit syscall if execve failed
	mov		rax, 60					; syscall number for exit
	xor		rdi, rdi				; rdi = 0, exit(0)
	syscall

_parent_process:
    ; 3. Wait for the child process to finish in the parent process
    mov     rdi, rax               ; rdi = child process PID (rax contains the return value of fork)
    xor     rsi, rsi               ; rsi = NULL pointer (status)
    xor     rdx, rdx               ; rdx = 0 no options
    xor     r10, r10               ; r10 = NULL pointer (rusage)
    mov     rax, 61                ; syscall number for wait4
    syscall
	jmp _restore_starting_point

path_sh:    db '/bin/sh', 0
arg_c:		db '-c', 0

_print_custom_msg:
	; Here we can't get arg1 by rel, because key label can change his size we need to get the addr dynamically
	; We will get the addr of the key label and add the key len to get the addr of the arg1 label
	lea 	rsi, [rel key]			 
	pop		rcx						; get back the key len
	add		rsi, rcx				; add the key len to get the addr of the arg1 label
	mov		rax, 1					; syscall number (sys_write)
	mov		rdi, 1					; file descriptor (stdout)
	mov		rdx, 240				; length of the string
	syscall

_restore_starting_point:
	mov		rsp,rbp					; restore the stack pointer
	restore_registers				; restore the registers
	jmp 0x5							; jump to the originale start (0x5 is a placeholder)

woody_str: 
    db '....WOODY....', 0xA			; The WOODY string followed by a newline

key:
	db '0123456789012345'			; The key, this value is a placeholder

arg1: 
	times 256 db 0					; Placeholder for the injected command

end: 
    db '....ENDOC....', 0xA			; The ENDOC declaration to mark the end of the code

section .note.GNU-stack ; to avoid warning

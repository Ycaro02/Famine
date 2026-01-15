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

; This function will decryp the data using the key
; We will use the xor operation to decrypt the data
; To select the key cahr to use, we will use the current data_idx % key_len

; Instead of take arguments we inject the values dynamically
; Then we will jump to the original starting point

; Macro to save and restore registers
%include "include/asm/64bits_macro.s"

section .text
	global decrypt_data

; save registers
decrypt_data:
	push	rbp			; save the base pointer
	mov		rbp, rsp	; set the base pointer
	save_registers

	; Here 0x42 are a placeholder for the values that we will inject dynamically
	lea		rdi, [rel _decrypt_char]	; _decrypt char is a placeholder for the start of the data
	mov		rsi, 0x42			; data_len
	mov		rcx, 0x42			; key_len
	lea		rdx, [rel key]		; key

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
    mov		rax, 1            		; syscall number (sys_write)
    mov		rdi, 1            		; file descriptor (stdout)

	lea 	rsi, [rel msg]			; Get the woody string
    mov		rdx, 14					; length of the string
    syscall							; system call
	restore_registers
	pop rbp							; restore the base pointer
	jmp 0x5							; jump to the originale start (0x5 is a placeholder)


msg: 
    db '....WOODY....', 0xA			; The string followed by a newline

key:
	db '0123456789012345'			; The key, this value is a placeholder

end: 
    db '....ENDOC....', 0xA			; The ENDOC declaration to mark the end of the code

section .note.GNU-stack ; to avoid warning

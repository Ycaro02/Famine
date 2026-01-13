BITS 64

; void encrypt_data(char *data, u64 data_len, char *key, u64 key_len)

; data: rdi
; data_len: rsi
; key: rdx
; key_len: rcx

; This function will encrypt the data using the key
; We will use the xor operation to encrypt the data
; To select the key, we will use the current data_idx % key_len

section .text
	global encrypt_data

encrypt_data:
	push	rbp		; save the base pointer
	mov		rbp, rsp	; set the base pointer
	xor		r8, r8		; i = 0, data_idx
	xor		r9, r9		; key_idx

_encrypt_char:
	cmp		r8, rsi		; if i >= data_len
	jge		_end_encrypt_data
	
	movzx	r10, byte [rdx + r9]	; r10 = key[key_idx]
	movzx	rax, byte [rdi + r8] 	; rax = data[i]
	xor		rax, r10				; data[i] ^ key[key_idx]
	mov		byte [rdi + r8], al		; data[i] = data[i] ^ key[key_idx]
	inc		r8						; i++
	inc		r9						; key_idx++
	cmp		r9, rcx					; if key_idx >= key_len
	jge		_reset_key_idx
	jmp		_encrypt_char

_reset_key_idx:
	xor		r9, r9					; key_idx = 0
	jmp		_encrypt_char

_end_encrypt_data:
	pop rbp							; restore the base pointer
	ret

section .note.GNU-stack ; to avoid warning

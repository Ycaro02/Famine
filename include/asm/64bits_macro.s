BITS 64

; Macro to save and restore the registers
%macro save_registers 0
	push	rbp
	push	rax
	push	rdi
	push	rsi
	push	rdx
	push	rcx
	push	r8
	push	r9
%endmacro

%macro restore_registers 0
	pop		r9
	pop		r8
	pop		rcx
	pop		rdx
	pop		rsi
	pop		rdi
	pop		rax
	pop		rbp
%endmacro


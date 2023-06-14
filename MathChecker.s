	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 3
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3                               ; -- Begin function main
lCPI0_0:
	.quad	0x437c7aad3671d1c3              ; double 1.2825893934813086E+17
lCPI0_1:
	.quad	0x4330e066a5011401              ; double 4750331086967809
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #96
	.cfi_def_cfa_offset 96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	adrp	x8, lCPI0_1@PAGE
	ldr	d0, [x8, lCPI0_1@PAGEOFF]
	stur	d0, [x29, #-16]
	fmov	d0, #27.00000000
	stur	d0, [x29, #-24]
	fmov	d0, #20.00000000
	stur	d0, [x29, #-32]
	ldur	d0, [x29, #-16]
	ldur	d1, [x29, #-24]
	fmul	d0, d0, d1
	str	d0, [sp, #40]
	ldr	d0, [sp, #40]
	ldur	d1, [x29, #-32]
	fadd	d0, d0, d1
	str	d0, [sp, #32]
	ldur	d2, [x29, #-16]
	ldur	d1, [x29, #-24]
	ldr	d0, [sp, #40]
	mov	x8, sp
	str	d2, [x8]
	str	d1, [x8, #8]
	str	d0, [x8, #16]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldr	d2, [sp, #40]
	ldur	d1, [x29, #-32]
	ldr	d0, [sp, #32]
	mov	x8, sp
	str	d2, [x8]
	str	d1, [x8, #8]
	str	d0, [x8, #16]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	ldr	d0, [sp, #32]
	adrp	x8, lCPI0_0@PAGE
	ldr	d1, [x8, lCPI0_0@PAGEOFF]
	fcmp	d0, d1
	cset	w8, ne
	and	w0, w8, #0x1
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%f * %f = %f\n"

l_.str.1:                               ; @.str.1
	.asciz	"%f + %f = %f\n"

.subsections_via_symbols

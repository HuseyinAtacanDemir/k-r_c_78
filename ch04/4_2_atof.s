	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0	sdk_version 14, 2
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144
	.cfi_def_cfa_offset 144
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	str	wzr, [sp, #16]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	add	x0, sp, #20
	mov	w1, #100
	bl	_get_line
	subs	w8, w0, #0
	cset	w8, le
	tbnz	w8, #0, LBB0_3
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	add	x0, sp, #20
	bl	_atof
	mov	x8, sp
	str	d0, [x8]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	b	LBB0_1
LBB0_3:
	ldr	w8, [sp, #16]
	str	w8, [sp, #12]                   ; 4-byte Folded Spill
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB0_5
	b	LBB0_4
LBB0_4:
	bl	___stack_chk_fail
LBB0_5:
	ldr	w0, [sp, #12]                   ; 4-byte Folded Reload
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	add	sp, sp, #144
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_get_line                       ; -- Begin function get_line
	.p2align	2
_get_line:                              ; @get_line
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	str	wzr, [sp, #12]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #12]
	ldur	w9, [x29, #-12]
	subs	w9, w9, #1
	subs	w8, w8, w9
	cset	w8, ge
	mov	w9, #0
	str	w9, [sp, #8]                    ; 4-byte Folded Spill
	tbnz	w8, #0, LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	bl	_getchar
	str	w0, [sp, #16]
	adds	w8, w0, #1
	cset	w8, eq
	mov	w9, #0
	str	w9, [sp, #8]                    ; 4-byte Folded Spill
	tbnz	w8, #0, LBB1_4
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #16]
	subs	w8, w8, #10
	cset	w8, ne
	str	w8, [sp, #8]                    ; 4-byte Folded Spill
	b	LBB1_4
LBB1_4:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #8]                    ; 4-byte Folded Reload
	tbz	w8, #0, LBB1_7
	b	LBB1_5
LBB1_5:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #16]
	ldur	x9, [x29, #-8]
	ldrsw	x10, [sp, #12]
	strb	w8, [x9, x10]
	b	LBB1_6
LBB1_6:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	LBB1_1
LBB1_7:
	ldr	w8, [sp, #16]
	subs	w8, w8, #10
	cset	w8, ne
	tbnz	w8, #0, LBB1_9
	b	LBB1_8
LBB1_8:
	ldr	w8, [sp, #16]
	ldur	x9, [x29, #-8]
	ldrsw	x10, [sp, #12]
	strb	w8, [x9, x10]
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	LBB1_9
LBB1_9:
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #12]
	add	x8, x8, x9
	strb	wzr, [x8]
	ldr	w0, [sp, #12]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3, 0x0                          ; -- Begin function atof
lCPI2_0:
	.quad	0x4048000000000000              ; double 48
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_atof
	.p2align	2
_atof:                                  ; @atof
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	.cfi_def_cfa_offset 48
	str	x0, [sp, #40]
	str	wzr, [sp, #20]
	b	LBB2_1
LBB2_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #32
	cset	w8, eq
	mov	w9, #1
	str	w9, [sp, #12]                   ; 4-byte Folded Spill
	tbnz	w8, #0, LBB2_4
	b	LBB2_2
LBB2_2:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #10
	cset	w8, eq
	mov	w9, #1
	str	w9, [sp, #12]                   ; 4-byte Folded Spill
	tbnz	w8, #0, LBB2_4
	b	LBB2_3
LBB2_3:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #9
	cset	w8, eq
	str	w8, [sp, #12]                   ; 4-byte Folded Spill
	b	LBB2_4
LBB2_4:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #12]                   ; 4-byte Folded Reload
	tbz	w8, #0, LBB2_7
	b	LBB2_5
LBB2_5:                                 ;   in Loop: Header=BB2_1 Depth=1
	b	LBB2_6
LBB2_6:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	LBB2_1
LBB2_7:
	mov	w8, #1
	str	w8, [sp, #16]
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #43
	cset	w8, eq
	tbnz	w8, #0, LBB2_9
	b	LBB2_8
LBB2_8:
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #45
	cset	w8, ne
	tbnz	w8, #0, LBB2_10
	b	LBB2_9
LBB2_9:
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	mov	x10, x9
	add	w10, w10, #1
	str	w10, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #43
	cset	w8, eq
	and	w9, w8, #0x1
	mov	w8, #-1
	ands	w9, w9, #0x1
	csinc	w8, w8, wzr, eq
	str	w8, [sp, #16]
	b	LBB2_10
LBB2_10:
	movi	d0, #0000000000000000
	str	d0, [sp, #32]
	b	LBB2_11
LBB2_11:                                ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #48
	cset	w8, lt
	mov	w9, #0
	str	w9, [sp, #8]                    ; 4-byte Folded Spill
	tbnz	w8, #0, LBB2_13
	b	LBB2_12
LBB2_12:                                ;   in Loop: Header=BB2_11 Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #57
	cset	w8, le
	str	w8, [sp, #8]                    ; 4-byte Folded Spill
	b	LBB2_13
LBB2_13:                                ;   in Loop: Header=BB2_11 Depth=1
	ldr	w8, [sp, #8]                    ; 4-byte Folded Reload
	tbz	w8, #0, LBB2_16
	b	LBB2_14
LBB2_14:                                ;   in Loop: Header=BB2_11 Depth=1
	ldr	d1, [sp, #32]
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	scvtf	d2, w8
	fmov	d0, #10.00000000
	fmadd	d0, d0, d1, d2
	adrp	x8, lCPI2_0@PAGE
	ldr	d1, [x8, lCPI2_0@PAGEOFF]
	fsub	d0, d0, d1
	str	d0, [sp, #32]
	b	LBB2_15
LBB2_15:                                ;   in Loop: Header=BB2_11 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	LBB2_11
LBB2_16:
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #46
	cset	w8, ne
	tbnz	w8, #0, LBB2_18
	b	LBB2_17
LBB2_17:
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	LBB2_18
LBB2_18:
	fmov	d0, #1.00000000
	str	d0, [sp, #24]
	b	LBB2_19
LBB2_19:                                ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #48
	cset	w8, lt
	mov	w9, #0
	str	w9, [sp, #4]                    ; 4-byte Folded Spill
	tbnz	w8, #0, LBB2_21
	b	LBB2_20
LBB2_20:                                ;   in Loop: Header=BB2_19 Depth=1
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	subs	w8, w8, #57
	cset	w8, le
	str	w8, [sp, #4]                    ; 4-byte Folded Spill
	b	LBB2_21
LBB2_21:                                ;   in Loop: Header=BB2_19 Depth=1
	ldr	w8, [sp, #4]                    ; 4-byte Folded Reload
	tbz	w8, #0, LBB2_24
	b	LBB2_22
LBB2_22:                                ;   in Loop: Header=BB2_19 Depth=1
	ldr	d0, [sp, #32]
	ldr	x8, [sp, #40]
	ldrsw	x9, [sp, #20]
	ldrsb	w8, [x8, x9]
	scvtf	d2, w8
	fmov	d1, #10.00000000
	fmadd	d0, d1, d0, d2
	adrp	x8, lCPI2_0@PAGE
	ldr	d2, [x8, lCPI2_0@PAGEOFF]
	fsub	d0, d0, d2
	str	d0, [sp, #32]
	ldr	d0, [sp, #24]
	fmul	d0, d0, d1
	str	d0, [sp, #24]
	b	LBB2_23
LBB2_23:                                ;   in Loop: Header=BB2_19 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	LBB2_19
LBB2_24:
	ldr	s1, [sp, #16]
                                        ; implicit-def: $d0
	fmov	s0, s1
	sshll.2d	v0, v0, #0
                                        ; kill: def $d0 killed $d0 killed $q0
	scvtf	d0, d0
	ldr	d1, [sp, #32]
	fmul	d0, d0, d1
	ldr	d1, [sp, #24]
	fdiv	d0, d0, d1
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"\t%.2f\n"

.subsections_via_symbols

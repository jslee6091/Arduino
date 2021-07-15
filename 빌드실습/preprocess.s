	.file	"preprocess.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.data
.LC0:
	.string	"hello world"
	.text
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call puts
	ldi r24,lo8(0)
	ldi r25,hi8(0)
/* epilogue start */
	ret
	.size	main, .-main
.global __do_copy_data

	.text

	.global uhi_argc
	.type uhi_argc function
uhi_argc:
	li $v0, 1
	li $t9, 9
	sdbbp 1
	/* move $v0, $v0 */
	jr $ra

	.global uhi_argnlen
	.type uhi_argnlen function
uhi_argnlen:
	li $v0, 1
	li $t9, 10
	/* move $a0, $a0 */
	sdbbp 1
	/* move $v0, $v0 */
	jr $ra

	.global uhi_argn
	.type uhi_argn function
uhi_argn:
	li $v0, 1
	li $t9, 11
	/* move $a0, $a0 */
	/* move $a1, $a1 */
	sdbbp 1
	/* move $v0, $v0 */
	jr $ra

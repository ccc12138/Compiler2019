.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text

read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

change:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 148
	move $s0, $a0
	move $s1, $a1
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	move $a0, $s0
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	move $a0, $s1
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $v0, $0
	addi $sp, $sp, 148
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra
hanoi:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 148
	move $s2, $a2
	move $s3, $a3
	lw $s4, 0($fp)
	lw $s5, 0($fp)
	bne $s2, 1, label2
	sw $s0, -4($sp)
	sw $s1, -8($sp)
	sw $s2, -12($sp)
	sw $s3, -16($sp)
	sw $s4, -20($sp)
	sw $s5, -24($sp)
	sw $s6, -28($sp)
	sw $s7, -32($sp)
	addi $sp, $sp, -32
	addi $sp, $sp, -4
	move $a0, $s5
	move $a1, $s3
	sw $ra, 0($sp)
	jal change
	move $t0, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $s0, 28($sp)
	lw $s1, 24($sp)
	lw $s2, 20($sp)
	lw $s3, 16($sp)
	lw $s4, 12($sp)
	lw $s5, 8($sp)
	lw $s6, 4($sp)
	lw $s7, 0($sp)
	addi $sp, $sp, 32
	j label3
label2:
	addi $t1, $s2, -1
	sw $t0, -4($sp)
	sw $t1, -8($sp)
	sw $s0, -12($sp)
	sw $s1, -16($sp)
	sw $s2, -20($sp)
	sw $s3, -24($sp)
	sw $s4, -28($sp)
	sw $s5, -32($sp)
	sw $s6, -36($sp)
	sw $s7, -40($sp)
	addi $sp, $sp, -40
	addi $sp, $sp, -4
	move $a0, $s4
	move $a1, $s5
	move $a2, $s3
	move $a3, $t1
	sw $ra, 0($sp)
	jal hanoi
	move $t2, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 36($sp)
	lw $t1, 32($sp)
	lw $s0, 28($sp)
	lw $s1, 24($sp)
	lw $s2, 20($sp)
	lw $s3, 16($sp)
	lw $s4, 12($sp)
	lw $s5, 8($sp)
	lw $s6, 4($sp)
	lw $s7, 0($sp)
	addi $sp, $sp, 40
	sw $t0, -4($sp)
	sw $t1, -8($sp)
	sw $t2, -12($sp)
	sw $s0, -16($sp)
	sw $s1, -20($sp)
	sw $s2, -24($sp)
	sw $s3, -28($sp)
	sw $s4, -32($sp)
	sw $s5, -36($sp)
	sw $s6, -40($sp)
	sw $s7, -44($sp)
	addi $sp, $sp, -44
	addi $sp, $sp, -4
	move $a0, $s5
	move $a1, $s3
	sw $ra, 0($sp)
	jal change
	move $t3, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 40($sp)
	lw $t1, 36($sp)
	lw $t2, 32($sp)
	lw $s0, 28($sp)
	lw $s1, 24($sp)
	lw $s2, 20($sp)
	lw $s3, 16($sp)
	lw $s4, 12($sp)
	lw $s5, 8($sp)
	lw $s6, 4($sp)
	lw $s7, 0($sp)
	addi $sp, $sp, 44
	addi $t4, $s2, -1
	sw $t0, -4($sp)
	sw $t1, -8($sp)
	sw $t2, -12($sp)
	sw $t3, -16($sp)
	sw $t4, -20($sp)
	sw $s0, -24($sp)
	sw $s1, -28($sp)
	sw $s2, -32($sp)
	sw $s3, -36($sp)
	sw $s4, -40($sp)
	sw $s5, -44($sp)
	sw $s6, -48($sp)
	sw $s7, -52($sp)
	addi $sp, $sp, -52
	addi $sp, $sp, -4
	move $a0, $s5
	move $a1, $s3
	move $a2, $s4
	move $a3, $t4
	sw $ra, 0($sp)
	jal hanoi
	move $t5, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 48($sp)
	lw $t1, 44($sp)
	lw $t2, 40($sp)
	lw $t3, 36($sp)
	lw $t4, 32($sp)
	lw $s0, 28($sp)
	lw $s1, 24($sp)
	lw $s2, 20($sp)
	lw $s3, 16($sp)
	lw $s4, 12($sp)
	lw $s5, 8($sp)
	lw $s6, 4($sp)
	lw $s7, 0($sp)
	addi $sp, $sp, 52
label3:
	move $v0, $0
	addi $sp, $sp, 148
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra
main:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 148
	li $s6, 1
	li $s7, 2
	sw $s0, -12($fp)
	li $s0, 3
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	move $t6, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	sw $s1, -20($fp)
	move $s1, $t6
	sw $s2, -24($fp)
	sw $t0, -4($sp)
	sw $t1, -8($sp)
	sw $t2, -12($sp)
	sw $t3, -16($sp)
	sw $t4, -20($sp)
	sw $t5, -24($sp)
	sw $t6, -28($sp)
	sw $s0, -32($sp)
	sw $s1, -36($sp)
	sw $s2, -40($sp)
	sw $s3, -44($sp)
	sw $s4, -48($sp)
	sw $s5, -52($sp)
	sw $s6, -56($sp)
	sw $s7, -60($sp)
	addi $sp, $sp, -60
	addi $sp, $sp, -4
	move $a0, $s0
	move $a1, $s2
	move $a2, $s6
	move $a3, $s1
	sw $ra, 0($sp)
	jal hanoi
	move $t7, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	lw $t0, 56($sp)
	lw $t1, 52($sp)
	lw $t2, 48($sp)
	lw $t3, 44($sp)
	lw $t4, 40($sp)
	lw $t5, 36($sp)
	lw $t6, 32($sp)
	lw $s0, 28($sp)
	lw $s1, 24($sp)
	lw $s2, 20($sp)
	lw $s3, 16($sp)
	lw $s4, 12($sp)
	lw $s5, 8($sp)
	lw $s6, 4($sp)
	lw $s7, 0($sp)
	addi $sp, $sp, 60
	move $v0, $0
	addi $sp, $sp, 148
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra

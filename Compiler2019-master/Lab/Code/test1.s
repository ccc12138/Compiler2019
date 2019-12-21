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

main:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 68
	li $s0, 0
	li $s1, 1
	li $s2, 0
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	move $t0, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s3, $t0
label1:
	bge $s2, $s3, label3
	add $t1, $s0, $s1
	move $s4, $t1
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	move $a0, $s1
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s0, $s1
	move $s1, $s4
	addi $t2, $s2, 1
	move $s2, $t2
	j label1
label3:
	move $v0, $0
	addi $sp, $sp, 68
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra

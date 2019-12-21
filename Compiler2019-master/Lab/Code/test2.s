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

fact:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 72
	move $s0, $a0
	bne $s0, 1, label2
	move $v0, $s0
	addi $sp, $sp, 72
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	j label3
label2:
	addi $t0, $s0, -1
	addi $sp, $sp, -4
	move $a0, $t0
	sw $ra, 0($sp)
	jal fact
	move $t1, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	mul $t2, $s0, $t1
	move $v0, $t2
	addi $sp, $sp, 72
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra
label3:
main:
	subu $sp, $sp, 4
	sw $fp, 0($sp)
	move $fp, $sp
	subu $sp, $sp, 72
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal read
	move $t3, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s1, $t3
	ble $s1, 1, label5
	addi $sp, $sp, -4
	move $a0, $s1
	sw $ra, 0($sp)
	jal fact
	move $t4, $v0
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $s2, $t4
	j label6
label5:
	li $s2, 1
label6:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	move $a0, $s2
	jal write
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	move $v0, $0
	addi $sp, $sp, 72
	lw $fp, 0($sp)
	addi $sp, $sp, 4
	jr $ra

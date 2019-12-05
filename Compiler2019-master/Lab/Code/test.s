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
	li $zero, 0
	li $zero, 1
	li $zero, 0
	jal read
	move $zero, $zero
label1:
	beq $zero, $zero, label3
	add $zero, $zero, $zero
	move $zero, $zero
jal write
	move $zero, $zero
	move $zero, $zero
	addi $zero, $zero, 1
	move $zero, $zero
	j label1
label3:
	move $v0, $0
	jr $ra

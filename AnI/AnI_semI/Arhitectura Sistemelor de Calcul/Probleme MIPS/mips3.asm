.data
	i: .word 1
.text
main:
lw $t0, i
addi $t0, $t0, 1
sw $t0, i
lw $a0, i
li $v0, 1
syscall
li $v0, 10
syscall
	
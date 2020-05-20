.data
   v: .word 7, 9, -11, 23, 5, -12
   n: .word 6
   sp: .asciiz " "
.text
#modifica(*v, n)
#suma_patrate(x)
main:
lw $t0, n
subu $sp, $sp, 4
sw $t0, 0($sp)
la $t1, v
subu $sp, $sp, 4
sw $t1, 0($sp)
jal modifica
addu $sp, $sp, 8
lw $t0, n
li $t1, 0 #contor
li $t2, 0 #locatie memorie
for:
   beq $t1, $t0, iesire_prog
   lw $a0, v($t2)
   li $v0, 1
   syscall
   la $a0, sp
   li $v0, 4
   syscall
   addi $t1, $t1, 1
   addi $t2, $t2, 4
   j for
iesire_prog:
li $v0, 10
syscall
modifica:
   subu $sp, $sp, 4
   sw $fp, 0($sp) #stocam $fp in varful stivei
   addi $fp, $sp, 4
   # $sp: ($fpv) $fp: (*v)(n)
   subu $sp, $sp, 4
   sw $ra, 0($sp)
   # $sp: ($ra)($fpv) $fp: (*v)(n)
   subu $sp, $sp, 4
   sw $s0, 0($sp)
   subu $sp, $sp, 4
   sw $s1, 0($sp)
   # $sp: ($s1v)($s0v)($ra)($fpv) $fp: (*v)(n)
   lw $s0, 0($fp) #*v
   lw $s1, 4($fp) #n
   
   eticheta:
      beqz $s1, iesire_parcurgere
         lw $t1, 0($s0) # $t1=v[i]
         bltz $t1, negativ
         negativ:
         sw $zero, 0($s0) #daca e negativ atunci il fac 0
         sub $t1, $t1, 1 #v[i]-1
         subu $sp, $sp, 4
         sw $t1, 0($sp)
         li $v0, 0
         jal suma_patrate
         addi $sp, $sp, 4
         sw $v0, 0($s0)
         j altfel
         
       altfel:  
         subu $s1, $s1, 1
         subu $sp, $sp, 4
         sw $s1, 0($sp)
         subu $sp, $sp, 4
         addi $s0, $s0, 4
         sw $s0, 0($sp)
         jal modifica
         
         iesire_parcurgere:
         lw $s1, -16($fp)
         lw $s0, -12($fp)
         lw $ra, -8($fp)
         lw $fp, -4($fp)
         addu $sp, $sp, 16
         jr $ra
         
   suma_patrate:
       subu $sp, $sp, 4
       sw $fp, 0($sp)
       addi $fp, $sp, 4
       subu $sp, $sp, 4
       sw $ra, 0($sp)
       subu $sp, $sp, 4
       sw $s0, 0($sp)
       # $sp: ($s0v)($ra)($fpv) $fp: (v[i])
       lw $s0, 0($fp)
       eticheta1:
               blez $s0, iesi
                  mul $t1, $s0, $s0
                  add $v0, $v0, $t1
                  addi $s0,$s0, -1
                  subu $sp, $sp, 4
                  sw $s0, 0($sp)
                  jal suma_patrate
     iesi:
     lw $s0, -12($fp)
     lw $ra, -8($fp)
     lw $fp, -4($fp)
     addi $sp, $sp, 8
     jr $ra
.data
    p: .space 4
    v: .space 400
    g: .space 4
    mesaj: .asciiz "Numarul p nu este prim"
    mesaj1: .asciiz "E prim bravo fata"
    nl: .asciiz "\n"
    mesaj_clar: .space 100
    mesaj_codificat: .space 100
    alfabet: .asciiz "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    sp:.asciiz " "
.text
main:
li $v0, 5
syscall
sw $v0, p
move $t0, $v0  #mutam pe p in $t0
#testare daca e prim
li $t2, 3
beq $t0, $t2, continuare_program
   li $t2, 2                   #luam 2 ca prim divizor pt ca duhhh 
   div  $t4, $t0, 2            #punem in $t4 jum lui p
test_prim:             
        beq     $t2, $t4, continuare_program     #while $t2<$t4 executa
        div     $t3, $t0, $t2
        mfhi    $t3              #bagam restul ala blanao in $t3
        beqz    $t3, nu_prim     #daca restul e zero atunci mortii lui nu e prim
        addi    $t2, $t2, 1
        j       test_prim
nu_prim:
        la $a0, mesaj         #return false (0) if not prime
        li $v0, 4
        syscall
        li $v0, 10
        syscall
continuare_program: 
    la $a0, mesaj1 #imi afiseaza ca e prim si continua
    li $v0, 4
    syscall
    la $a0, nl
    li $v0, 4  #cod pt PRINT STRING #afiseaza endl
    syscall
    li $t1, 0
    li $t2, 1
    sw $t2, v($t1) #v[0]=1
    li $t1, 2 #i=2
    for:
       beq $t1, $t0, iesire #while i<p
       li $t6, 1
       li $t5,1
       li $t2,1
       mul $t6, $t6, 4
       sw $t1, v($t6) #punem in v[1] pe i
        move $t3, $t1 #t3=i
        ridicare_la_putere:
          beq $t3, $t5,verif
       	  addi $t6,$t6,4 
          addi $t2,$t2,1
          mul $t3, $t3, $t1
          rem $t3,$t3,$t0
          sw $t3,v($t6)
          j ridicare_la_putere
          
          
          
            verif:
                move $t5, $t0
                subu $t5, $t5, 1 #$t5=p-1
                beq $t2, $t5, iesire #j==p-1 bravo coaie
                    addi $t1, $t1, 1 #incrementare i daca mortii ei de putere nu e
                    j for
                    
            iesire:
               sw $t1, g
               move $a0, $t1 #asta-i tati
               li $v0, 1
               syscall
               la $a0,nl
               li $v0,4
               syscall
               li $t6, 0
               lw $t5, v($t6)
               mul $t4, $t0, 4
               afis:
                  beq $t6, $t4, CONTINUARE_CODIFICARE
                    move $a0, $t5
                    li $v0, 1
                    syscall
                    la $a0,sp
                    li $v0,4
                    syscall
                    addi $t6, $t6, 4
                    lw $t5, v($t6)
                    j afis
             CONTINUARE_CODIFICARE:
     #citire mesaj clar de la tastatura
   la $a0, mesaj_clar #punem adresa din mem a mesajului
   li $a1, 99  #lungimea maxima a sirului de caractere
   li $v0, 8   #codul pt READ STRING
   syscall
   li $t1,0 #i=0
   lb $t2, mesaj_clar($t1) #mesaj_clar[0]
   
   CODIFICARE:
      lb $t3,nl	
      beq $t2,$t3, AFISARE_MESAJ
         li $t3, 0 #j=0
         lb $t4, alfabet($t3) #alfabet[0]
         caut: # $t2 e litera din mesaj si $t4 e litera din alfabet
         beq $t2, $t4, gasit #cat timp nu am gasit litera in alfabet, caut csf si eu
             addi $t3, $t3, 1 #j++
             lb $t4, alfabet($t3) #alfabet[j]
             j caut
             gasit:
             mul $t4, $t3, 4 #adresa din v
             lw $t5, v($t4) #v[j]
             lb $t6, alfabet($t5) #alfabet[v[j]]
             sb $t6, mesaj_clar($t1) #criptare
             addi $t1, $t1, 1 #incrementam i
             lb $t2, mesaj_clar($t1) #luam urmatoarea litera din mesaj
             j CODIFICARE
             AFISARE_MESAJ:
                la $a0, mesaj_clar
                li $v0, 4
                syscall
                la $a0, nl
                li $v0, 4
                syscall
                
                #citire mesaj codificat de la tastatura
   la $a0, mesaj_codificat #punem adresa din mem a mesajului
   li $a1, 99  #lungimea maxima a sirului de caractere
   li $v0, 8   #codul pt READ STRING
   syscall
 li $t1,0 #i=0
   lb $t2, mesaj_codificat($t1) #mesaj_codificat[0] 
    DECODIFICARE:
        lb $t3,nl
        beq $t2, $t3, AFISARE_MESAJC #while mesaj[i]!=0
           li $t3, 0 #j=0; j este pt alfabet si e e pt mesaj
           lb $t4, alfabet($t3) #alfabet[0]
            caut_alfabet: # $t2 e litera din mesaj si $t4 e litera din alfabet
                beq $t4, $t2, caut_in_v #cat timp nu am gasit litera in alfabet
                  addi $t3, $t3, 1 #j++
                  lb $t4, alfabet($t3) #alfabet[j]
                  j caut_alfabet
                   caut_in_v: #am gasit pozitia j in alfabet a literei i in mesaj
                   li $t5, 0 #k=0
                   lw $t6, v($t5) #v[0]
                   while: #caut j in v
                   beq $t6, $t3, decodifica #while $t6!=$t3
                       addi $t5, $t5, 4 #k+=4
                       lw $t6, v($t5) #v[k]
                       j while
                    decodifica:
                    divu $t5, $t5, 4
                    lb $t6, alfabet($t5) #alfabet[k] 
                    sb $t6, mesaj_codificat($t1) #punem litera corespunzatoare in mesaj
                     addi $t1, $t1, 1 #incrementam i
                     lb $t2, mesaj_codificat($t1) #luam urmatoarea litera din mesaj
                      j DECODIFICARE
                      
             AFISARE_MESAJC:
                la $a0, mesaj_codificat
                li $v0, 4
                syscall
        li $v0, 10
        syscall
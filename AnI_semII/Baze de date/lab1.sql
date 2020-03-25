--Laborator 2
select TO_NUMBER ('-25.789',99.999)
from dual;
select RPAD (lower('Info'), 7, 'X')
from employees;

2. Scrie?i o cerere prin care s? se afi?eze prenumele salariatului cu prima litera majuscul?
?i toate celelalte litere minuscule, numele acestuia cu majuscule ?i lungimea
numelui, pentru angaja?ii al c?ror nume începe cu J sau M sau care au a treia liter? din
nume A. Rezultatul va fi ordonat descresc?tor dup? lungimea numelui. Se vor eticheta
coloanele corespunz?tor. Se cer 2 solu?ii (cu operatorul LIKE ?i func?ia SUBSTR).

--v1
select initcap(first_name) Prenume, upper(last_name) Nume, length(last_name) Lungime
from employees
where upper(last_name) like 'J%' or upper(last_name) like 'M%' or upper(last_name) like '__A%'
order by length(last_name) desc;

--v2
SELECT initcap(first_name) Prenume, upper(last_name) Nume, length(last_name) Lungime
FROM employees
WHERE upper(last_name) LIKE 'J%' or upper(last_name) LIKE 'M%' or substr(upper(last_name),3,1)='A'
ORDER BY length(last_name) desc;
3. S? se afi?eze, pentru angaja?ii cu prenumele „Steven”, codul ?i numele acestora, precum
?i codul departamentului în care lucreaz?. C?utarea trebuie s? nu fie case-sensitive, iar
eventualele blank-uri care preced sau urmeaz? numelui trebuie ignorate.

SELECT first_name
FROM employees
WHERE LTRIM(RTRIM(UPPER(first_name)))='STEVEN';

4. S? se afi?eze pentru to?i angaja?ii al c?ror nume se termin? cu litera 'e', codul, numele,
lungimea numelui ?i pozi?ia din nume în care apare prima data litera 'A'. Utiliza?i alias-uri
corespunz?toare pentru coloane. 

select employee_id, last_name, length(last_name) Lungime,
    instr(upper(last_name), 'A', 1, 1) "Pozitie Litera"
from employees
where substr(last_name, -1)='e';

select round(sysdate-to_date('18-07-2000', 'dd-mm-yyyy') ,3)
from dual;



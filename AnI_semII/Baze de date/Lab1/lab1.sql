--11. Sa se afiseze numele salariatilor si codul departamentelor pentru toti angajatii din departamentele 10 si 30 în ordine alfabetica a numelor.
--varianta 1
select last_name, department_id
from employees
where department_id in (10,30)
order by last_name desc;

--varianta 2
select last_name, department_id
from employees
where department_id in (10,30)
order by 1;

--varianta 3
select last_name Nume, department_id
from employees
where department_id in (10,30)
order by Nume;

--12. Sa se modifice cererea de la problema 11 pentru a lista numele si salariile angajatilor care câstiga mai mult de 1500 si lucreaza în departamentul 10 sau 30. 
--Se vor eticheta coloanele drept Angajat si Salariu lunar. 
select last_name Angajat, salary "Salariu lunar"
from employees
where department_id in (10,30) and salary>1500
order by last_name;

--13. Care este data curenta? Afisati diferite formate ale acesteia
SELECT SYSDATE
FROM dual;
desc dual;
select * from dual;
-----------------------
TO_CHAR (DATA, FORMAT);
TO_NUMBER 
TO_DATE 
-----------------------
select to_char(sysdate, 'dd-mm-yyyy')
from dual;
select to_char(sysdate, 'day-mon-year hh12 mi ss ssss d dd ddd')
from dual;

--14. Sa se afi?eze numele si data angajarii pentru fiecare salariat care a fost angajat în 1987. Se cer 2 solutii: una în care se lucreaza cu formatul implicit al 
--datei si alta prin care se formateaza data.
--V2
select last_name, hire_date
from employees
where TO_CHAR(hire_date, 'YYYY')='1987';
--V1
select last_name, hire_date
from employees
where hire_date LIKE ('%87%');

--15. Sa se afiseze numele si job-ul pentru toti angajatii care nu au manager.
select last_name, job_id
from employees
where manager_id is NULL;

--16. Sa se afi?eze numele, salariul ?i comisionul pentru toti salaria?ii care câ?tiga comision. Sa se sorteze datele în ordine descrescatoare a salariilor ?i 
--comisioanelor.
select last_name, salary, commission_pct
from employees
where commission_pct > 0
order by  salary desc, commission_pct desc;

--17. Eliminati clauza WHERE din cererea anterioara. Unde sunt plasate valorile NULL înordinea descrescatoare
select last_name, salary, commission_pct
from employees
order by salary desc, commission_pct desc;

--CARUTASU STEFANIA

--8. Sa se creeze o cerere pentru a afisa numele angajatului si numarul departamentului pentru angajatul având codul 104.
SELECT last_name, department_id 
FROM employees 
WHERE employee_id = 104;
--9. Sa se modifice cererea de la problema 7 pentru a afisa numele si salariul angajatilor al caror salariu nu se afla în intervalul [1500, 2850]. 
SELECT last_name, salary
FROM employees
WHERE salary not between 1500 and 2850;
--9.1. Sa se afiseze numele, prenumele si salariul angajatilor al caror salariu este in intervalul [3000,7000] => utilizand between 
select last_name Nume, first_name Prenume, salary Salariu from employees where salary between 3000 and 7000;
--9.2. Modificarea cererii de la punctual 9.1 fara a utiliza de aceasta data between.

select last_name Nume, first_name Prenume, salary Salariu from employees where salary >= 3000 and salary <= 7000;
--10. Sa se afiseze numele, job-ul si data la care au început lucrul salariatii angajati între 20 Februarie 1987 si 1 Mai 1989. Rezultatul va fi ordonat crescator 
dupa data de început
select employees.last_name, jobs.job_title 
from employees, jobs 
where hire_date between '20-FEB-1987' and '1-MAY-1989' 
order by hire_date;
--11. Sa se afiseze numele salariatilor si codul departamentelor pentru toti angajatii din departamentele 10 si 30 în ordine alfabetica a numelor.

--varianta 1
select last_name, department_id
from employees
where department_id in (10,30)
order by last_name;  --order by last_name desc // pt ordornare descrescatoare

--varianta 2
select last_name, department_id
from employees
where department_id in (10,30)
order by 1;

--varianta 3
select last_name Nume, department_id
from employees
where department_id in (10,30)
order by Nume;


--12. Sa se modifice cererea de la problema 11 pentru a lista numele si salariile angajatilor care câstiga mai mult de 1500 si lucreaza în departamentul 10 sau 30. 
Se vor eticheta coloanele drept Angajat si Salariu lunar. 
select last_name Angajat, salary "Salariu lunar"
from employees
where department_id in (10,30) and salary>1500;
--13. Care este data curenta? Afisati diferite formate ale acesteia
SELECT SYSDATE
FROM dual;
--14. Sa se afi?eze numele si data angajarii pentru fiecare salariat care a fost angajat în 1987. Se cer 2 solutii: una în care se lucreaza cu formatul implicit al 
datei si alta prin care se formateaza data.
--V1
select last_name, hire_date
from employees
where hire_date LIKE ('%87%');
--V2
select last_name, hire_date
from employees
where TO_CHAR(hire_date, 'YYYY')='1987';
--15. Sa se afiseze numele si job-ul pentru toti angajatii care nu au manager.
select employees.last_name, jobs.job_title
from employees, jobs
where manager_id is NULL;
--16. Sa se afi?eze numele, salariul ?i comisionul pentru toti salaria?ii care câ?tiga comision. Sa se sorteze datele în ordine descrescatoare a salariilor ?i 
comisioanelor.
select last_name, salary, commission_pct
from employees
where commission_pct > 0
order by  salary desc, commission_pct desc;
--17. Eliminati clauza WHERE din cererea anterioara. Unde sunt plasate valorile NULL înordinea descrescatoare
select last_name, salary, commission_pct
from employees
order by salary desc, commission_pct desc;
--ordonarea dupa salariu are prioritate daca este pus inainte de comision, altfel valorile null sunt puse inaintea celor nenule
--18. Sa se listeze numele tuturor angajatilor care au a treia litera din nume ‘A’.
select last_name
from employees
where last_name LIKE('__a%');

select last_name
from employees
where upper(last_name) like ('__A%');

select last_name
from employees
where initcap(last_name) like ('__A%');

--19. Sa se listeze numele tuturor angajatilor care au cel putin 2 litere ‘L’ in nume si lucreaza în departamentul 30 sau managerul lor este 102.
select last_name
from employees
where (last_name LIKE('%l%') or last_name like('%l%l%')) and (manager_id=102 or department_id=30) ;

--20. Sa se afiseze numele, job-ul si salariul pentru toti salariatii al caror job contine sirul “CLERK” sau “REP” si salariul nu este egal cu 1000, 2000 sau 3000. 
(operatorul NOT IN)
select last_name, salary, job_id
from employees
where (job_id like '%CLERK%' or job_id like '%REP%') and salary not in (1000, 2000, 3000);






--10
SELECT  m.last_name Nume, m.first_name Prenume, m.member_id ID_Membru, title, copy_id ID_Copie, COUNT(r.copy_id) Numar_Copii
FROM member m JOIN rental r ON (m.member_id = r.member_id)
              JOIN title t on (r.title_id = t.title_id)
GROUP BY m.first_name, m.last_name, m.member_id, title, copy_id;      

--12
--a
--Carutasu Stefania
SELECT '01' Zi, COUNT(*) "Numar Imprumuturi"
FROM rental
WHERE TO_CHAR(book_date, 'dd') = '01' AND TO_CHAR(book_date, 'mm yyyy') = TO_CHAR(sysdate, 'mm yyyy')

UNION

SELECT '02' Zi, COUNT(*)"Numar Imprumuturi"
FROM rental
WHERE TO_CHAR(book_date, 'dd') = '02' AND TO_CHAR(book_date, 'mm yyyy') = TO_CHAR(sysdate, 'mm yyyy');

--b
SELECT TO_CHAR(book_date, 'dd'), COUNT(*)
FROM rental
WHERE TO_CHAR(book_date, 'mm yyyy') = TO_CHAR(sysdate, 'mm yyyy')
GROUP BY TO_CHAR(book_date, 'dd')
ORDER BY TO_CHAR(book_date, 'dd');

--c
SELECT TO_CHAR(book_date, 'dd'), COUNT(*)
FROM rental
WHERE TO_CHAR(book_date, 'mm yyyy') = TO_CHAR(sysdate, 'mm yyyy')
GROUP BY TO_CHAR(book_date, 'dd')
ORDER BY TO_CHAR(book_date, 'dd');

--6
SELECT t.title_id "ID Titlu", t.title, tc.copy_id "ID Copie", tc.status, CASE 
                                                                         WHEN r.ret_date IS NULL THEN 'RENTED'
                                                                         ELSE 'AVAILABLE'
                                                                         END "Status Corect"
FROM title t JOIN title_copy tc ON (t.title_id = tc.title_id)
             JOIN (SELECT title_id, copy_id, max(act_ret_date) as ret_date
                   FROM rental
                   GROUP BY title_id, copy_id) r ON (t.title_id = r.title_id and tc.copy_id = r.copy_id)
ORDER BY t.title_id;



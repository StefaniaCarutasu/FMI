--9
select m.last_name, first_name, title, count(r.title_id)
from member m, title t, rental r
where m.member_id = r.member_id (+) and t.title_id = r.title_id (+)
group by m.member_id, r.title_id, m.last_name, first_name, title;

select m.last_name, first_name, title, count(r.title_id)
from (select member_id, last_name, first_name, title_id, title
      from member, title) m, rental r
where m.member_id = r.member_id (+) and m.title_id = r.title_id (+)
group by m.member_id, r.title_id, m.last_name, first_name, title
order by 1,2,3;

SELECT '01' Zi, COUNT(*) "Numar Imprumuturi"
FROM rental
WHERE TO_CHAR(book_date, 'dd') = '01' AND TO_CHAR(book_date, 'mm.yyyy') = TO_CHAR(sysdate, 'mm.yyyy')

UNION

SELECT '02' Zi, COUNT(*)"Numar Imprumuturi"
FROM rental
WHERE TO_CHAR(book_date, 'dd') = '02' AND TO_CHAR(book_date, 'mm.yyyy') = TO_CHAR(sysdate, 'mm.yyyy');

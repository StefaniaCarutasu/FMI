<< principal >> DECLARE
    v_client_id       NUMBER(4) := 1600;
    v_client_nume     VARCHAR2(50) := 'N1';
    v_nou_client_id   NUMBER(3) := 500;
BEGIN
    << secundar >> DECLARE
        v_client_id         NUMBER(4) := 0;
        v_client_nume       VARCHAR2(50) := 'N2';
        v_nou_client_id     NUMBER(3) := 300;
        v_nou_client_nume   VARCHAR2(50) := 'N3';
    BEGIN
        v_client_id := v_nou_client_id;
        principal.v_client_nume := v_client_nume
                                   || ' '
                                   || v_nou_client_nume;
--pozi?ia 1
    END;

    v_client_id := ( v_client_id * 12 ) / 10;
--pozi?ia 2
END;
/
BEGIN
    dbms_output.put_line('Invat PL/SQL');
END;
/

VARIABLE g_mesaj VARCHAR2(50)
BEGIN
:g_mesaj := 'Invat PL/SQL';
END;
/
PRINT g_mesaj

--4
DECLARE
    v_dep departments.department_name%TYPE;
BEGIN
    SELECT
        department_name
    INTO v_dep
    FROM
        employees     e,
        departments   d
    WHERE
        e.department_id = d.department_id
    GROUP BY
        department_name
    HAVING
        COUNT(*) = (
            SELECT
                MAX(COUNT(*))
            FROM
                employees
            GROUP BY
                department_id
        );

    dbms_output.put_line('Departamentul ' || v_dep);
END;
/

--5
DECLARE
rezultat VARCHAR2(35);
nrAng NUMBER(3);

BEGIN
    SELECT
        department_name,
        COUNT(employee_id)
    INTO
        :rezultat,
        :nrAng
    FROM
        employees     e,
        departments   d
    WHERE
        e.department_id = d.department_id
    GROUP BY
        department_name
    HAVING
        COUNT(*) = (
            SELECT
                MAX(COUNT(*))
            FROM
                employees
            GROUP BY
                department_id
        );

    dbms_output.put_line('Departamentul ' || :rezultat);
    dbms_output.put_line('Nr Angajati ' || :nrAng);
END;
/

--7
SET VERIFY OFF

DECLARE
    v_cod             employees.employee_id%TYPE := &p_cod;
    v_bonus           NUMBER(8);
    v_salariu_anual   NUMBER(8);
BEGIN
    SELECT
        salary * 12
    INTO v_salariu_anual
    FROM
        employees
    WHERE
        employee_id = v_cod;

    IF v_salariu_anual >= 200001 THEN
        v_bonus := 20000;
    ELSIF v_salariu_anual BETWEEN 100001 AND 200000 THEN
        v_bonus := 10000;
    ELSE
        v_bonus := 5000;
    END IF;

    dbms_output.put_line('Bonusul este ' || v_bonus);
END;
/

SET VERIFY ON

--8
DECLARE
    v_cod             employees.employee_id%TYPE := &p_cod;
    v_bonus           NUMBER(8);
    v_salariu_anual   NUMBER(8);
BEGIN
    SELECT
        salary * 12
    INTO v_salariu_anual
    FROM
        employees
    WHERE
        employee_id = v_cod;

    CASE
        WHEN v_salariu_anual >= 200001 THEN
            v_bonus := 20000;
        WHEN v_salariu_anual BETWEEN 100001 AND 200000 THEN
            v_bonus := 10000;
        ELSE
            v_bonus := 5000;
    END CASE;

    dbms_doutput.put_line('Bonusul este ' || v_bonus);
END;
/

--9
DEFINE p_cod_sal = 200

DEFINE p_cod_dept = 80

DEFINE p_procent = 20

DECLARE
    v_cod_sal    emp_sca.employee_id%TYPE := &p_cod_sal;
    v_cod_dept   emp_sca.department_id%TYPE := &p_cod_dept;
    v_procent    NUMBER(8) := &p_procent;
BEGIN
    UPDATE emp_sca
    SET
        department_id = v_cod_dept,
        salary = salary + ( salary * v_procent / 100 )
    WHERE
        employee_id = v_cod_sal;

    IF SQL%rowcount = 0 THEN
        dbms_output.put_line('Nu exista un angajat cu acest cod');
    ELSE
        dbms_output.put_line('Actualizare realizata');
    END IF;

END;
/
ROLLBACK;


--1
DECLARE
    numar    NUMBER(3) := 100;
    mesaj1   VARCHAR2(255) := 'text 1';
    mesaj2   VARCHAR2(255) := 'text 2';
BEGIN
    DECLARE
        numar    NUMBER(3) := 1;
        mesaj1   VARCHAR2(255) := 'text 2';
        mesaj2   VARCHAR2(255) := 'text 3';
    BEGIN
        numar := numar + 1;
        mesaj2 := mesaj2 || ' adaugat in sub-bloc';
        
    END;
    
    numar := numar + 1;
    mesaj1 := mesaj1 || ' adaugat un blocul principal';
    mesaj2 := mesaj2 || ' adaugat in blocul principal';
    
END;
/
--a: 2
--b: text 2
--c: text 3 adaugat in sub-bloc
--c: la inceputul blocului este 100 si dupa executia numar := numar + 1 are valoarea 101
--d: la inceputul blocului are valoarea text 1 si apoi valoarea text 1 adaugat in blocul principal
--e: la inceputul bloului are valoarea text 2 si la finalul blocului are valoarea text 2 adaugat in blocul principal


--2
--a
SELECT
    to_char(book_date, 'dd'),
    COUNT(*)
FROM
    rental
WHERE
    to_char(book_date, 'mm') = '10'
    AND to_char(book_date, 'yyyy') = to_char(sysdate, 'yyyy')
GROUP BY
    to_char(book_date, 'dd');

--b
CREATE TABLE octombrie_sca
    AS
        SELECT
            to_char(book_date, 'dd') Data,
            COUNT(*) NrImp
        FROM
            rental
        WHERE
            to_char(book_date, 'mm') = '10'
            AND to_char(book_date, 'yyyy') = to_char(sysdate, 'yyyy')
        GROUP BY
            to_char(book_date, 'dd');
drop table octombrie_sca;

CREATE TABLE octombrie_sca (
    id     NUMBER(2),
    data   DATE
);

DECLARE
    var_data date;
    i number(3) := 1;
BEGIN
    while i <=31 loop
        var_data := to_date(i || 'October 2020', 'dd-mm-yy');
        INSERT INTO octombrie_sca
        VALUES (i, var_data);
        i := i + 1;
    END LOOP;
END;
/

drop table octombrie_sca;

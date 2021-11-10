--5
VARIABLE rezultat VARCHAR2(35)

BEGIN
    SELECT
        department_name
    INTO :rezultat
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
END;
/

PRINT rezultat

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

    dbms_output.put_line('Bonusul este ' || v_bonus);
END;
/

--9
DEFINE p_cod_sal = 200

DEFINE p_cod_dept = 80

DEFINE p_procent = 20
DECLARE v_cod_sal emp_sca.employee_id%TYPE:= &p_cod_sal;
v_cod_dept emp_sca.department_id%TYPE:= &p_cod_dept;
v_procent NUMBER(8):=&p_procent;
BEGIN
UPDATE emp_sca
SET
    department_id = v_cod_dept,
    salary = salary + ( salary * v_procent / 100 )
WHERE
    employee_id =
        v_cod_sal;
    IF SQL%rowcount = 0 THEN
        dbms_output.put_line('Nu exista un angajat cu acest cod');
    ELSE
        dbms_output.put_line('Actualizare realizata');
    END IF;

END;
/
ROLLBACK;

--10

CREATE TABLE zile_sca (
    id NUMBER(5) PRIMARY KEY,
    data DATE,
    nume_zi VARCHAR2(50)
);

DECLARE
    contor   NUMBER(6) := 1;
    v_data   DATE;
    maxim    NUMBER(2) := last_day(sysdate) - sysdate;
BEGIN
LOOP v_data := sysdate + contor;
INSERT
    INTO zile_sca VALUES (
    contor,
    v_data,
    to_char(v_data, 'Day')
);
    contor := contor + 1;
    EXIT WHEN contor > maxim;
END LOOP;
END;
/

select * from zile_sca;

--11
DECLARE
    contor   NUMBER(6) := 1;
    v_data   DATE;
    maxim    NUMBER(2) := last_day(sysdate) - sysdate;
BEGIN WHILE contor <= maxim LOOP v_data := sysdate + contor;
INSERT
    INTO zile_*** VALUES (
    contor,
    v_data,
    to_char(v_data, 'Day')
);
contor := contor + 1;
END loop;
END;
/
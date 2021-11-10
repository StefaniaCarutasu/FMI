--6
--sa se afiseze numele, prenumele, specializarea si salariul pentru toti medicii
--peste 40 de ani
   create or replace procedure afisare_date_medic is
        type date_medic is record 
        (nume doctor.last_name%type, prenume doctor.first_name%type, spec doctor.specialization%type, salariu doctor.salary%type);
        type v_date_medic is table of date_medic; 
        v_date v_date_medic;
    begin 
        select last_name, first_name, specialization, salary
        bulk collect into v_date
        from doctor
        where lower(specialization) != 'lab assistant' and lower(specialization) != 'anesthetist' and age > 80;
        if v_date.exists(1) then
            for i in v_date.first..v_date.last loop
                DBMS_OUTPUT.PUT_LINE ('-----------------------------');
                DBMS_OUTPUT.PUT_LINE ('Nume: ' || v_date(i).nume);
                DBMS_OUTPUT.PUT_LINE ('Prenume: ' || v_date(i).prenume);
                DBMS_OUTPUT.PUT_LINE ('Specializare: ' || v_date(i).spec);
                DBMS_OUTPUT.PUT_LINE ('Salariu: ' || v_date(i).salariu);
                DBMS_OUTPUT.PUT_LINE ('-----------------------------');
            end loop;
        else RAISE no_data_found;
        end if;
        EXCEPTION
            when no_data_found then
                DBMS_OUTPUT.PUT_LINE ('Nu exista astfel de medici');
             when others then
                DBMS_OUTPUT.PUT_LINE ('Alta eroare!');   
    end afisare_date_medic;
    /
   
    EXECUTE afisare_date_medic;

--7
--Sa se afiseze informatii din tabelul OPERATION in functie de optiunea 
--data ca parametru procedurii
--pentru 1: toate datele din tabel
--pentru 2: toate operatiile care au avut loc in camera 134
--pentru 3: toate operatiile ce au avut loc in luna curenta

create or replace procedure afisare_operatii (optiune in number default 1)
is
    type op_type is ref cursor return operation%rowtype;
    v_op op_type;
    v_date operation%rowtype;
    type doc_data is record (nume_doctor doctor.last_name%type, prenume_doctor doctor.first_name%type);
    type doc_type is table of doc_data;
    v_doc doc_type;
    nume_pacient patient.last_name%type;
    prenume_pacient patient.first_name%type;
    
begin
    if optiune = 1 then
        open v_op for select * 
                      from operation;
    elsif optiune = 2 then
        open v_op for select *
                      from operation
                      where operation_room = 134;
    elsif optiune = 3 then
        open v_op for select * 
                      from operation
                      where to_char(operation_date, 'mm') = to_char(sysdate, 'mm') and to_char(operation_date, 'yyyy') = to_char(sysdate, 'yyyy');
    else
        dbms_output.put_line('Nu exista optiunea introdusa');
    end if;
        loop
            fetch v_op into v_date;
            exit when v_op%notfound;
            select last_name, first_name
            bulk collect into v_doc
            from doctor d join operation_doctor od on (d.id = od.doctor_id) 
            where od.operation_id = v_date.id;
            select last_name, first_name
            into nume_pacient, prenume_pacient
            from patient
            where id = v_date.patient_id;
            DBMS_OUTPUT.PUT_LINE('----------------------------------------------');
            for i in v_doc.first..v_doc.last loop
                DBMS_OUTPUT.PUT_LINE('Doctor: '|| v_doc(i).nume_doctor || ' ' || v_doc(i).prenume_doctor);
            end loop;
            DBMS_OUTPUT.PUT_LINE('Pacient: '||nume_pacient || ' ' || prenume_pacient);
            DBMS_OUTPUT.PUT_LINE('Ziua: '|| v_date.operation_date);
            DBMS_OUTPUT.PUT_LINE('Ora: ' || v_date.operation_time);
            DBMS_OUTPUT.PUT_LINE('----------------------------------------------');
        end loop;
        close v_op;
    EXCEPTION
        when no_data_found then
             DBMS_OUTPUT.PUT_LINE('Nu exista informatiile cerute');
        when others then
             DBMS_OUTPUT.PUT_LINE('S-a produs o eroare!');
end afisare_operatii;
/

execute afisare_operatii(2);

--8
--sa se afiseze numele medicului unui pacient al carui nume este dat 
create or replace function medic_pacient (nume_pacient in patient.last_name%type default 'Sigal') 
return doctor.last_name%type 
is
medic doctor.last_name%type;
begin
    select d.last_name
    into medic
    from doctor d join patient_doctor pd on (d.id = pd.doctor_id)
                  join patient p on (pd.pacient_id = p.id)
    where lower(p.last_name) = lower(nume_pacient);
    return medic;
    EXCEPTION
        when no_data_found then
            DBMS_OUTPUT.PUT_LINE('Nu exista un pacient cu acest nume!');
            return -1;
        when too_many_rows then
            DBMS_OUTPUT.PUT_LINE('Pacientul ' || nume_pacient || ' are mai multi doctori');
            return -1;
        when others then
            DBMS_OUTPUT.PUT_LINE('Alta eroare!');
            return -1;
end medic_pacient;
/
begin
    DBMS_OUTPUT.PUT_LINE(medic_pacient);
end;
/

--9
--se se afiseze informatii despre toti doctorii ai caror pacienti
--au fost operati in luna curenta si au fost internati luna precedenta.

create or replace procedure proc_afisare_doctori
is
cursor c_date_medic is
    select d.last_name, d.first_name, d.age, specialization, d.phone_number, d.email
    from doctor d join patient_doctor pd on (d.id = pd.doctor_id)
                  join patient p on (pd.pacient_id = p.id)
                  join operation o on (p.id = o.patient_id)
                  join patient_admission pa on (p.id = pa.pacient_id)
    where (to_char(o.operation_date, 'mm') = to_char(sysdate, 'mm') and to_number(to_char(pa.admission_date, 'mm')) = to_number(to_char(sysdate, 'mm')) - 1)
        or (to_char(o.operation_date, 'mm') = 'January' and to_char(pa.admission_date, 'mm') = 'December' and 
        to_number(to_char(o.operation_date, 'yyyy')) = to_number(to_char(pa.admission_date, 'yyyy')) + 1);
type date_doctor is record (nume doctor.last_name%type, prenume doctor.first_name%type, varsta doctor.age%type, spec doctor.specialization%type, nr_telefon doctor.phone_number%type, email doctor.email%type);
type tablou_date_doctori is table of date_doctor;
tablou_doctori tablou_date_doctori;
begin
    open c_date_medic;
    fetch c_date_medic bulk collect into tablou_doctori;
    close c_date_medic;
    if tablou_doctori.exists(1) then 
        for i in tablou_doctori.first..tablou_doctori.last loop
            DBMS_OUTPUT.PUT_LINE ('-------------------------------');
            DBMS_OUTPUT.PUT_LINE ('Nume: ' || tablou_doctori(i).nume || ' ' || tablou_doctori(i).prenume);
            DBMS_OUTPUT.PUT_LINE ('Varsta: ' || tablou_doctori(i).varsta);
            DBMS_OUTPUT.PUT_LINE ('Specializare: ' || tablou_doctori(i).spec);
            DBMS_OUTPUT.PUT_LINE ('Numar telefon: ' || tablou_doctori(i).nr_telefon);
            DBMS_OUTPUT.PUT_LINE ('Adresa email: ' || tablou_doctori(i).email);
            DBMS_OUTPUT.PUT_LINE ('-------------------------------');
        end loop;
    else raise no_data_found;
    end if;
    EXCEPTION
        when no_data_found then
            DBMS_OUTPUT.PUT_LINE ('Nu exista medici cu pacienti operati luna curenta si internati luna precedenta');
        when others then
            DBMS_OUTPUT.PUT_LINE ('Alta eroare!');
end proc_afisare_doctori;
/


EXECUTE proc_afisare_doctori;

--TRIGGERS
--10
--triggerul se va declansa daca se incearca adaugarea de operatii noi de Craciun sau in weekend
create or replace trigger restrictionare_operatii
    before insert or update or delete on operation
begin
    if (to_char(sysdate, 'dd') = 25) and (to_char(sysdate, 'mm') = 12)
        then raise_application_error(-20001, 'Nu se efectueaza operatii de Craciun');
    elsif (to_char(sysdate,'D') = 1) OR (to_char(sysdate,'D') = 7)
        then raise_application_error(-20002, 'Nu se efectueaza operatii in weekend');
    end if;
end;
/

--11
--trigger-ul se va declansa cand se va incerca scaderea salariului unui medic cu varsta mai mare de 50 de ani
create or replace trigger modif_salariu
before update of salary on doctor
FOR EACH ROW
declare
exceptie EXCEPTION;
begin
    if :OLD.salary > :NEW.salary and :NEW.age >= 50 then 
        raise exceptie;
    end if;
   EXCEPTION
WHEN exceptie THEN
RAISE_APPLICATION_ERROR (-20003, 'Nu puteti scadea salariul unui doctor cu varsta mai mare de 50 de ani'); 
end;
/

--12
create table audit_orcldb 
    (event_user varchar2(30),
    db_name varchar2(30),
    event varchar2(20),
    object_name varchar2(30),
    event_date date);

create or replace trigger insert_event
    after create or alter or drop on schema
begin
    insert into audit_orcldb
    values (sys.login_user, sys.database_name, sys.sysevent, sys.dictionary_obj_name, sysdate);
end;
/

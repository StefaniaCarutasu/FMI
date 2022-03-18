declare 
    ang emp_sca%rowtype;
    TYPE tab_ind IS TABLE OF emp_sca%rowtype INDEX BY PLS_INTEGER;
    t    tab_ind; 
    maxim emp_sca.employee_id%type;
    minim emp_sca.employee_id%type;
    j number(5) := 0;
begin
   select min(employee_id) into minim from emp_sca;
   select max(employee_id) into maxim from emp_sca;
   
   for i in minim..maxim loop
        select *
        into ang
        from emp_sca
        where employee_id = i;
        if ang.commission_pct is not null then
            t(j) := ang;
            j := j+1;
        end if;
    end loop;
    
    for j in t.first..t.last loop
        delete from emp_sca
        where employee_id = t(j).employee_id;
     end loop;
end;
/

select * from emp_sca;

declare 
    type tab_ind is table of emp_sca%rowtype
                index by binary_integer;
    t   tab_ind;
begin
    delete from emp_sca
    where commission_pct is not null
    returning employee_id, first_name, last_name, email, phone_number, hire_date, job_id,
              salary, commission_pct, manager_id, department_id
    bulk collect into t;
    for i in t.first..t.last loop
        dbms_output.put_line(t(i).employee_id || ' ' || t(i).first_name || ' ' || t(i).last_name || ' ' ||
                             t(i).email || ' ' || t(i).phone_number || ' ' || t(i).hire_date || ' ' ||
                             t(i).job_id || ' ' || t(i).salary || ' ' || t(i).commission_pct || ' ' || 
                             t(i).manager_id || ' ' || t(i).department_id);
    end loop;
end;
/
rollback;

desc emp_sca;






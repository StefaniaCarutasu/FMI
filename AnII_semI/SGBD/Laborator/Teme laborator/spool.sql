SPOOL E:\transfer\Facultate\FMI\AnII_semI\SGBD\Laborator\inserareDepartamente.sql;
SET FEEDBACK OFF;
SET PAGESIZE 0;
SELECT 'INSERT INTO' || table_name || 'SELECT * FROM departments'
FROM user_tables 
WHERE UPPER(table_name) = 'DEP_SCA';
SPOOL OFF;

select * from dep_sca;

SPOOL inserareDepartamente.sql;
SET FEEDBACK OFF;
SET PAGESIZE 0;
SELECT 'INSERT INTO' || table_name || 'VALUES (1, 'DEP', 1, 1)';
FROM user_tables 
WHERE UPPER(table_name) = 'DEP_SCA';
SPOOL OFF;
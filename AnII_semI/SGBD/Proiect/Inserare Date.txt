--inserare in ROOM
insert into room
values (123, 1, 'Ward', 'Full');
insert into room
values (124, 1, 'Ward', 'Empty');
insert into room
values (134, 3, 'Operation Room', 'Empty');
insert into room
values (135, 3, 'Operation Room', 'Full');
insert into room
values (101, 0, 'ER', '-');
alter table room
add beds_number number(2);
insert into room
values (125, 1, 'Ward', 'Available', 3);

--inserare in ADDRESS
insert into address
values(1, 'Romania', 'Bucharest', '012345', 'Teiul Doamnei', 7, 2, 5);
insert into address
values(2, 'Romania', 'Bucharest', '012346', 'Regina Elisabeta', 5, 1, 3);
insert into address
values(3, 'Romania', 'Bucharest', '013345', 'Grigore Ionescu', 43, 8, 36);
insert into address
values(4, 'Romania', 'Bucharest', '012445', 'Otesani', 3, 0, 1);
insert into address
values(5, 'Romania', 'Bucharest', '112345', 'Dristorului', 10, 6, 20);
insert into address
values(6, 'Romania', 'Bucharest', '222345', 'Ion Alexe', 23, 4, 13);
insert into address
values(7, 'Romania', 'Bucharest', '012355', 'Grigore Ionescu', 7, 2, 5);
insert into address
values(8, 'Romania', 'Bucharest', '012355', 'Grigore Ionescu', 73, 5, 20)
insert into address
values(9, 'Romania', 'Bucharest', '222345', 'Ion Alexe', 41, 4, 13);
insert into address
values(10, 'Romania', 'Bucharest', '012345', 'Teiul Doamnei', 44, 7, 21);

--inserare PACIENT
insert into pacient
values (100, 'King', 'Steven', 34, 'Male', '0723', 'stevenking@gmail.com', 123, 1);
insert into pacient
values (101, 'Ernst', 'Bruce', 22, 'Male', '0724', 'bruceernst@gmail.com', 123, 2);
insert into pacient
values (102, 'Popp', 'Louise', 55, 'Female', '0725', 'popplouise@gmail.com', 124, 3);
insert into pacient
values (103, 'King', 'Nancy', 30, 'Female', '0726', 'nancyking@gmail.com', 124, 1);
insert into pacient
values (104, 'Sigal', 'Tobias', 18, 'Male', '0727', 'tobiassigal@gmail.com', 124, 6);\
insert into pacient
values (105, 'Khan', 'Elena', 21, 'Female', '0787', 'elenakhan@gmail.com', 125, 10);

--inserare DOCTOR
insert into doctor
values (200, 'Lorentz', 'Andrew',  40, 'Cardiology', '0727', 'andrewlorentz@gmail.com', 5);
insert into doctor
values (201, 'Ernst', 'Anna',  55, 'Pediatrics', '0728', 'anaernst@gmail.com', 2);
insert into doctor
values (202, 'Lorentz', 'Jhon',  28, 'Orthopaedics', '0729', 'jhonlorentz@gmail.com', 5);
insert into doctor
values (203, 'Sigal', 'Ana',  65, 'Radiology', '0733', 'anasigal@gmail.com', 6);
insert into doctor
values (204, 'Hall', 'Peter',  40, 'Dermatology', '0734', 'peterhall@gmail.com', 7);
insert into doctor
values (205, 'Popp', 'Andrew',  56, 'Lab assistant', '0747', 'andrewpopp@gmail.com', 3);
insert into doctor
values (206, 'Grant', 'Douglas',  25, 'Lab assistant', '0749', 'douglasgrant@gmail.com', 8);
insert into doctor
values (207, 'Grant', 'Tina',  26, 'Lab assistant', '0750', 'tinagrant@gmail.com', 8);
insert into doctor
values (208, 'Higgins', 'Shelly',  40, 'Anesthetist', '0799', 'shellyhiggins@gmail.com', 9)

update doctor
set salary = 5000
where lower(specialization) != lower('Lab assistant') and lower(specialization) != lower('Anesthetist');
update doctor
set salary = 4500
where lower(specialization) = 'lab assistant';
update doctor
set salary = 4200
where lower(specialization) = 'anesthetist';

--inserare LABORATORY
insert into laboratory
values (1234, 205);
insert into laboratory
values (1235, 205);
insert into laboratory
values (1236, 206);
insert into laboratory
values (1237, 206);
insert into laboratory
values (1238, 207);100

--inserare LAB_TESTS
insert into lab_tests
values (100, 204, 1234, 'Iritation', 'Negative', to_date('10 May 2020'));
insert into lab_tests
values (101, 200, 1234, 'Palpitaions', 'Pozitive', to_date('19 July 2020'));
insert into lab_tests
values (101, 200, 1235, 'Palpitaions', 'Negative', '27 July 2020');
insert into lab_tests
values (101, 200, 1235, 'Palpitaions', 'Negative', '27 July 2020');
insert into lab_tests
values (104, 202, 1236, 'Broken arm', 'Pozitive', '27 July 2020');
insert into lab_tests
values (104, 202, 1236, 'Broken arm', 'Negative', '27 October 2020');

--inserare OPERATION
insert into operation
values (1, 104, 134, '18 June 2020', '17;45');
insert into operation
values (2, 104, 134, '20 June 2020', '18:00');
insert into operation
values (3, 101, 135, '21 July 2020', '09:00');
insert into operation 
values (4, 103, 135, '23 July 2020', '09:00');
insert into operation 
values (5, 102, 135, '23 July 2020', '10:45');
insert into operation 
values (6, 105, 135, '3-December-2020', '12:00');

--inserare PACIENT_ADMISSION
insert into pacient_admission
values (104, 124, '17-June-2020', '25-June-2020');
insert into pacient_admission
values (101, 123, '20-July-2020', '25-July-2020');
insert into pacient_admission
values (103, 124, '23-July-2020', '24-July-2020');
insert into pacient_admission (pacient_id, room_id, admission_date)
values (102, 124, '08-December-2020');
insert into pacient_admission (pacient_id, room_id, admission_date)
values (104, 124, '08-December-2020');
insert into pacient_admission (pacient_id, room_id, admission_date)
values (105, 124, '30-November-2020');

--inserare PACIENT_DOCTOR
insert into pacient_doctor
values (100, 200);
insert into pacient_doctor
values (100, 204);
insert into pacient_doctor
values (101, 200);
insert into pacient_doctor
values (101, 202);
insert into pacient_doctor
values (101, 204);
insert into pacient_doctor
values (102, 200);
insert into pacient_doctor
values (102, 204);
insert into pacient_doctor
values (103, 202);
insert into pacient_doctor
values (103, 204);
insert into pacient_doctor
values (104, 200);
insert into pacient_doctor
values (104, 204);
insert into pacient_doctor
values (105, 204);
insert into pacient_doctor
values (105, 200);

--inserare OPERATION_DOCTOR
insert into operation_doctor values
(200, 1);
insert into operation_doctor values
(205, 1);
insert into operation_doctor values
(208, 1);

insert into operation_doctor values
(202, 2);
insert into operation_doctor values
(207, 2);
insert into operation_doctor values
(208, 2);

insert into operation_doctor values
(202, 3);
insert into operation_doctor values
(204, 3);
insert into operation_doctor values
(208, 3);

insert into operation_doctor values
(200, 4);
insert into operation_doctor values
(208, 4);

insert into operation_doctor values
(200, 5);
insert into operation_doctor values
(208, 5);

insert into operation_doctor values
(200, 6);
insert into operation_doctor values
(208, 6);
--creare PATIENT
CREATE TABLE patient (
id number(5) primary key,
last_name varchar2(25) not null,
first_name varchar2(25) not null,
age number(3) not null,
gender varchar2(15) not null,
phone_number varchar2(10) not null,
email varchar2(20),
address varchar2(40));

alter table pacient
modify email varchar2(30);

alter table patient
drop column room_id;

--creare DOCTOR
create table doctor(
id number(5) primary key,
last_name varchar2(25),
first_name varchar2(25),
age number(3),
specialization varchar2(25),
phone_number varchar2(10),
email varchar2(20),
address varchar2(40));

--creare TABEL ASOCIATIV
create table pacient_doctor (
pacient_id number(5),
doctor_id number(5)); 

alter table pacient_doctor
add constraint pd_fk FOREIGN KEY (pacient_id) REFERENCES pacient(id) on delete cascade;

alter table pacient_doctor
add constraint pd_fk_doctor FOREIGN KEY (doctor_id) REFERENCES doctor(id) on delete cascade;

create table laboratory (
id number(5) primary key,
lab_assistant varchar2(40) not null);

create table lab_results (
pacient_id number(5),
doctor_id number(5),
lab_id number(5),
tested_for varchar2(25),
restult varchar2(15),
test_date date,
FOREIGN KEY (pacient_id) references pacient(id),
FOREIGN KEY (doctor_id) references doctor(id),
FOREIGN KEY (lab_id) references laboratory(id));

alter table lab_results
add constraint pk_lab_results primary key (pacient_id, doctor_id, lab_id);

create table room (
id NUMBER(4) primary key,
floor number(2) not null,
type varchar2(20),
status varchar2(20) not null);

alter table pacient
add room_id number(4);

alter table pacient
add constraint room_fk FOREIGN KEY (room_id) REFERENCES room(id) on delete cascade;

ALTER TABLE room
ADD beds_number number(2);
update room
set beds_number = 3
where id = 124;

alter table pacient
add room_id number(4);

alter table pacient
add constraint room_fk FOREIGN KEY (room_id) REFERENCES room(id) on delete cascade;

create table lab_tests (
pacient_id number(5),
doctor_id number(5),
lab_id number(5),
tested_for varchar2(30),
test_result varchar2(30),
test_date date,
FOREIGN key (pacient_id) references pacient(id),
FOREIGN key (doctor_id) references doctor(id),
FOREIGN key (lab_id) references laboratory(id));

alter table laboratory
modify lab_assistant number(5);

alter table laboratory
add constraint lab_assistant_fk FOREIGN KEY (lab_assistant) references doctor(id) on delete cascade;

create table operation (
id number(5) primary key,
patient_id number(5),
operation_room NUMBER(4),
operation_date date,
operation_time varchar2(10),
foreign key (patient_id) references patient(id));

create table operation_doctor (
doctor_id number(5),
operation_id number(5),
foreign key (doctor_id) references doctor(id),
foreign key (operation_id) references operation(id));

create table pacient_admission (
pacient_id number(5),
room_id number(4),
admission_date date,
discharge_date date);

alter table pacient_doctor
add constraint pk_pd primary key (pacient_id, doctor_id);

alter table lab_tests
add constraint pk_lab_tests primary key (pacient_id, doctor_id, lab_id);

alter table operations
add constraint fk_room foreign KEY (operation_room) references room(id) on delete set null;

alter table pacient_admission
add constraint fk_p_add foreign key (pacient_id) references pacient(id) on delete cascade;

alter table pacient_admission
add constraint fk_room_add foreign key (room_id) references room(id) on delete cascade;

alter table pacient_admission
add constraint pk_admission primary key (pacient_id, room_id, admission_date);

alter table operations
add constraint pk_op primary key (pacient_id, doctor_id, operation_room, operation_date, operation_time);

SELECT * FROM session_privs
ORDER BY privilege;

alter table lab_tests
drop constraint pk_lab_tests;

alter table lab_tests
add constraint pk_lab_tests primary key (pacient_id, doctor_id, tested_for, test_date);

create table address (
id number(5) primary key,
country varchar2(25),
city varchar2(25),
postal_code varchar2(10),
street_name varchar2(25),
street_number number(4),
floor number(2),
apartment_number number(3));

alter table pacient
drop column address;

alter table pacient
add address number(5); 
alter table pacient
add constraint fk_address foreign key (address) references address(id) on delete set null;

alter table doctor
drop column address;

alter table doctor
add address number(5); 
alter table doctor
add constraint fk_address_doc foreign key (address) references address(id) on delete set null;


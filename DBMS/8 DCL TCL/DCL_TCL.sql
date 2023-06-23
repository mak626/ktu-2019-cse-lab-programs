CREATE SCHEMA `mak_tcl_dcl`;
CREATE TABLE students(
	name VARCHAR(255) ,
    rollno INT PRIMARY KEY,
    address VARCHAR(255)
);

INSERT INTO students VALUES
('MAK',1,'221B Baker Street'),
('Kevin',2,'79S Oxford Street'),
('Hendry',3,'90 Jake Street');


START TRANSACTION;
SAVEPOINT checkpoint1;
INSERT INTO students VALUES('Jacob',4,'9877 Will Street');
SELECT * FROM students;
ROLLBACK TO checkpoint1;
SELECT * FROM students;


CREATE USER 'test'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON *.* TO 'test'@'localhost' WITH GRANT OPTION;

GRANT SELECT ON mak_tcl_dcl.students to 'test'@'localhost';

REVOKE SELECT ON mak_tcl_dcl.students FROM 'test'@'localhost';

SHOW GRANTS FOR 'test'@'localhost';
DROP USER 'test'@'localhost'
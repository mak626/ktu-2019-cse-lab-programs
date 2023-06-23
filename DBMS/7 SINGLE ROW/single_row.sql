CREATE TABLE `mak_single_row`.`employee` (
  `emp_no` INT NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(45) NULL,
  `last_name` VARCHAR(45) NULL,
  `hire_date` DATE NULL,
  `salary` FLOAT NULL,
  PRIMARY KEY (`emp_no`));

INSERT into employee(first_name,last_name,hire_date,salary) VALUES
("Aswin","Kishore",'2021-09-12',30000);

INSERT into employee(first_name,last_name,hire_date,salary) VALUES
("Victor","Hellsing",'2021-10-10',40000),
("Hendry","James",'2022-01-02',400000);

-- Q1
SELECT emp_no, lower(first_name) as first_name FROM employee;

-- Q2
SELECT concat(upper(left(first_name,1)), substring(first_name,2)) as first_name FROM employee;

-- Q3
SELECT first_name, length(first_name) FROM employee;

-- Q4
SELECT concat(first_name,last_name) as Name FROM employee;

-- Q5
SELECT lpad(salary,15,'$') AS "New Salary" FROM employee;

-- Q6
SELECT rpad(salary,15,'*') as "New Salary" from employee;

-- Q7
SELECT first_name,instr(first_name,'a') AS "Numeric Position" from employee;

-- Q8
SELECT first_name, substring(first_name,1,3) AS "First 3 Chars" from employee;

-- Q9
SELECT MOD(10,3) FROM DUAL;
SELECT ROUND(203.347,2) FROM DUAL;
SELECT truncate(203.347,1) FROM DUAL;
SELECT POWER(5,2) FROM DUAL;
SELECT SQRT(25) FROM DUAL;

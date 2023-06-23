CREATE TABLE `customer` (
  `cust_id` int(20) NOT NULL default '0',
  `cust_name` varchar(20) default NULL,
  `cust_hname` varchar(20) default NULL,
  `cust_street` varchar(20) default NULL,
  `cust_phone` int(15) default NULL,
  PRIMARY KEY  (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `item_db` (
  `item_code` int(5) NOT NULL default '0',
  `item_name` varchar(20) default NULL,
  `stock` int(5) default NULL,
  `unit_price` int(5) default NULL,
  PRIMARY KEY  (`item_code`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `order_db` (
  `order_id` int(20) default NULL,
  `cust_id` int(20) default NULL,
  `item_code` int(5) default NULL,
  `order_date` date NOT NULL,
  `expiry_date` date default NULL,
  `delivery_date` date default NULL,
  `payment_mode` char(1) default NULL,
  UNIQUE KEY `order_id` (`order_id`),
  KEY `cust_id` (`cust_id`),
  CONSTRAINT `order_db_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `customer` (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Q1
insert into customer values(1, "MAK", "221B", "Baker Stret",904998900);
insert into item_db values(1, 'Apple', 20, 47);
insert into order_db values(1, 1, 1, CURRENT_DATE(), CURRENT_DATE()+1, CURRENT_DATE(),"R"); 

-- Q2
insert into item_db values
(2, 'Mango', 60, 20),
(3, 'JackFruit', 40, 90);

insert into customer values(2, "Kash", "221A", "Chambers Street",904998940);
insert into order_db values(2, 2, 3, CURRENT_DATE(), CURRENT_DATE()+20, CURRENT_DATE()+10,"C"); 
insert into order_db values(3, 2, 3, CURRENT_DATE(), CURRENT_DATE()-1, CURRENT_DATE()+10,"C"); 


-- Q3
SELECT * FROM order_db ORDER BY delivery_date;

-- Q4
SELECT * FROM item_db ORDER BY unit_price desc;

-- Q5
SELECT * FROM order_db WHERE order_id > 1 AND order_id <7;

-- Q6
DELETE FROM order_db WHERE expiry_date < current_date();

-- Q7
CREATE TABLE test_db as SELECT * FROM item_db;

-- Q8
SELECT cust_name FROM customer WHERE cust_name LIKE "A%";

-- Q9
SELECT order_id,cust_id from order_db;

-- Q10
TRUNCATE TABLE order_db;

-- Q11
select order_id,cust_id from order_db where delivery_date BETWEEN '2021-12-01' and '2021-12-31';

-- Q12
SELECT AVG(order_qty) FROM order_db WHERE item_code=256;

-- Q13
SELECT * FROM item_db WHERE unit_price = (SELECT MAX(unit_price) FROM item_db);

-- Q14
SELECT * FROM item_db WHERE unit_price = (SELECT MIN(unit_price) FROM item_db);

-- Q15
SELECT COUNT(*) FROM order_db WHERE item_code=256;

-- Q16
SELECT COUNT(*) FROM item_db WHERE unit_price BETWEEN 100 AND 200;

-- Q17
SELECT AVG(unit_price) FROM item_db;

-- Q18
select order_id AS order_code, delivery_date AS dateofdelivery FROM order_db;

-- Q19
SELECT cust_name FROM customer WHERE 
cust_name IN (SELECT cust_name FROM customer WHERE cust_name LIKE "%a%") 
AND 
cust_name IN (SELECT cust_name FROM customer WHERE cust_name LIKE "%j%");

-- Q20
SELECT MIN(LENGTH(cust_name)) FROM customer;

-- Q21
CREATE TABLE deliver_db as (SELECT * FROM order_db where cust_id is NULL);

-- Q22
SELECT * from deliver_db UNION select * from order_db;

-- Q23
SELECT e.order_id,e.cust_id,e.item_code,e.order_date,e.expiry_date,e.delivery_date from deliver_db as e
INNER JOIN 
order_db
ON e.order_id = order_db.order_id;

-- Q24
SELECT order_id FROM order_db WHERE delivery_date > current_date();

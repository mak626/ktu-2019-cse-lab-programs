-- Q1
SELECT * FROM customer c
WHERE (SELECT COUNT(cust_id) FROM customer d WHERE c.cust_street = d.cust_street) > 1
ORDER BY cust_street;

-- Q2
SELECT DISTINCT cust_id,cust_name FROM customer c
WHERE (
	SELECT COUNT(cust_id) FROM order_db d
    WHERE delivery_date IN (SELECT delivery_date FROM order_db e WHERE e.cust_id = c.cust_id) 
		  AND d.cust_id != c.cust_id
) >= 1;

-- Q3
SELECT * FROM order_db a
WHERE (
	SELECT COUNT(order_id) FROM order_db b
    WHERE a.order_date = b.order_date
) > 1
ORDER BY order_date;

-- Q4
SELECT * FROM order_db a
NATURAL JOIN item_db c
WHERE (
	SELECT COUNT(order_id) FROM order_db b 
    WHERE a.expiry_date = b.expiry_date 
) > 1 AND unit_price > 100
ORDER BY expiry_date;

-- Q5
SELECT cust_id FROM customer c
WHERE (SELECT COUNT(cust_id) FROM order_db d WHERE c.cust_id = d.cust_id) > 3;

-- Q6
SELECT * FROM order_db a
WHERE a.qty > (SELECT AVG(qty) FROM order_db b WHERE a.item_code = b.item_code);

-- Q7
SELECT * FROM order_db a
WHERE (SELECT COUNT(cust_id) FROM order_db b WHERE b.cust_id = a.cust_id) > 1
ORDER BY cust_id;

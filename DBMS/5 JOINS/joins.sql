INSERT INTO address
VALUES
(1,"221b","Baker Street","New York"),
(2,"12C","Wolfs Street","New Jersey"),
(3,"41b","Oxford Street","London");

INSERT into category
VALUES
(1,"novel"),
(2,"language"),
(3,"biography");

INSERT into publisher
VALUES
(1,"hills",1),
(2,"cbse",2);

insert into author
values
(1,"Aswin",762783682,"www.aswin.com",1),
(2,"Yack",76223482,"www.yack.com",2),
(3,"Hella",922783682,"www.hella.com",3);

INSERT into rating
values
(1,1,8),
(2,2,5),
(3,3,10);

INSErt into book
VALUES
(1,37828328,"Wings Of Fire",1,2600,2,1,1),
(2,21228328,"Fault in our starts",3,300,2,1,2);

SELECT city,phone,url FROM author
INNER JOIN address on author.author_id = address.address_id
WHERE name is NOT NULL;

SELECT name,concat_ws(',',houseno,street,city) as address, phone
FROM publisher
INNER JOIN address on publisher.address_id = address.address_id
WHERE city = 'New York';

SELECT title,price FROM book
WHERE page_count = 2600;

SELECT ISBN,title,price FROM book
INNER JOIN category on book.category_id = category.category_id
WHERE category.name = "novel" OR category.name = "language";

SELECT title,price FROM book
INNER JOIN publisher on book.publisher_id = publisher.publisher_id 
WHERE publisher.name = "hills";

SELECT title as 'Book Title', rating FROM BOOK
INNER JOIN rating on book.rating_id = rating.rating_id;
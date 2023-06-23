CREATE DATABASE  IF NOT EXISTS `mak_correlated_sub_query` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `mak_correlated_sub_query`;
-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: localhost    Database: mak_correlated_sub_query
-- ------------------------------------------------------
-- Server version	8.0.27

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `cust_id` int NOT NULL DEFAULT '0',
  `cust_name` varchar(20) DEFAULT NULL,
  `cust_hname` varchar(20) DEFAULT NULL,
  `cust_street` varchar(20) DEFAULT NULL,
  `cust_phone` int DEFAULT NULL,
  PRIMARY KEY (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'MAK','221B','Bakers Street',904998900),(2,'Kash','221A','Chambers Street',904998940),(3,'Yakov','44B','Bakers Street',803998440);
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `item_db`
--

DROP TABLE IF EXISTS `item_db`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `item_db` (
  `item_code` int NOT NULL DEFAULT '0',
  `item_name` varchar(20) DEFAULT NULL,
  `stock` int DEFAULT NULL,
  `unit_price` int DEFAULT NULL,
  PRIMARY KEY (`item_code`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `item_db`
--

LOCK TABLES `item_db` WRITE;
/*!40000 ALTER TABLE `item_db` DISABLE KEYS */;
INSERT INTO `item_db` VALUES (1,'Apple',20,47),(2,'Mango',60,120),(3,'JackFruit',40,90);
/*!40000 ALTER TABLE `item_db` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_db`
--

DROP TABLE IF EXISTS `order_db`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_db` (
  `order_id` int DEFAULT NULL,
  `cust_id` int DEFAULT NULL,
  `item_code` int DEFAULT NULL,
  `order_date` date NOT NULL,
  `expiry_date` date DEFAULT NULL,
  `delivery_date` date DEFAULT NULL,
  `payment_mode` char(1) DEFAULT NULL,
  `qty` int DEFAULT '1',
  UNIQUE KEY `order_id` (`order_id`),
  KEY `cust_id` (`cust_id`),
  CONSTRAINT `order_db_ibfk_1` FOREIGN KEY (`cust_id`) REFERENCES `customer` (`cust_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_db`
--

LOCK TABLES `order_db` WRITE;
/*!40000 ALTER TABLE `order_db` DISABLE KEYS */;
INSERT INTO `order_db` VALUES (1,1,1,'2022-02-13','2022-02-14','2022-02-13','R',3),(2,2,3,'2022-02-13','2022-02-23','2022-02-23','C',1),(3,2,3,'2022-02-13','2022-02-12','2022-02-23','C',1),(4,2,2,'2022-02-13','2022-02-12','2022-02-13','R',1),(5,3,1,'2022-02-12','2022-02-23','2022-02-23','R',1),(6,3,2,'2022-02-10','2022-02-12','2022-02-23','R',1),(7,2,1,'2022-02-14','2022-02-17','2022-02-26','R',1);
/*!40000 ALTER TABLE `order_db` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'mak_correlated_sub_query'
--

--
-- Dumping routines for database 'mak_correlated_sub_query'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-13 16:05:57

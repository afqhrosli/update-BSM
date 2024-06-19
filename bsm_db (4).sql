-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 19, 2024 at 10:10 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.1.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bsm_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `book`
--

CREATE TABLE `book` (
  `bookID` int(100) NOT NULL,
  `title` varchar(1000) NOT NULL,
  `author` varchar(1000) NOT NULL,
  `genre` varchar(1000) NOT NULL,
  `publisher` varchar(100) DEFAULT NULL,
  `priceBook` float(4,2) NOT NULL,
  `quantityOfStock` int(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `book`
--

INSERT INTO `book` (`bookID`, `title`, `author`, `genre`, `publisher`, `priceBook`, `quantityOfStock`) VALUES
(4, 'AKU BENCI KAU', 'IKMAL ILHAM', 'love', 'TIGA SDN BHD', 23.00, 50),
(23, 'The Hunger Games', 'Suzanne Collins', 'Thriller', 'Scholastic', 50.00, 8),
(25, 'The Midnight Library', 'Matt Haig', 'fiction, fantasy', 'Conangate Books', 50.40, 100),
(26, 'When I Was A Kid 5', 'Boey', 'funny and honest', 'Last Gasp, US', 20.00, 2);

-- --------------------------------------------------------

--
-- Table structure for table `member`
--

CREATE TABLE `member` (
  `MembersID` int(20) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(15) NOT NULL,
  `fullname` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `address` varchar(100) NOT NULL,
  `phoneNum` int(12) NOT NULL,
  `gender` varchar(10) NOT NULL,
  `role` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `member`
--

INSERT INTO `member` (`MembersID`, `username`, `password`, `fullname`, `email`, `address`, `phoneNum`, `gender`, `role`) VALUES
(2, 'syaza', 'syaza@12', 'KU SYAZA KARMILA', 'syaza12@gmail.com', 'no 65 lorong melati KL', 1167954624, 'f', 0),
(3, 'hamka', 'hamka123', 'hamka', 'hamka01@gmail.com', 'melati hidup jalan tunggal KL', 11586242, 'm', 0),
(4, 'MIKAIL', 'hamka@12', 'KU HAMKA MIKAIL', 'hamka12@gmail.com', 'no 14 jalan melawati 45000 KL', 1158796472, 'M', 0),
(5, 'rab', 'Rabiatul123', 'rabiatul', 'rabnajwa@gmail.com', 'b158 kedah', 1110615723, 'female', 2),
(7, 'yana', 'yana123456', 'liyana', 'yana@gmail.com', 'sungai petani, kedah', 123456789, 'female', 2);

-- --------------------------------------------------------

--
-- Table structure for table `order`
--

CREATE TABLE `order` (
  `orderID` int(25) NOT NULL,
  `quantity` int(25) NOT NULL,
  `totalprice` float(6,2) NOT NULL,
  `price` float(6,2) NOT NULL,
  `bookID` int(100) NOT NULL,
  `orderDate` date NOT NULL,
  `userID` int(100) NOT NULL,
  `status` varchar(255) DEFAULT 'UNPAID'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `order`
--

INSERT INTO `order` (`orderID`, `quantity`, `totalprice`, `price`, `bookID`, `orderDate`, `userID`, `status`) VALUES
(1, 2, 100.00, 50.00, 23, '2024-06-09', 10, 'paid'),
(2, 2, 100.00, 50.00, 23, '2024-06-09', 10, 'paid'),
(9, 7, 196.00, 28.00, 5, '2024-06-09', 12, 'UNPAID'),
(11, 5, 250.00, 50.00, 23, '2024-06-10', 12, 'UNPAID'),
(15, 2, 40.00, 20.00, 26, '2024-06-16', 10, 'paid'),
(16, 3, 60.00, 20.00, 26, '2024-06-20', 10, 'paid');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `paymentID` int(100) NOT NULL,
  `billDate` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `amount` decimal(10,2) NOT NULL,
  `userID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`paymentID`, `billDate`, `amount`, `userID`) VALUES
(1, '2024-06-19 20:09:32', 660.00, 10);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `userID` int(15) NOT NULL,
  `username` varchar(20) NOT NULL,
  `password` varchar(15) NOT NULL,
  `name` varchar(50) NOT NULL,
  `age` int(100) NOT NULL,
  `gender` varchar(50) NOT NULL,
  `phoneNum` int(12) NOT NULL,
  `email` varchar(255) NOT NULL,
  `employmentStartDate` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `role` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`userID`, `username`, `password`, `name`, `age`, `gender`, `phoneNum`, `email`, `employmentStartDate`, `role`) VALUES
(6, 'afiqah1234', 'afiqah1234', 'afiqahh', 23, 'F', 182694241, 'afiqah1789@gmail.com', '2024-05-28 16:55:16', 1),
(9, 'hamka', '123', 'ku hamka', 25, 'm', 125794683, 'hamka12@gmail.com', '2024-06-19 19:12:02', 1),
(10, 'hafiz', '123', 'hafizuddin', 25, 'f', 157512622, 'buh12@gmail.com', '2024-06-19 19:13:11', 2),
(12, 'liyana', 'liyana123', 'liyana', 25, 'female', 113784654, 'liyana123@gmail.com', '2024-05-29 16:34:13', 2),
(13, 'zurina', 'zurinaahmad12', 'ku zurina', 25, 'female', 1134876592, 'zurina1504@gmail.com', '2024-06-13 17:18:28', 3),
(14, 'zunaidah', 'zunaidah12', 'ku zunaidah', 21, 'female', 15348674, 'zunaidah12@gmail.com', '2024-06-19 17:25:05', 2),
(15, 'zainiahmad12', 'zainiahmad12', 'ku zaini bt ku ahmad', 21, 'female', 216789536, 'zaini12@gmail.com', '2024-06-16 17:19:14', 3),
(16, 'zaimahahmad12', 'zaimahahmad12', 'ku zaimah bt ku ahmad', 25, 'female', 14689357, 'zaimah12@gmail.com', '2024-06-17 17:19:22', 3);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `book`
--
ALTER TABLE `book`
  ADD PRIMARY KEY (`bookID`);

--
-- Indexes for table `member`
--
ALTER TABLE `member`
  ADD PRIMARY KEY (`MembersID`);

--
-- Indexes for table `order`
--
ALTER TABLE `order`
  ADD PRIMARY KEY (`orderID`),
  ADD KEY `memberID` (`userID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`paymentID`),
  ADD KEY `user` (`userID`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`userID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `book`
--
ALTER TABLE `book`
  MODIFY `bookID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- AUTO_INCREMENT for table `member`
--
ALTER TABLE `member`
  MODIFY `MembersID` int(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT for table `order`
--
ALTER TABLE `order`
  MODIFY `orderID` int(25) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `paymentID` int(100) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `userID` int(15) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `order`
--
ALTER TABLE `order`
  ADD CONSTRAINT `memberID` FOREIGN KEY (`userID`) REFERENCES `user` (`userID`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `user` FOREIGN KEY (`userID`) REFERENCES `user` (`userID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

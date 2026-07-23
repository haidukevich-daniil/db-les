# Forest Database Management System

## Overview

This project implements two C applications for managing and querying a forest database stored in binary files.

- **db_builder** – creates or updates the database from a text file or generates random test data.
- **db_shell** – provides an interactive interface for querying the database without loading it into memory.

The database consists of two binary files:

- `database.dat` – stores forest records.
- `database.idx` – stores a disk-based binary search tree index.

## Features

- Create and update binary databases
- Generate random test data
- Display database statistics (`STATS`)
- Find all records by planting year (`FIND`)
- Calculate the total forest area within a year range (`SUM`)
- Efficient disk-based indexing with logarithmic search performance
- Memory-efficient implementation without loading the entire database into RAM

## Technologies

- C
- Binary file I/O
- Disk-based Binary Search Tree (BST)
- Makefile

# MMN22 - C Algorithms


## Context
1. [Overview](#overview)
2. [About](#about)
3. [Features](#features)
4. [Project Structure](#project-structure)
5. [Sets](#sets)
6. [Command Syntax](#command-syntax)

## Overview

This repository, part of the C-Algorithms project by Yotam Levit, focuses on implementing and managing various algorithms in C. It includes functionalities for command dispatching, set operations, error handling, and hash map management.

## About

This project is a pocket calculator designed for performing various set operations. It allows users to input commands to manipulate sets, including union, intersection, subtraction, and symmetric difference. The project provides a robust and efficient way to handle these operations through a command-line interface.


## Features

- **Command Dispatcher:** Executes commands based on user input.
- **Set Operations:** Supports union, intersection, subtraction, and symmetric difference.
- **Error Handling:** Robust error management.
- **Hash Map:** Custom implementation for efficient data handling.
- **Set Map Initialization:** Predefined sets for operations.

## Project Structure

* main.c: The main entry point of the program.
* set.c & set.h: Functions and definitions for set operations.
* Errors.c & Errors.h: Error handling mechanisms.
* CommandDispatcher.c & CommandDispatcher.h: Command management and execution.
* CommandParser.c & CommandParser.h: Command parsing logic.
* HashMap.c & HashMap.h: Custom hash map implementation.
* SetMap.c & SetMap.h: Initialization of predefined sets.

```angular2html
MMN22/
├── CommandDispatcher.c
├── CommandDispatcher.h
├── CommandParser.c
├── CommandParser.h
├── Errors.c
├── Errors.h
├── HashMap.c
├── HashMap.h
├── SetMap.c
├── SetMap.h
├── main.c
├── set.c
└── set.h
```

## Sets
Currently the program has 6 Sets:
1. **SETA**
2. **SETB**
3. **SETC**
4. **SETD**
5. **SETE**
6. **SETF**


## Command Syntax

1. **Reading a Set**
   ```plaintext
   read_set set_name, value1, value2, ..., valueN, -1
   ```
   Example:
    ```plaintext
   read_set SETA, 1, 2, 8, 9, -1
   ```
2. **Printing a Set**
    ```plaintext
   print_set set_name
   ```
   Example:
    ```plaintext
   print_set SETA
   ```
3. **Union of Sets**
    ```plaintext
   union_set set_name_A, set_name_B, set_name_C
   ```
   Example:
    ```plaintext
   union_set SETA, SETB, SETC
   ```
4. **Intersection of Sets**
    ```plaintext
   intersec_set set_name_A, set_name_B, set_name_C
   ```
   Example:
    ```plaintext
   intersec_set SETA, SETB, SETC
   ```
5. **Subtraction of Sets**
    ```plaintext
   sub_set set_name_A, set_name_B, set_name_C
   ```
   Example:
    ```plaintext
   sub_set SETA, SETB, SETC
   ```
6. **Symmetric Difference of Sets**
    ```plaintext
   symdiff_set set_name_A, set_name_B, set_name_C
   ```
   Example:
    ```plaintext
   symdiff_set SETA, SETB, SETC
   ```
7. **Stop**
    ```plaintext
   stop
   ```

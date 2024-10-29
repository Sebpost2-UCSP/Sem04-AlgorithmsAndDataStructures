# Sem04-AlgorithmsAndDataStructures

### Course Overview
This repository contains assignments and projects for the **Algorithms and Data Structures** course taken in my fourth semester. The course focused on understanding different data structures, their applications, and best practices for using them in problem-solving scenarios. Each assignment demonstrates the practical use of data structures like hash tables, trees, graphs, and stacks.

### Learning Outcomes
Through this course, I gained a solid understanding of:
- Implementing fundamental data structures from scratch.
- Evaluating the efficiency of data structures in various scenarios.
- Applying data structures to solve real-world problems, such as managing identifiers, handling game mechanics, and graph manipulation.

### Project and Assignments

#### 1. **HASH DNI.cpp**
   - **Description**: Implemented a hash table using the **DNI** (Documento Nacional de Identidad), a unique identifier for individuals in Peru, as the key.
   - **Features**:
     - Custom hash function designed to work efficiently with DNI numbers.
     - Efficient insertion, search, and deletion operations.
     - Collision handling to ensure data integrity.
   - **Purpose**: This assignment reinforced hashing concepts, demonstrating efficient data retrieval and manipulation based on unique identifiers.

#### 2. **Juego_bomba.cpp**
   - **Description**: A game where players pass an imaginary "bomb" in a circle. Players are sequentially eliminated based on random numbers until only one player remains.
   - **Features**:
     - Uses a doubly linked list to manage players in a circular queue.
     - Simulates random bomb passes and eliminates players accordingly.
   - **Purpose**: This project illustrated the use of linked lists and queues in real-world scenarios involving dynamic and sequential data processing.

#### 3. **Podar_arbol.cpp**
   - **Description**: A binary tree with a custom **pruning** function that removes nodes based on specific criteria.
   - **Features**:
     - Binary tree with methods for inserting, removing, and printing nodes.
     - Pruning algorithm that removes nodes if the binary tree structure is incomplete beyond a specific level.
   - **Purpose**: This assignment demonstrated tree structures and the concept of "pruning" a tree to maintain structural integrity up to a certain depth.

#### 4. **TAREA RPNv2.cpp**
   - **Description**: A program that takes an input in **Reverse Polish Notation (RPN)** and evaluates it, outputting results in RPN format.
   - **Features**:
     - Stack-based implementation to handle RPN calculations.
     - Ability to parse and compute expressions in RPN form.
   - **Purpose**: This assignment reinforced the use of stacks in evaluating mathematical expressions, especially in non-standard (RPN) formats.

#### 5. **grafos_pre.cpp**
   - **Description**: A fully implemented **graph** structure using templates, allowing for custom data types for nodes and edges.
   - **Features**:
     - Creation, insertion, and deletion of nodes and edges.
     - Flexibility to update nodes and edges dynamically.
   - **Purpose**: This project introduced the fundamentals of graph theory, covering essential operations and demonstrating how graphs can be managed and manipulated programmatically.

### Usage Instructions
To run each assignment:
1. **Compile** the `.cpp` file with a C++ compiler, such as `g++`.
   ```bash
   g++ -o output_file_name assignment_name.cpp
   ```
2. **Execute** the compiled program:
   ```bash
   ./output_file_name
   ```


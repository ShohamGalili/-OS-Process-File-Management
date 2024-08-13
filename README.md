# Student Code Verifier and Calculator

This repository contains two main projects: **ProgramChecker** and **CalculatorBuilder**, both developed in C and designed to run on Linux systems.

## ProgramChecker

### Overview
**ProgramChecker** is a tool developed to assess the correctness of programs submitted by students, ensuring they meet predefined output criteria. It leverages the Linux environment to fork processes, manage permissions, and handle files efficiently.

### Features
- **Automated File Comparison:** Automatically compares the output of students' programs with expected outputs using system-level operations.
- **Process Control:** Utilizes Linux process management to handle multiple student programs simultaneously.
- **Detailed Error Logging:** Implements comprehensive error checking and logging to manage file and process-related errors effectively.

### Getting Started
1. Navigate to the directory containing the program files:
    ```bash
    cd Desktop/OS
    ```
2. Compile the verifier program using GCC:
    ```bash
    gcc Comparison.c -o comp.out
    ```
3. Execute the program with the required file paths:
    ```bash
    ./comp.out <path-to-student-program> <path-to-expected-output>
    ```

### Paths and Configuration
The paths provided in the compilation and execution instructions are specific to my development environment. If you wish to use this tool in your environment, adjust the file paths according to where your files are located.

### Advanced Usage
To handle multiple student submissions, configure the paths in `confFile.txt`:
    ```bash
    ./comp.out <path-to-confFile.txt>
    ```
The program assumes `main.exe` exists due to prior compilation as per the instructions.

## CalculatorBuilder

### Overview
**CalculatorBuilder** consists of a straightforward calculator application capable of basic arithmetic operations such as addition, subtraction, multiplication, and division, showcasing the use of command-line arguments and basic I/O.

### Features
- **Basic Arithmetic Operations:** Supports the four fundamental arithmetic operations.
- **Command-Line Interface:** Operates entirely through the command line for input and output, enhancing its usability in educational settings.

### Getting Started
1. Navigate to the project directory:
    ```bash
    cd <path-to-calculator-builder>
    ```
2. Compile and run the server component:
    ```bash
    gcc EX2_Server.c -o EX2_Server.out
    ./server.out
    ```
3. Compile and execute the client component, specifying operations and operands:
    ```bash
    gcc EX2_Client.c -o EX2_Client.out
    ./client.out <operation> <operand1> <operand2>
    ```

### Paths and Configuration
Similar to the ProgramChecker, the paths used in this project are specific to my setup. Ensure to modify the paths in the command lines to reflect the directories and files in your environment.

## Technologies Used
- **C Programming:** Utilized for both projects to interact directly with Linux system calls.
- **Linux:** Provides a robust environment for process and file management.
- **GCC:** Used to compile the source code into executable programs.

## Process Management
The core functionality of the **ProgramChecker** revolves around creating and managing processes using the `fork` system call. This creates a parent-child (father-son) process hierarchy, where the parent process forks multiple child processes to handle concurrent execution of student programs, thereby enabling efficient multitasking and resource management within the system.

## Operating System Timer Simulation

This project simulates an operating system timer and calculates the turnaround time for various scheduling algorithms. It reads input data from a file, executes processes using different timing protocols, and computes the average turnaround time for each protocol.

### Supported Scheduling Algorithms

- **First-Come, First-Served (FCFS):** Processes are executed in the order they arrive.
- **Last-Come, First-Served Non-preemptive (LCFS-NP):** The most recently arrived process is executed next, without preemption.
- **Last-Come, First-Served Preemptive (LCFS-P):** The most recently arrived process can preempt the currently running process.
- **Shortest Job First Preemptive (SJF-P):** The process with the shortest remaining time is executed next and can preempt the current process.
- **Round Robin (RR):** Processes are executed in a cyclic order, each given a fixed time slice.

### How to Use

1. **Prepare Input Data:**
   - Ensure your input data file is formatted correctly. This file should contain the details of the processes you want to simulate.

2. **Run the Simulation:**
   - Execute the Python script from the command line, specifying the path to your input data file.
   - Example command:
     ```bash
     python simulate_timer.py input_data.txt
     ```

3. **View Results:**
   - The script will simulate process execution according to the specified algorithms and display the mean turnaround time for each scheduling protocol.

### Requirements

- **Python:** Make sure you have Python installed.
- **Libraries:**
  - `numpy` for numerical calculations
  - `tqdm` for progress bar visualization

  You can install the required libraries using pip:
  ```bash
  pip install numpy tqdm

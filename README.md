# Student Record Management

A menu-driven C application using a linked list to add, list, modify, delete, and sort student records. Each student's mark is a whole number from 1 to 100. Records are loaded from and saved to `data/students.dat` in binary format.

## Build and run

From the project directory, build with GNU Make:

```sh
make
```

Or compile directly with GCC:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src\main.c src\insert.c src\display.c src\search.c src\update.c src\delete.c src\sort.c src\file.c -o student_record_management_percentage.exe
```

Then run `.\student_record_management_percentage.exe` in Windows PowerShell.

## Run from VS Code on Windows

Install GCC and make sure `gcc` works in the VS Code terminal. Open this project folder in VS Code, then select **Terminal > Run Task... > Run Student Record Management**. The task builds the C files first and starts the interactive program in the integrated terminal.

The program expects the `data` directory to exist. It loads existing records at startup. Choose **7** to save records, or **0** and then **1** to save and exit / **2** to exit without saving. Choose **6** to sort by ID, name, or percentage in ascending order; choose **3** in the sort submenu to sort by percentage.

## Project layout

- `src/` contains the C application and its student operations.
- `include/student.h` defines the record and shared function declarations.
- `data/students.dat` stores student records.
- `src/sort.c` sorts the linked list by ID, name, or percentage.
- `src/file.c` loads and saves the linked-list records.

The binary data format is intended for use with this application and may not be portable across different compilers or platforms. The record fields stay compatible with the earlier version's ID, name, age, and mark records.

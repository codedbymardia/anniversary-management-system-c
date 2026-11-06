<CodeBlock language="markdown" editable>
# Anniversary Management System — C

Overview
A command-line application written in C to manage birthdays, anniversaries, and other important dates.

The application uses a singly linked list to manage records in memory and file handling to store information between program sessions.
Features
- Add birthdays and anniversaries
- Validate dates, including leap-year rules
- Display stored records
- Search records by category
- Find events occurring on a specific day and month
- Display events for the previous or next month
- Save and load records using a text file
Technologies and Concepts
- C Programming
- Singly Linked Lists
- Structures and Pointers
- Dynamic Memory Allocation
- File Input/Output
- Date Validation
- Menu-Driven Programming
Project Structure
- main.c — Source code
- User Documentation.pdf — Instructions for users
- Developer's Documentation.pdf — Technical explanation
Running the Application
Install a C compiler such as GCC.

From the project directory, compile the program:
gcc -Wall -Wextra -o anniversary main.c


On Windows CMD, run:
anniversary.exe


The program uses anniversaries_data.txt in the current working directory to save its records.
Academic Context
Developed as a university programming project at Budapest University of Technology and Economics (BME).
</CodeBlock>

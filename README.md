# inverted-serach

## Description
This project is a simple inverted search engine that can be used to search for words in a given text file. The project is written in C. 

## Files
- `main.c`: This is the main file that contains the main function.
- `search.c`: This file contains the functions that are used to search or traverse in the database.
- `search.h`: This file contains the function declarations for the search.c file.
- `create.c`: This file contains the functions that are used to create, and update the database.
- `create.h`: This file contains the function declarations for the create.c file.
- `file.c`: This file contains the functions that are used to read database from a file or write database to a file.
- `file.h`: This file contains the function declarations for the file.c file.
- `makefile`: This file is used to compile the project.
- `struct.h`: This file contains the structure that is used to store the database.
- `file1.txt, file2.txt`: These are some example text files that are can be used to create the database.

## How to run
To run the project, you need to have a text file that you want to search for words in. You can use the provided `file1.txt` and `file2.txt` file. To run the project, you can use the following command:
```
make
./a.out file1.txt file2.txt file3.txt
```
This will run the project and you can start adding the words into the database and searching for words.

## How to use
The project has the following operations:
- `Create database`: This will create a new database from the given file names.
- `Search`: This will search for a word in the database.
- `Display`: This will display the database.
- `Save`: This will save the database to a <.txt> file.
- `Updatr`: This will update the data in <.txt> file to the database.
- `Exit`: This will exit the program.

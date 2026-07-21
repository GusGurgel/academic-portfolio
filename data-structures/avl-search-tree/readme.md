# AVL Tree Database Search in C++ and CLI App

<p align="center" >
  <!-- Substitua o link do src pela sua imagem/gif de demonstração, se tiver -->
  <img width="600" src="./avl-search-tree-showcase.gif" alt="Project Showcase">
</p>

Implementation of the **AVL Tree** data structure in C++ using templates to index and manage a database of registered people. The program loads records from a `.csv` file and creates three distinct balanced trees (indexing by National ID, Name, and Date of Birth) to provide efficient multi-parameter searches. 

Developed for the Advanced Data Structures course at Universidade Federal do Ceará (UFC).

## Repository Documents

- [📄 Project Specification (PDF)](./projeto-buscas-arvores-avls.pdf)

## Interactive CLI Menu (`main.cpp`)

Upon executing the application, it automatically loads the `data.csv` file, builds the AVL trees, and presents an interactive terminal menu with custom-drawn tables (`GTable`).

| Menu Option | Description |
| :--- | :--- |
| `1. Search by National ID` | Searches for a specific person using their exact National ID (CPF). Returns an exact match. |
| `2. Search by Date Interval` | Finds all people born within a specific date range (`Min Date` to `Max Date`). |
| `3. Search by Name Prefix` | Retrieves all people whose names start with a specific string (e.g., searching "Mar" returns "Maria", "Marcos"). |
| `4. Show All Registered` | Displays all people currently loaded in the database in a formatted terminal table. |
| `5. Exit` | Safely terminates the application. |

## Core Technologies & Data Structures
* **Templates & Generics:** The AVL Tree (`avl_tree<T>`) is completely generic, allowing it to easily store `long long int` (IDs), `std::string` (Names), and custom `GDate` objects.
* **Prefix & Interval Traversals:** Custom tree traversal algorithms implemented using stacks (`std::stack`) to efficiently find nodes within ranges or matching prefixes without standard recursion.
* **Custom Terminal UI:** Uses a custom `GTable` class to dynamically calculate widths and render properly aligned, UTF-8 formatted tables directly in the terminal.

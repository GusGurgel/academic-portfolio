# Media Collection Manager (CLI)

<p align="center" >
  <!-- Substitua o link do src pela sua imagem/gif de demonstração, se tiver -->
  <img width="600" src="./showcase.gif" alt="Project Showcase">
</p>

A Command-Line Interface (CLI) application written in C++ for managing a collection of Media, CDs, and DVDs. The program allows users to create, list, remove, and query media files with persistent storage.

**Author:** Gustavo Gurgel Medeiros (Computer Science Student)

## 📌 Features

- **Object-Oriented Design:** Uses inheritance and polymorphism (Base class `Midia`, derived classes `CD` and `DVD`).
- **Persistent Storage:** Media items are automatically loaded from and saved to `.txt` files in the `Resources/` directory upon opening and closing the program.
- **CRUD Operations:** Create, Read (Show), and Delete media entries.
- **Advanced Queries:** Filter media by artist, year, genre, and extract unique keywords.

## 📂 Project Structure

```text
.
├── Arquivos.h / .cpp    # File management and directory traversal utilities
├── Midia.h / .cpp       # Base Media class definition
├── CD.h / .cpp          # CD class (inherits from Midia)
├── DVD.h / .cpp         # DVD class (inherits from Midia)
├── main.cpp             # Main application loop and CLI logic
├── makefile             # Compilation script
├── menu.txt             # Text file containing the main menu UI
├── out                  # Compiled executable
└── Resources/           # Directory where media data is persistently saved
    └── Backup/          # Folder for data backups
```

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (e.g., `g++`)
- `make` utility installed

### Compilation
To compile the project, simply navigate to the project directory in your terminal and run the provided makefile:
```bash
make
```

### Execution
Run the compiled executable:
```bash
# On Linux/macOS
./out

# On Windows
out.exe
```
*(Note: The program uses `chcp 65001` on startup to ensure proper UTF-8 character encoding in the Windows command prompt).*

## 📖 How to Use the CLI

Once the program is running, it will display a menu (loaded from `menu.txt`). You can interact with the program by typing the following commands and pressing `Enter`:

### Main Commands:

- `create` : Starts the wizard to add a new media item.
  - You will be asked to choose the type: `{0} Generic Media`, `{1} CD`, or `{2} DVD`.
  - Follow the prompts to enter Artist, Title, Tracks, Release Date (format: `dd/mm/yyyy`), Genre, and Keywords.
  - Depending on the type, it will ask for specific attributes (e.g., Duration and Volume for CDs; Audio format and Subtitles for DVDs).
  
- `show` : Displays a formatted list of all media items currently loaded in memory.

- `remove` : Lists all current media files with an index number. Type the index number of the media you wish to delete from both memory and the `Resources/` folder.

- `exit` : Safely saves all changes to the `Resources/` folder and closes the application. **Always use this command to quit to avoid data loss.**

### Query Command (`letra`):
Typing `letra` opens a sub-menu for specific data queries and sorting. After typing `letra`, select one of the following options:

- **`a`** - Shows all CDs by a specific artist, ordered by release date.
- **`b`** - Shows all DVDs by a specific artist, ordered by release date.
- **`c`** - Shows all Media (CDs, DVDs, and Generic) by a specific artist, ordered by release date.
- **`d`** - Shows all Media released in a specific year, ordered alphabetically.
- **`f`** - Shows CDs and DVDs separated by a specific genre, ordered alphabetically.
- **`g`** - Lists all unique keywords found across the entire media collection (no repetitions).

# 🔎 Inverted Search Project in C

## 📌 Project Overview

Inverted Search is a command-line application written in **C** that builds an **inverted index** from multiple text files. It stores each unique word, the files containing that word, and the number of times it appears in each file. The database can be displayed, searched, updated with new files, and saved for future use.

## ✨ Features

- 📂 **Input File Validation:** Checks file extensions, existence, non-empty content, and duplicate files.
- 🏗️ **Create Database:** Builds an inverted index from valid text files.
- 📊 **Display Database:** Displays indexed words, filenames, file counts, and word frequencies in a table.
- 🔍 **Search Database:** Finds a word and displays the files containing it and its occurrence count.
- 🔄 **Update Database:** Adds a new file to the existing index without rebuilding previously indexed files.
- 💾 **Save Database:** Stores the index in a text file for future use.
- 🖥️ **Menu-Driven Interface:** Provides six menu options with a continue prompt after operations.

## ⚙️ How It Works

The program uses a **hash table with 27 slots**. Each word is assigned an index based on its first character.

| 🔤 First Character | 📍 Hash Index |
|---|---:|
| `a`–`z` or `A`–`Z` | 0–25 |
| Digits and other characters | 26 |

Alphabetic characters are converted to lowercase before calculating the index:

```c
tolower(ch) - 'a'
```

Each hash-table slot points to a linked list of unique words (**main list**). Every word node maintains another linked list (**sub list**) containing the filenames in which the word appears and its occurrence count in each file.

### 🗂️ Data Structure Visualization

```text
Hash Table (27 slots)

[0] --> "apple" (2 files) --> "arrow" (1 file) --> NULL
           |                     |
           v                     v
        file2.txt (3)          file1.txt (1)
           |
           v
        file1.txt (1)

[1] --> "bat" ...
...
[26] --> "123" ...
```

## 🧱 Data Structures

- 📄 **Flist:** Maintains the list of valid input files.
- 🗃️ **Hash_t:** Represents a hash-table slot and points to its main linked list.
- 📝 **Mlist:** Stores each unique word, the number of files containing it, and a pointer to its sub list.
- 🔗 **Slist:** Stores a filename, the word's occurrence count in that file, and a pointer to the next file node.

## 📁 Project Structure

```text
inverted-search/
├── header.h
├── main.c
├── read_and_validation.c
├── create_db.c
├── display_db.c
├── search_db.c
├── update_db.c
├── save_database.c
└── README.md
```

## 🖥️ Menu Options

| Option | Operation | Description |
|---:|---|---|
| 1️⃣ | Create Database | Reads valid input files and builds the index. |
| 2️⃣ | Display Database | Displays all indexed words and their file details. |
| 3️⃣ | Search Database | Searches for a word and displays its file details. |
| 4️⃣ | Update Database | Validates and indexes a new file. |
| 5️⃣ | Save Database | Saves the index to a `.txt` file. |
| 6️⃣ | Exit | Terminates the program. |

After options 1–5, the program asks `Do you want to continue?`. Enter `y` or `Y` to continue, or `n` or `N` to quit.

## 📊 Sample Output

### 📋 Display Database

```text
+-------+----------------------+-------+---------------------------+------------+
| Index | Word                 | Files | File Name                 | Word Count |
+-------+----------------------+-------+---------------------------+------------+
| 0     | apple                | 2     | file2.txt                 | 3          |
| 0     | apple                | 2     | file1.txt                 | 1          |
| 1     | bat                  | 1     | file1.txt                 | 2          |
+-------+----------------------+-------+---------------------------+------------+
```

### 💾 Saved Database Format

```text
#0;apple;2;file2.txt;3;file1.txt;1;#
#1;bat;1;file1.txt;2;#
```

Each line follows this format:

```text
#index;word;fileCount;filename;wordcount;filename;wordcount;...;#
```

## ✅ Input File Validation

A file is accepted only if it meets all four conditions:

1. 📌 It has the `.txt` extension.
2. 📂 It exists and can be opened.
3. 📄 It is not empty.
4. 🔁 It has not already been added.

Invalid files are reported and skipped, while the remaining valid files continue to be processed.

## 🛠️ Technologies Used

- 💻 C Programming
- 🗃️ Hash Tables
- 🔗 Singly Linked Lists
- 👉 Pointers and Dynamic Memory Allocation
- 🔤 String Manipulation
- 📂 File Handling
- 🖥️ Command-Line Interface
- ⚙️ Makefile (if used in the project)

## 🚀 Compilation and Execution

Compile the source files using your project's Makefile:

```bash
make
```

Run the program with the input text files:

```bash
./a.out file1.txt file2.txt file3.txt
```

> **Note:** These commands assume your Makefile generates `a.out`. If it generates a differently named executable, use that executable's name instead.

## 👩‍💻 Author

**Shruti Khamitkar**

# 🧩 AcrosticMultiCreator

🔠 **AcrosticMultiCreator** is a C terminal-based program for creating intelligent **acrostics** (ακροστιχίδες), using user-supplied or file-loaded word lists.

---

## ✨ Features

✅ Create acrostics from any word  
📂 Load word lists from files (e.g., `Cars.txt`, `History.txt`)  
🔡 Insert/delete words manually  
📈 Words are sorted and tracked by usage and metadata  
🎮 Easy or Hard difficulty mode for generating acrostics  
💾 Save acrostics with hidden letters and solutions to `.txt` files  

---

## ⚙️ Compilation & Execution

### 🔧 Compile

```bash
gcc AcrosticMultiCreator.c -o Acrostic
```

### ▶️ Run

```bash
./Acrostic
```

---

## 🧑‍💻 Commands

```
insert:      Insert words manually
load:        Load words from a file (Cars, Sports, etc.)
delete:      Delete one or more words
showfwd:     Show first N words in list
showrev:     Show last N words in list
findfwd:     Find N words (starting with prefix) forward
findrev:     Find N words (starting with prefix) backward
create:      Create acrostic (e.g. create: hello easy)
save:        Save acrostic and solution to file
exit         Exit the program
```

---

## 📁 Word File Format

Files must contain **only alphabetic words** (e.g., `SPORT`, `ENGINE`)  
Words can be separated by **spaces** or **new lines**

**Examples:** `Cars.txt`, `Cooking.txt`, `Geography.txt`

---

## 🧩 Acrostic Modes

- 🔹 **Easy**: shorter & frequently used words  
- 🔸 **Hard**: longer & rarer words, more letters hidden

---

## 🖥️ Sample Menu Output

```
╔══════════════════════════════════════════════════════════════════════╗
║                                「 ✦ MENU✦ 」                            ║
║----------------------------------------------------------------------║
║   .Options:                                                          ║
║   -Insert: Command -> insert: word1 word2                            ║
║   -Insertfile: Command -> load: filename                             ║
║   -Files Choices: Sports, Cars, History, Geography, Cooking          ║
║   -Delete: Command -> delete: word1 word2                            ║
║   -Showfwd: Command -> showfwd: (number)                             ║
║   -Showrev: Command -> showrev: (number)                             ║
║   -Findfwd: Command -> findfwd: (prefix) (number)                    ║
║   -Findrev: Command -> findrev: (prefix) (number)                    ║
║   -Create: Command -> create: word easy/hard                         ║
║   -Savefile: Command -> save: filename                               ║
║   -Exit: Command -> exit                                             ║
╚══════════════════════════════════════════════════════════════════════╝
```

---

## 💾 Save Output Example

```
A _ _ L E
C _ R

Solution:
APPLE
CAR
```
---
## 📜 License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2025 [George]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

---

## 👤 Author

> Made by [George]  
> Contributions, stars ⭐ and forks 🍴 are welcome!

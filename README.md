#Library Management System

**Author:** Javlonbek  
**Language:** C++  
**Environment:** MSYS2 (required to run `.exe`)  

---

## Overview

This is a **simple C++ Library Management System** that allows users to manage a small library.  
The system supports:

- Adding new books  
- Viewing all books  
- Searching and borrowing books  
- Returning books  
- Saving library data with backups  

> **Note:** The compiled executable (`library.exe`) requires MSYS2 or a similar C++ environment. Running it directly in Windows CMD may not work.

---

## Features

### 1. Add New Book
- Enter **Book ID**, **Title**, **Author**, **Publication Year**, and **Quantity**.  
- Ensures **unique IDs** and valid inputs.  

### 2. View All Books
- Lists all books with details:  

| ID | Title | Author | Year | Qty |
|----|-------|--------|------|-----|

### 3. Search and Borrow Book
- Search by **ID** or **Title**.  
- Borrow available books (quantity decreases).  

### 4. Return Book
- Return previously borrowed books (quantity increases).  

### 5. Save and Exit
- Saves all library data.  
- Creates a backup in `saved_data/backup.txt`.

---

## Screenshots

```markdown
!("C:\Users\Javlonbek\Desktop\screenshots\1.png")
!("C:\Users\Javlonbek\Desktop\screenshots\2.png")
!("C:\Users\Javlonbek\Desktop\screenshots\3.png")
!("C:\Users\Javlonbek\Desktop\screenshots\4.png")
!("C:\Users\Javlonbek\Desktop\screenshots\5.png")

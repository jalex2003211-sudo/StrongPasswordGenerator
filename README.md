# 🔐 StrongPasswordGenerator

A simple but effective **C++ Strong Password Generator** created as a university assignment and now used in everyday practice.

Developed by **AlexPCodes**

---

## 📌 Description

StrongPasswordGenerator is a C++ console application that generates secure random passwords based on a user-defined length.

The generated password includes:
- ✅ Uppercase letters (A–Z)
- ✅ Lowercase letters (a–z)
- ✅ Numbers (0–9)
- ✅ Special characters (!@#$%^&*)

For passwords longer than 2 characters, the program ensures:
- At least **one number**
- At least **one special character**

---

## 🚀 Features

- User-defined password length
- Randomized character selection
- Basic strength validation
- Simple and lightweight C++ implementation
- Fast execution

---

## 🛠 Technologies Used

- C++
- Standard Library:
  - `<iostream>`
  - `<cstdlib>`
  - `<ctime>`

---

## 💻 How to Compile & Run

### Linux / macOS
```bash
g++ StrongPasswordGenerator.cpp -o StrongPasswordGenerator
./StrongPasswordGenerator


# 🛡️ FileGuard - File Integrity Checker

A cybersecurity tool developed using C programming
and OpenSSL to detect unauthorized file modifications
using SHA-256 cryptographic hashing.

## 🚀 Features

- SHA-256 hash generation
- File registration
- Secure hash comparison
- File integrity verification
- Unauthorized modification detection
- Registered file management

## 🛠️ Technologies Used

- C Programming
- OpenSSL
- SHA-256
- Linux / Ubuntu
- GCC Compiler

## ⚙️ Installation

Install the required dependencies:

```bash
sudo apt update
sudo apt install build-essential libssl-dev git
```

## ▶️ Compilation

```bash
gcc -Wall -Wextra -std=c11 main.c -o fileguard -lcrypto
```

## ▶️ Execution

```bash
./fileguard
```

## 🔍 How It Works

1. Select a file.
2. Generate its SHA-256 hash.
3. Register and store the original hash.
4. Calculate the hash again during verification.
5. Compare the stored and current hashes.
6. Display the integrity verification result.

## 📸 Project Demonstration

The application can identify whether a file
has been modified after registration.

- PASS: Original file remains unchanged.
- WARNING: File content has been modified.

## 🔮 Future Enhancements

- Automatic folder monitoring
- Digital signature verification
- Improved database security
- Graphical user interface

## 👨‍💻 Author

Sesha Sai

GitHub: https://github.com/Seshasai-tech

---

⭐ If you find this project useful, consider
giving the repository a star!

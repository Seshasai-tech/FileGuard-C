
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

### 1. Application Interface
![Main Menu](screenshots/01-main-menu.png)

### 2. File Registration
![File Registration](screenshots/02-file-registration.png)

### 3. Integrity Verification
![Integrity Verification](screenshots/03-integrity-verified.png)

### 4. Unauthorized Modification Detection
![Modification Detection](screenshots/04-modification-detected.png)

### 5. Registered Files
![Registered Files](screenshots/05-registered-files.png)

## 🔮 Future Enhancements

- Duplicate registration prevention
- File monitoring
- Digital signature verification
- Improved database security

## 👨‍💻 Author

**Sesha Sai**

GitHub: https://github.com/Seshasai-tech


---

⭐ If you find this project useful, consider
giving the repository a star!

## Holberton Simple Shell (HSS)

A simple UNIX command line interpreter written in C, built as part of the Holberton School curriculum.

![C](https://img.shields.io/badge/C-gnu89-blue)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-orange)
![Project](https://img.shields.io/badge/Project-Holberton-success)

## 📚 Table of Contents

<details>
<summary>📖 Click to expand</summary>

<br>

* 📟 [Technologies used](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#technologies-used)
* 📖 [Description](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#-description)
* 🔧 [Prerequisites](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#prerequisites)
* ⚙️ [Installation](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#-description)
* 🛠️ [Compilation](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#%EF%B8%8F-compilation)
* ▶️ [Usage](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#%EF%B8%8F-usage)
* ✨ [Features](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#features)
* 🗂️ [Project Structure](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#%EF%B8%8F-project-structure)
* 👨‍💻 [Authors](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#%E2%80%8D-authors)
* 👥 [Acknowledgements](https://github.com/sagalou/holbertonschool-simple_shell/tree/dev?tab=readme-ov-file#-additionals)


WIP

* 📘 [Manual]()
* ⚠️ [Limitations]()
* 🧪 [Valgrind]()
* 🔄 [Flowchart]()


* []()

</details>

## 📟 Technologies used

![C](https://camo.githubusercontent.com/b449f10e4a9af27bbe5db205b455a8f1a80d1c71f816b094bcf998c252627fec/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f632d2532333030353939432e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d63266c6f676f436f6c6f723d7768697465)![Ubuntu](https://camo.githubusercontent.com/7330205ef5ca5b6c63162e2e0f6245b13a03791da7600a826fc77d7aa15a83d6/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f5562756e74752d4539353432303f7374796c653d666f722d7468652d6261646765266c6f676f3d7562756e7475266c6f676f436f6c6f723d7768697465)![GCC](https://camo.githubusercontent.com/7f68c714dd1bcb9be97fe23f58f34f245ae71a8f607f6c620971ad5e5bf589be/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4743432d3333333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676e75266c6f676f436f6c6f723d7768697465)![VSCODE](https://camo.githubusercontent.com/8056377ae1874efe9fb628d089a0e796e2020ac12e9a0a2d5353bf8f99ab6d02/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f56697375616c25323053747564696f253230436f64652d3030373864372e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d76697375616c2d73747564696f2d636f6465266c6f676f436f6c6f723d7768697465)![Git](https://camo.githubusercontent.com/18c1d28951104e3dbf342dcaae38b07f65c95f0401e5de36aa560f6073db149e/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769742d2532334630353033332e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d676974266c6f676f436f6c6f723d7768697465)

## 📖 Description
`hsh` is a simple shell that reads commands from standard input and executes them,
in both interactive and non-interactive mode.

---

## Getting Started

## 🔧 Prerequisites

Before starting, ensure you have:

| Requirement | Details |
|------------|--------|
| OS | Linux / Unix-based system (Ubuntu 20.04+ recommended) |
| Compiler | `gcc` (-Wall -Werror -Wextra -pedantic -std=gnu89) |
| Standard | `gnu89` |
| Libraries | glibc |
| Tools | `git`, `valgrind` |
| Permissions | Ability to compile and execute binaries |
| Betty | Betty code style compliant |

---

## ⚙️ Installation

## 📋 Clone the repository

```bash
git clone https://github.com/sagalou/holbertonschool-simple_shell.git
```

## 📁 Navigate into the directory

```bash
cd holbertonschool-simple_shell
```

## 🛠️ Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## ▶️ Usage

```bash
./hsh
```

**Interactive mode:**
$ ./hsh
($) /bin/ls
($) exit

**Non-interactive mode:**
$ echo "/bin/ls" | ./hsh

## ✨ Features

- Display a prompt and wait for user input
- Execute commands with their full path (`/bin/ls`)
- Handle errors the same way as `/bin/sh`
- Support end-of-file (Ctrl+D)

## 🗂️ Project Structure

| File | Description |
|---|---|
| `main.c` | Entry point |
| `env.c` | Print environment |
| `prompt.c` | Handle prompt display |
|||

## 👨‍💻 Authors

- Kevin Rigal (splint314) — krigal323@gmail.com
- Sagal-Louise Haider (sagalou) — sagal.louise.haider@gmail.com

## 👥 Acknowledgements

This project is part of the Holberton School curriculum.
Special thanks to Hugo Chilemme & Sofian Messaoui for their guidance.
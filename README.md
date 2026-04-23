## Holberton Simple Shell (HSS)

A simple UNIX command line interpreter written in C, built as part of the Holberton School curriculum.

![C](https://img.shields.io/badge/C-gnu89-blue)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-orange)
![Project](https://img.shields.io/badge/Project-Holberton-success)

## 📚 Table of Contents

<details>
<summary>📖 Click to expand</summary>

<br>

* 📟 [Technologies used](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-technologies-used)
* 📖 [Description](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-description)
* 🔄 [Flowchart](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-flowchart)
* 🔧 [Prerequisites](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-prerequisites)
* ⚙️ [Installation](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%EF%B8%8F-installation)
* 🛠️ [Compilation](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%EF%B8%8F-compilation)
* ▶️ [Usage](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%EF%B8%8F-usage)
* 📘 [Manual](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-manual)
* ⚠️ [Limitations](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%EF%B8%8F-limitations)
* 🧪 [Valgrind](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-valgrind)
* ✨ [Features](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-features)
* 🗂️ [Project Structure](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%EF%B8%8F-project-structure)
* 👨‍💻 [Authors](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#%E2%80%8D-authors)
* 👥 [Acknowledgements](https://github.com/sagalou/holbertonschool-simple_shell/blob/main/README.md#-acknowledgements)

</details>

## 📟 Technologies used

![C](https://camo.githubusercontent.com/b449f10e4a9af27bbe5db205b455a8f1a80d1c71f816b094bcf998c252627fec/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f632d2532333030353939432e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d63266c6f676f436f6c6f723d7768697465)![Ubuntu](https://camo.githubusercontent.com/7330205ef5ca5b6c63162e2e0f6245b13a03791da7600a826fc77d7aa15a83d6/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f5562756e74752d4539353432303f7374796c653d666f722d7468652d6261646765266c6f676f3d7562756e7475266c6f676f436f6c6f723d7768697465)![GCC](https://camo.githubusercontent.com/7f68c714dd1bcb9be97fe23f58f34f245ae71a8f607f6c620971ad5e5bf589be/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4743432d3333333333333f7374796c653d666f722d7468652d6261646765266c6f676f3d676e75266c6f676f436f6c6f723d7768697465)![VSCODE](https://camo.githubusercontent.com/8056377ae1874efe9fb628d089a0e796e2020ac12e9a0a2d5353bf8f99ab6d02/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f56697375616c25323053747564696f253230436f64652d3030373864372e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d76697375616c2d73747564696f2d636f6465266c6f676f436f6c6f723d7768697465)![Git](https://camo.githubusercontent.com/18c1d28951104e3dbf342dcaae38b07f65c95f0401e5de36aa560f6073db149e/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6769742d2532334630353033332e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d676974266c6f676f436f6c6f723d7768697465)

## 📖 Description
`hsh` is a simple shell that reads commands from standard input and executes them,
in both interactive and non-interactive mode.

## 🔄 Flowchart
```text
┌─────────────────┐
│      START      │
└────────┬────────┘
         │
         ▼
┌─────────────────────┐
│   Display prompt    │
│        "$ "         │
└────────┬────────────┘
         │
         ▼
┌─────────────────────┐
│    Read command     │
│     getline()       │
└────────┬────────────┘
         │
         ▼
◇─────────────◇
◇    EOF ?    ◇──── yes ──→ ┌─────────┐
◇─────────────◇             │  EXIT   │
         │ no                └─────────┘
         ▼
┌─────────────────────┐
│   split_string()    │
│      → av[]         │
└────────┬────────────┘
         │
         ▼
◇──────────────────────◇
◇  av[0] == "exit" ?   ◇── yes ──→ ┌─────────┐
◇──────────────────────◇           │  EXIT   │
         │ no                       └─────────┘
         ▼
◇─────────────────────◇
◇  av[0] == "env" ?   ◇── yes ──→ ┌───────────────┐
◇─────────────────────◇           │ print environ │
         │ no                      └───────────────┘
         ▼
┌─────────────────────┐
│     find_path()     │◄──────────────────┐
│  stat() each dir    │                   │
└────────┬────────────┘                   │
         │                                │
         ▼                                │
◇──────────────◇                          │
◇  cmd == NULL ? ◇── yes ──→ ┌──────────────┐
◇──────────────◇             │ print error  │
         │ no                 │  (no fork!)  │
         ▼                    └──────┬───────┘
┌──────────────────────────┐         │
│ fork() +execve()+ wait() │   ◄─────┘
└────────────┬─────────────┘
             │
             ▼
      ↻ Back to prompt
```

## 🖼️ Picture

![Flowchart](https://i.imgur.com/dMKaWHh.png)

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

## 📘 Manual

To view the manual page for `hsh`, first move the man file to the appropriate directory and use the `man` command:

Rename and install the man page:

```bash
mv man_1_simple_shell hsh.1
sudo cp hsh.1 /usr/share/man/man1/
sudo gzip /usr/share/man/man1/hsh.1
man hsh
```

Alternatively, you can display it without installation using:

```bash
man ./hsh.1
```

## ⚠️ Limitations

### Missing features

No support for:
- pipes (|)  
- command chaining (&&, ||, ;)  
- variable expansion ($?, $$)  
- comments (#)  
- script execution  

### Missing builtins

- cd  
- setenv  
- unsetenv  
- alias  
- help  

### Robustness

- No handling of very long lines  
- No SIGINT handling (Ctrl+C)  

## 🧪 Valgrind
```text
(.venv) kevin@splint:~/projets/holberton/holbertonschool-simple_shell$ valgrind --leak-check=full --show-leak-kinds=all ./hsh
==3810== Memcheck, a memory error detector
==3810== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3810== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3810== Command: ./hsh
==3810== 
($) ls
AUTHORS  README.md  builtins.c  find_path.c  flowchart.md  flowchart.png  hsh  main.c  main.h  man_1_simple_shell  process_command.c  resolve_command.c  shell.c
($) ls -l
total 120
-rw-r--r-- 1 kevin kevin   107 Apr 20 20:35 AUTHORS
-rw-r--r-- 1 kevin kevin 13450 Apr 21 18:56 README.md
-rw-r--r-- 1 kevin kevin   560 Apr 21 18:50 builtins.c
-rw-r--r-- 1 kevin kevin  1277 Apr 21 18:50 find_path.c
-rw-r--r-- 1 kevin kevin   473 Apr 20 21:43 flowchart.md
-rw-r--r-- 1 kevin kevin 40246 Apr 20 21:45 flowchart.png
-rwxr-xr-x 1 kevin kevin 21680 Apr 21 18:55 hsh
-rw-r--r-- 1 kevin kevin  1280 Apr 21 18:50 main.c
-rw-r--r-- 1 kevin kevin   741 Apr 21 18:50 main.h
-rw-r--r-- 1 kevin kevin  1046 Apr 21 18:58 man_1_simple_shell
-rw-r--r-- 1 kevin kevin   599 Apr 21 18:50 process_command.c
-rw-r--r-- 1 kevin kevin   878 Apr 21 18:50 resolve_command.c
-rw-r--r-- 1 kevin kevin  2036 Apr 21 18:50 shell.c
($) ls -l /tmp
total 40
drwx------ 2 kevin kevin 4096 Apr 21 18:49  mcp-sU0NcM
drwx------ 2 kevin kevin 4096 Apr 21 18:50  pyright-976-R1yi1p0X6qZY
drwxr-xr-x 3 kevin kevin 4096 Apr 21 18:50  python-languageserver-cancellation
drwx------ 2 root  root  4096 Apr 21 18:49  snap-private-tmp
drwx------ 3 root  root  4096 Apr 21 18:49  systemd-private-e6a0a62332a742ea8950b993c1255e8b-systemd-logind.service-i3ebVp
drwx------ 3 root  root  4096 Apr 21 18:49  systemd-private-e6a0a62332a742ea8950b993c1255e8b-systemd-resolved.service-pxoqSp
drwx------ 3 root  root  4096 Apr 21 18:49  systemd-private-e6a0a62332a742ea8950b993c1255e8b-systemd-timesyncd.service-jGRPFF
drwx------ 3 root  root  4096 Apr 21 18:49  systemd-private-e6a0a62332a742ea8950b993c1255e8b-wsl-pro.service-eyJ44I
prw------- 1 kevin kevin    0 Apr 21 18:58 'vgdb-pipe-from-vgdb-to-3810-by-kevin-on-???'
-rw------- 1 kevin kevin   48 Apr 21 18:58 'vgdb-pipe-shared-mem-vgdb-3810-by-kevin-on-???'
prw------- 1 kevin kevin    0 Apr 21 18:58 'vgdb-pipe-to-vgdb-from-3810-by-kevin-on-???'
drwxr-xr-x 2 kevin kevin 4096 Apr 21 18:50  {C1724EE2-8359-4E4A-9FD6-E2CBCD67EC94}
($) /bin/ls
AUTHORS  README.md  builtins.c  find_path.c  flowchart.md  flowchart.png  hsh  main.c  main.h  man_1_simple_shell  process_command.c  resolve_command.c  shell.c
($) hugolegoat
./hsh: 5: hugolegoat: not found
($) ls     -l
total 120
-rw-r--r-- 1 kevin kevin   107 Apr 20 20:35 AUTHORS
-rw-r--r-- 1 kevin kevin 13450 Apr 21 18:56 README.md
-rw-r--r-- 1 kevin kevin   560 Apr 21 18:50 builtins.c
-rw-r--r-- 1 kevin kevin  1277 Apr 21 18:50 find_path.c
-rw-r--r-- 1 kevin kevin   473 Apr 20 21:43 flowchart.md
-rw-r--r-- 1 kevin kevin 40246 Apr 20 21:45 flowchart.png
-rwxr-xr-x 1 kevin kevin 21680 Apr 21 18:55 hsh
-rw-r--r-- 1 kevin kevin  1280 Apr 21 18:50 main.c
-rw-r--r-- 1 kevin kevin   741 Apr 21 18:50 main.h
-rw-r--r-- 1 kevin kevin  1046 Apr 21 18:58 man_1_simple_shell
-rw-r--r-- 1 kevin kevin   599 Apr 21 18:50 process_command.c
-rw-r--r-- 1 kevin kevin   878 Apr 21 18:50 resolve_command.c
-rw-r--r-- 1 kevin kevin  2036 Apr 21 18:50 shell.c
($) 
($) exit
==3810== 
==3810== HEAP SUMMARY:
==3810==     in use at exit: 0 bytes in 0 blocks
==3810==   total heap usage: 23 allocs, 23 frees, 8,301 bytes allocated
==3810== 
==3810== All heap blocks were freed -- no leaks are possible
==3810== 
==3810== For lists of detected and suppressed errors, rerun with: -s
==3810== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
## ✨ Features

Display a prompt and wait for user input
Interactive and Non-Interactive Modes: Supports manual command entry and piped input.  
Command Execution: Finds and runs executable programs using the PATH.  
Path Resolution: Correctly handles both absolute paths (e.g., /bin/ls) and relative command names (e.g., ls).  
Built-in Commands: Includes native support for exit (to close the shell) and env (to display environment variables).  
Robust Error Handling: Displays system-specific error messages and returns correct status codes (like 127 for command not found).  
Memory Efficiency: Designed to free all allocated memory before exiting to ensure no leaks.  

## 🗂️ Project Structure

| File | Description |
|---|---|
| `main.c` | Entry point|
| `builtins.c` | Built-in commands|
| `main.h` | Core headers|
| `shell.c` | Command handling|
| `find_path.c` | Path resolution |

## 👨‍💻 Authors

- Kevin Rigal (splint314) — krigal323@gmail.com
- Sagal-Louise Haider (sagalou) — sagal.louise.haider@gmail.com

## 👥 Acknowledgements

This project is part of the Holberton School curriculum.  
Special thanks to Hugo Chilemme & Sofian Messaoui for their guidance.

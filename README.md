# Minishell — *As beautiful as a shell* 🚀

![Language: C](https://img.shields.io/badge/language-C-blue)
![Status: In progress](https://img.shields.io/badge/status-in--progress-yellow)
![42 Project](https://img.shields.io/badge/42-minishell-orange)

> A small, production-minded implementation of a Unix-like shell written in C for the 42 curriculum.  
> Designed to be a portfolio piece demonstrating system programming skills: processes, pipes, redirections, signals, parsing and environment handling.

---

## Table of contents

- [Pitch](#pitch)  
- [Why this project](#why-this-project-portfolio-highlights)  
- [Features](#features)  
- [Build & Run](#build--run)  
- [Usage examples](#usage-examples)  
- [Project structure](#project-structure)  
- [Tests](#tests)  
- [Evaluation checklist (42)](#evaluation-checklist-42)  
- [Known limitations](#known-limitations)  
- [How I implemented key parts (short)](#how-i-implemented-key-parts-short)  
- [Contributing & Contact](#contributing--contact)  
- [License](#license)

---

## Pitch

This `minishell` is a compact reimplementation of core shell features. It is intentionally minimal but robust: it follows the 42 subject requirements and is structured for readability, testing and demonstration during defense or interviews.

---

## Why this project (portfolio highlights)

- **Low-level system skills** — process control (`fork`, `execve`, `pipe`, `dup2`), file descriptors and redirections.  
- **Unix internals** — environment variables, signal handling and job control basics.  
- **Parser & architecture** — tokenization, quoting rules, AST-ish command representation, and a clear executor pipeline.  
- **Engineering practices** — Makefile with strict flags, tests, documented limitations, and Git history showing iterative improvements.

When presenting, show: parser code, how pipes are wired, heredoc handling, and a live demo with edge cases.

---

## Features

- Interactive prompt with history (readline).
- Execute binaries from `PATH`, relative and absolute paths.
- Builtins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Pipes (`|`) connecting multiple commands.
- Redirections: input `<`, output `>`, append `>>`, heredoc `<<`.
- Environment expansion: `$VAR` and special `$?`.
- Quote handling: `'` (literal) and `"` (allow `$` expansion).
- Signal handling approximating `bash` behavior in interactive mode:
  - `Ctrl-C` interrupts current input/foreground job and prints a fresh prompt.
  - `Ctrl-D` exits the shell (EOF).
  - `Ctrl-\` ignored in interactive mode.
- At most one global integer used to store received signal number (subject requirement).

---

## Build & Run

**Requirements:** `cc` (or `gcc`), `make`, `readline` library.

**Build**

**bash**
git clone <your-repo-url>
cd minishell
make
## Example session

Copy-paste into your shell to reproduce:

```bash
$ echo "Hello World"
Hello World

$ export MYVAR=42
$ echo "Value: $MYVAR"
Value: 42

$ ls -la | grep minishell > out.txt
$ cat out.txt

$ cat << EOF
line1
line2
EOF
line1
line2

$ false
$ echo $?
1

$ exit


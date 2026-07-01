*This project has been created as part of the 42 curriculum by guillsan*

# Disclaimer:
I made this project solo from scratch in about a month. I tried to keep the
project modular and organized, but due to time constraints, I believe there
are still a few areas were code duplication could've been avoided, or areas that
could've been modularized. That said, if time allows it, I'll be improving it
overtime, though I think it's interesting to have a snapshot of what was done
over that short period, even with its limitations. Memory control and leak avoidance
were a high priority.

# AI use
- Explore and discuss topics
- Clarifying POSIX behavior
- Understanding Bash edge cases
- Reviewing and discussing the documentation
- Reviewing parser design ideas
- Reviewing code written by me and analyzing it for errors
- Suggesting code fixes here and there

## (AI use-disclaimer):
- DONTs: It was never used to let it write code for me, rather, it provided fix-
  suggestions or some naming advice here and there.

# Resources:

### Linux man-pages (man7.org)
- https://man7.org/linux/man-pages/
### POSIX specification (> shell & utilities volume)
- https://pubs.opengroup.org/onlinepubs/9699919799/
### GNU Readline Library Documentation
- https://tiswww.case.edu/php/chet/readline/rltop.html
---
## chdir()
- https://man7.org/linux/man-pages/man2/chdir.2.html
## getcwd()
- https://man7.org/linux/man-pages/man3/getcwd.3.html
## getenv()
- https://man7.org/linux/man-pages/man3/getenv.3.html
## open()
- http://man7.org/linux/man-pages/man2/open.2.html
- https://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html
## readline()
- https://man7.org/linux/man-pages/man3/readline.3.html
### escape sequences (\001 & \002) for readline
- readline.h --> line 871:
```
/* Definitions available for use by readline clients. */
#define RL_PROMPT_START_IGNORE	'\001'
#define RL_PROMPT_END_IGNORE	'\002'
```

## Project Structure

```text
.
├── inc/
├── libft/
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── executor/
│   ├── builtins/
│   ├── signals/
│   └── ...
├── Makefile/
└── README.md
```

---

## Technical Overview

The shell execution flow can be summarized as:

```text
readline()
    ↓
lexer
    ↓
parser
    ↓
heredoc collection
    ↓
expansion
    ↓
pipes and redirections setup
    ↓
builtin execution or execve() (with path resolve)
    ↓
waitpid()
```

## Instructions

### Requirements

- GCC
- GNU Make
- Readline library
- Linux or macOS environment

### Compilation

```bash
make
```

Available Makefile rules:

```bash
make all
make clean
make fclean
make re
```

### Execution

```bash
./minishell
```

## Authors

**guillsan**

42 school

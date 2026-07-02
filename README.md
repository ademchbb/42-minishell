*This project has been created as part of the 42 curriculum by ragolden, adchebbi.*

# Minishell

## Description

Minishell is a lightweight Unix shell written in C, built as part of the 42 curriculum. The goal is to reproduce the core behavior of `bash --posix`, including command execution, environment variable management, redirections, pipes, and signal handling.

The project covers a wide range of systems programming concepts: process creation with `fork`/`execve`, inter-process communication via pipes, file descriptor manipulation, signal handling with `sigaction`, and terminal control with `termios`. The shell parses and executes command lines through a full pipeline: lexing, syntax checking, expansion, quote removal, parsing, and execution.

### Features

- Interactive prompt with command history (via `readline`)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Pipes (`|`) with support for multi-segment pipelines
- Multiple heredocs on the same command (`cat << A << B`)
- Quoted heredoc delimiters disable expansion (`cat << 'EOF'`)
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\` in all contexts (prompt, execution, heredoc)
- Proper exit codes following bash behavior (126, 127, 130...)

---

## Instructions

### Requirements

- GCC or Clang
- GNU Make
- `readline` library (`libreadline-dev` on Debian/Ubuntu)

### Compilation

```bash
make
```

This produces the `minishell` executable at the root of the repository.

```bash
make clean    # remove object files
make fclean   # remove object files and executable
make re       # recompile from scratch
```

### Execution

```bash
./minishell
```

The shell starts in interactive mode. Type commands as you would in bash:

```bash
minishell$ echo "hello world"
hello world
minishell$ cat << EOF | grep hello
> hello world
> bye
> EOF
hello world
minishell$ export FOO=bar && echo $FOO
bar
minishell$ exit
```

To run non-interactively (e.g. from a script):

```bash
echo "ls | grep .c" | ./minishell
```

---

## Resources

### Documentation and references

**Shell behavior and specification**
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative reference for bash behavior, used throughout the project to align our implementation.
- [POSIX.1-2017 — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal specification for POSIX shell behavior.
- [Write a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — introductory walkthrough of shell implementation concepts.
- [Shell implementation in C — cs.purdue.edu](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) — university course covering shell implementation in depth.

**System calls and Linux API**
- [Linux man pages](https://man7.org/linux/man-pages/) — used extensively for system calls: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`, `tcsetattr`, `readline`, and more.
- [The Linux Programming Interface — Michael Kerrisk](https://man7.org/tlpi/) — exhaustive reference on the Linux API; chapters 24–27 (processes), 44 (pipes), 63 (signals).
- [Advanced Unix Programming — Marc Rochkind](https://www.informit.com/store/advanced-unix-programming-9780131411548) — classic reference covering `fork`, `exec`, signals, and pipes.

**Signals**
- [signal(7) man page](https://man7.org/linux/man-pages/man7/signal.7.html) — complete list of POSIX signals and their default behavior.
- [sigaction(2) man page](https://man7.org/linux/man-pages/man2/sigaction.2.html) — signal disposition API used throughout the project.

**Terminal and termios**
- [termios(3) man page](https://man7.org/linux/man-pages/man3/termios.3.html) — terminal control, `VQUIT`, `ECHOCTL`, `tcsetattr`.
- [The TTY demystified — Linus Åkesson](https://www.linusakesson.net/programming/tty/) — essential read to understand why `SIG_IGN` alone is not enough to suppress `^\` during heredoc input.

**Readline**
- [GNU Readline Library — Programmatic API](https://tiswww.case.edu/php/chet/readline/readline.html#SEC23) — functions `rl_on_new_line`, `rl_replace_line`, `rl_redisplay` used in the SIGINT handler.
- [readline general documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — API reference for the readline library used for the interactive prompt and history.

**Heredoc**
- [Bash heredoc — linuxize.com](https://linuxize.com/post/bash-heredoc/) — expected heredoc behavior, quoted delimiters, and variable expansion rules.
- [Here Documents — tldp.org](https://tldp.org/LDP/abs/html/here-docs.html) — Advanced Bash Scripting Guide section on heredocs.

### AI usage

AI assistance (Claude, Anthropic) was used during the development of this project for the following tasks:

- **Debugging**: identifying the root cause of a double heredoc bug caused by `dup2` being called on `STDIN_FILENO` between heredoc reads, which corrupted the `save_stdin` captured in subsequent `handle_heredoc` calls. The fix was restructuring `apply_redirs` to resolve all file descriptors before applying any `dup2`.
- **Signal and terminal handling**: understanding why `Ctrl+\` printed `^\` during heredoc input despite `SIGQUIT` being set to `SIG_IGN` — the cause being `ECHOCTL` at the tty driver level — and implementing the fix via `tcsetattr`/`VQUIT`/`_POSIX_VDISABLE`.
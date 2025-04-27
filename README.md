# Minishell - Project Documentation

## 📊 General Project Architecture

The `minishell` project replicates bash behavior with certain limitations, setting a clear modular separation to facilitate development and understanding of the shell's flow.

### 🔹 Main Modules

- **Branch: Parser**
  - Read user input using `readline()`.
  - Tokenize input (lexer).
  - Parse tokens into command structures.
  - Expand environment and special variables (`$VAR`, `$?`).

- **Branch: Executor**
  - Apply input/output redirections.
  - Configure pipes if multiple commands are involved.
  - Analyze the type of command (builtin or external).
  - Execute builtins directly or fork for external commands.
  - Wait for process termination and save the exit status.


> 📍 Program Flow Diagram

![Program Flow](./Flujo_Programa_v1.0.jpg)

---

## 👨‍💻 Possible Architectures for Command Execution

### 1. Sequential Execution

- Each command is executed **after** the previous one finishes.
- Uses `fork() + execve()` + `waitpid()` in a strictly ordered manner.

**Advantages:**
- Simpler to implement and debug.
- Ideal for simple commands or linear scripts.

**Disadvantages:**
- Does not leverage natural concurrency.
- Cannot correctly manage pipelines or background tasks.

---

### 2. Controlled Concurrent Execution (Pipelines)

- Each command in a pipeline (`|`) is executed in its own `fork()`, communicating through `pipe()`.
- Processes run simultaneously.

**Advantages:**
- Replicates real Bash behavior.
- Enables efficient pipeline building.

**Disadvantages:**
- More complex redirection handling.
- File descriptor (`fd`) management must be very precise to avoid leaks or errors.

---

### 3. Recursive Execution (Subshells or Compound Commands)

- A tree structure is used to represent and evaluate compound commands (`(cmd1 && cmd2) || cmd3`).
- Each node may require child execution or recursive evaluation.

**Advantages:**
- Allows implementation of complex logical structures.
- Ideal for nested commands and subshells.

**Disadvantages:**
- More complex to implement.
- Greater care required in state ($?) propagation.

---

## 📚 Project Branch Organization

To enable parallel and organized development, two main branches have been defined:

- **Branch `parser`**: Development of lexical analysis, command parsing, and variable expansion.
- **Branch `executor`**: Development of redirections, pipes, command execution, and process management.

This structure allows:
- Dividing work without conflicts.
- Quickly iterating on separate functionalities.
- Integrating both flows (parser and executor) during testing phases.

---

## 📊 Visual Summary

- **Sequential**: for simple commands.
- **Concurrent**: for pipelines.
- **Recursive**: for control structures.

Each strategy will be used depending on the execution context detected during parsing.

---

## 🖋️ Commit Conventions

We will follow a commit standardization based on clear prefixes to identify the type of change:

### Example Commit History:

```
[FEAT] Add support for multiple languages
[FIX] Fix validation error on input
[REFACTOR] Improve structure of function ft_process
[DOCS] Update README with usage instructions
[TEST] Add tests for sorting function
```

### Allowed Prefixes:

| Prefix    | Description                                              |
|-----------|----------------------------------------------------------|
| feat      | To add a new functionality                               |
| fix       | To fix an error or bug                                   |
| refactor  | For internal improvements without changing functionality |
| style     | For format changes (indentation, spaces, etc.)           |
| docs      | For documentation changes                                |
| test      | To add or modify tests                                   |


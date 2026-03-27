# OCMS — Online Courses Manager System

**OCMS** (Online Courses Manager System) is a C++ console application that simulates a simple learning management system (LMS). It supports different user roles (Administrator, Teacher, Student), course/assignment management, submissions (answers), grading, and basic internal messaging.

## Features

- **Role-based users**
  - Administrator
  - Teacher
  - Student
- **Courses**
  - Teachers can create courses (optionally protected by a password)
  - Students can be enrolled in courses
- **Assignments & submissions**
  - Teachers can create assignments per course
  - Students can submit answers to assignments
  - Teachers can grade submissions and leave comments
- **Inbox / messages**
  - Users can send messages (mail) to other users
- **Persistence**
  - Application state is saved/loaded from a binary file (`systemData.bin`) on exit/start.

## Tech stack

- **Language:** C++
- **Build:** manual compilation via `g++` (no CMake/Makefile detected from the limited search results)

## Project structure (high level)

- `main.cpp` — CLI entry point and command loop
- `system.*` — central command detection / app orchestration
- `users/` — user types (`admin`, `teacher`, `student`, `user`)
- `course.*`, `assignment.*`, `answer.*`, `mail.*` — domain objects
- `customFunctions/` — custom containers/utilities (e.g., `CustomString`, `CustomVector`)
- `utils.*` — load/save state and helper lookups

## Getting started

### Prerequisites

- **g++** (GCC with C++ support)
  - Linux/macOS: usually available via your package manager (e.g., `build-essential` on Debian/Ubuntu)
  - Windows: use MinGW-w64, MSYS2, or WSL

### Compile

From the repository root, compile using `g++`:

```bash
g++ main.cpp utils.cpp system.cpp answer.cpp assignment.cpp course.cpp mail.cpp \
  users/admin.cpp users/student.cpp users/teacher.cpp users/user.cpp \
  customFunctions/customString.cpp \
  -g -o main.exe
```

> The command above is taken from the existing repository README and should match the project’s current file set.

### Run

```bash
./main.exe
```

On Windows (depending on your terminal):

```bat
main.exe
```

## Usage

When started, OCMS runs an interactive command loop and waits for commands at a `>` prompt. The available commands are parsed/handled by the `System` component (`system.detectCommand(cmd)` in `main.cpp`).

Because command names and exact syntax may evolve, consult the `System` implementation to see the full command list and parameters.

## Data persistence

OCMS loads and saves program state automatically:

- **Loads:** `systemData.bin` at startup
- **Saves:** `systemData.bin` at exit

If you want a clean start, delete `systemData.bin` and run the program again.

## Development notes

- The project uses custom data structures like `CustomString` and `CustomVector`.
- Several objects implement **binary serialization/deserialization** via `serialize(std::ofstream&)` and `deserialize(std::ifstream&)`.

## Author

- Felipe Urra Rivadeneira

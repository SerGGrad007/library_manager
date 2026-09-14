# Library Management System

Console-based library management system in C++20, built for the KFD test
assignment. Demonstrates OOP (inheritance/polymorphism), encapsulation, and
choosing appropriate STL data structures for a small in-memory system.

## Features

- **Book management** — add, remove, search (by title/author/genre/ISBN,
  case-insensitive substring match), find by ISBN.
- **User management** — register users of three types (Student, Faculty,
  Guest), find user by ID.
- **Borrowing operations** — borrow, return, view currently overdue books.
- **Input validation** — the console menu re-prompts on non-numeric or
  out-of-range input instead of crashing.

## Build & run

Requires CMake ≥ 3.16 and a C++20-capable compiler (GCC/Clang/MSVC).

```bash
mkdir build && cd build
cmake ..
cmake --build .
./library_app        # library_app.exe on Windows
```

Alternatively, just open the project folder in CLion — it picks up
`CMakeLists.txt` automatically; use the built-in Build/Run buttons.

## Project structure

```
include/   header files — class declarations (Book, User, Record,
           LibraryOperations, Library, LibraryConsole)
src/       implementation files (.cpp)
app/       main.cpp — the executable's entry point only
```

`main.cpp` contains nothing but a call into `LibraryConsole::run()` — all
actual logic lives in the `library_core` library, so it stays testable and
reusable independently of the console UI.

## OOP design

- `User` is an **abstract base class**; `Student`, `Faculty`, and `Guest`
  inherit from it and each override `getMaxBooks()`, `getBorrowDays()`, and
  `getType()` to encode their own business rules (see table below). This is
  the polymorphism the assignment asks for: `Library` only ever talks to a
  `User*`, never needs to know which concrete subclass it holds.
- `Book` and `Record` (a single borrowing transaction) are plain value
  classes — no inheritance needed, since every book/record behaves the same.
- `Library` implements the `LibraryOperations` interface and owns all data.
- `LibraryConsole` is a separate UI layer that only calls `Library`'s public
  methods — it has no knowledge of `unordered_map`/`vector`/`set` internals,
  so the console could be swapped for a different UI without touching the
  core logic.

## Data structure choices

| Structure | Used for | Why |
|---|---|---|
| `std::unordered_map<string, Book>` | books, keyed by ISBN | O(1) lookup for `findBook`/`borrowBook`/`returnBook`; ISBN is a natural unique key |
| `std::unordered_map<string, unique_ptr<User>>` | users, keyed by userId | same O(1) lookup rationale; `unique_ptr` is required because `User` is polymorphic — storing by value would slice Student/Faculty/Guest down to their base class |
| `std::vector<Record>` | borrowing history | history has no natural unique key (the same user can borrow the same book many times over its lifetime), and insertion order itself is meaningful (used when searching for the most recent open loan) |
| `std::set<string>` | genres seen so far | automatically keeps only unique genre names as books are added, with no manual dedup logic needed |

## Business rules

| User type | Max books | Borrow period |
|---|---|---|
| Student | 3 | 14 days |
| Faculty | 10 | 30 days |
| Guest | 1 | 7 days |

## Known limitations

- Registering a user or adding a book with an ID that already exists
  silently overwrites the previous entry (no duplicate-ID error).
- No persistence — all data lives in memory and is lost when the program
  exits.
- No per-day fine calculation — out of scope for this assignment; the
  system tracks *how many days* a book is overdue (`Record::countDaysExpired`),
  which is what "View overdue books" requires.

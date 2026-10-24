# CS 210: Corner Grocer Item Tracker

## Project Summary
The Corner Grocer Item Tracker is a C++ application designed to analyze daily transaction logs from text file records (`CS210_Project_Three_Input_File.txt`). The program parses item purchase histories and displays inventory frequencies through an interactive text menu. It generates a backing data file (`frequency.dat`) upon startup and offers real-time item searches, complete list views, and a visual asterisk histogram representing purchase metrics.

## Reflection

### Key Achievements & Code Quality
I designed the project using Object-Oriented Programming (OOP) principles by encapsulating the business logic within an `ItemTracker` class. I utilized `std::map<std::string, int>` to deliver $O(\log N)$ dynamic key-value lookups for item frequency tracking. Additionally, input string case standardization (`toTitleCase`) was implemented to ensure user search inputs matching item records were case-insensitive.

### Enhancements for Security & Efficiency
* **Data Structure Optimization:** Transitioning from `std::map` (Red-Black Tree) to `std::unordered_map` (Hash Table) would optimize key lookup time complexity from $O(\log N)$ down to average $O(1)$.
* **Input Validation & Exception Handling:** While basic stream buffer cleaning was implemented using `std::cin.clear()` and `std::cin.ignore()`, adding custom exception throwing (`try-catch` blocks) for file reading operations would improve runtime error robustness.
* **Security & Path Validation:** Hardcoding input file names could be refactored to sanitized path arguments to prevent directory traversal vulnerabilities if configured for external inputs.

### Challenges & Problem Solving
The most challenging aspect was implementing robust user input validation to prevent infinite loops when non-integer input was entered into the main menu. I resolved this issue by leveraging `std::cin.fail()` state checking alongside `std::numeric_limits<std::streamsize>::max()` to flush invalid data out of the input stream buffer cleanly. Reference materials such as *cppreference.com* were instrumental throughout this process.

### Transferable Skills
* Working with Standard Template Library (STL) associative containers (`std::map`).
* Stream file manipulation (`std::ifstream` and `std::ofstream`).
* Designing clean, modular Object-Oriented C++ classes separated into `.h` header definitions and `.cpp` implementation files.
* Stream buffer state clearing and input validation techniques.

### Maintainability, Readability, and Adaptability
The codebase is structured following standard C++ style practices:
* **Separation of Concerns:** Declaration (`ItemTracker.h`) and definition (`ItemTracker.cpp`) are strictly separated.
* **Inline Documentation:** Every method includes Doxygen-style header comments detailing functionality and parameter behavior.
* **Const Correctness:** Read-only methods (e.g., `printHistogram()`, `getItemFrequency()`) are marked `const` to preserve data integrity.
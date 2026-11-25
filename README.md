# MA429 Cybersecurity Assignments

M. Shubham · B.Tech Mathematics and Computing

Ten GNU C++17 programs, numbered in the order of the assignment PDF. The report includes the algorithms, correctness arguments, bounds and source listings.

| Problem | Topic | Source |
|---|---|---|
| 1 | Minimum panel flips | [p01.cpp](solutions/p01.cpp) |
| 2 | Hidden bit with AND or OR | [p02.cpp](solutions/p02.cpp) |
| 3 | Reconstruct a string from triples | [p03.cpp](solutions/p03.cpp) |
| 4 | Count safe XOR assignments | [p04.cpp](solutions/p04.cpp) |
| 5 | Decode a reversed-word sentence | [p05.cpp](solutions/p05.cpp) |
| 6 | Count equivalent words | [p06.cpp](solutions/p06.cpp) |
| 7 | Maximize the sum of path MEX values | [p07.cpp](solutions/p07.cpp) |
| 8 | Bipartiteness after edge toggles | [p08.cpp](solutions/p08.cpp) |
| 9 | Contact groups over a sliding day window | [p09.cpp](solutions/p09.cpp) |
| 10 | Find c and r for an iterated function | [p10.cpp](solutions/p10.cpp) |

## Compile and run

From the repository root, run `g++ -std=c++17 -O2 solutions/p01.cpp -o p01` and then `./p01` (Windows PowerShell uses `.\\p01.exe`). Paste the problem input. Problems 8 and 9 share `solutions/timeline.hpp`; keep it beside their sources.

Run `python tests/check.py` with Python 3.8+ and g++ on PATH to compile all ten programs and run the example checks, tree-label enumeration and local interactive judges. Problems 2 and 10 require a live judge or the simulator. The printed example dialogues are illustrative.

Problem 2 uses a randomized response in one ambiguous case. Under uniform private randomness its error probability per fixed case is at most 1/(2^29-1). The report explains the ambiguity and the bound.

[Read the complete solution report](MA429_Solutions.pdf).

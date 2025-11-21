# AVL Tree

A generic C++ AVL Tree implementation (HWT) made as a homework for C++ base course 25/26.
It supports standard BST operations and also **k-th element** and **rank queries** (counting elements $< n$) in **$O(\log N)$** time.

### Commands
| Cmd | Description |
| :--- | :--- |
| `k <x>` | Insert integer `x`. |
| `m <k>` | Find the `k`-th smallest element. |
| `n <x>` | Count elements strictly smaller than `x`. |
| `s ` | Stop program. |

### Build & Run
```bash
cmake -B build -S .
cmake --build build --parallel `nproc`
./build/AVLtrees
```

### Example
**Input:**
```text
k 8 k 2 k -1 m 1 m 2 n 3
```
**Output:**
```text
-1 2 2
```
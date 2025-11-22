# AVL Tree with Range Counting

A generic C++ AVL Tree implementation (HWT) made for the C++ base course 25/26.
It implements an ordered set that supports insertions and **range counting queries** in **$O(\log N)$** time.

### Task Logic
For a query `q L R`, the tree calculates the number of keys $x$ such that **$L < x \le R$** (strictly greater than $L$, less than or equal to $R$).

### Commands
| Cmd | Arguments | Description |
| :--- | :--- | :--- |
| `k` | `x` | Insert integer `x`. |
| `q` | `l r` | Print number of elements in range $(l, r]$. |

### Build & Run
```bash
cmake -B build -S .
cmake --build build --parallel `nproc`
./build/AVLtrees
```

### Example
**Input:**
```text
k 10 k 20 q 8 31 q 6 9 k 30 k 40 q 15 40
```
**Output:**
```text
2 0 3
```
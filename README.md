# Routing Protocols Simulation (DVR & LSR)

This project implements **Distance Vector Routing (DVR)** and **Link State Routing (LSR)** algorithms in C++, reading an adjacency‑matrix from a file and printing per‑node routing tables. It demonstrates how routers compute optimal paths via iterative table exchanges (DVR) and Dijkstra’s algorithm (LSR).

---

## Features

### Implemented

- **Distance Vector Routing (DVR):**
  - Initializes each node’s table with direct link metrics
  - Iteratively exchanges tables with neighbors until convergence
  - Computes and prints final “Dest  Metric  Next Hop” table for each node

- **Link State Routing (LSR):**
  - Reads full network topology at every node
  - Runs Dijkstra’s algorithm per node to find shortest paths
  - Prints “Dest  Metric  Next Hop” table for each source router

### Not Implemented

- **Dynamic Updates:**  
  - No support for link cost changes after convergence
- **Loop Prevention Techniques:**  
  - Basic DVR without split‐horizon or poison‐reverse
- **Real Networking Stack:**  
  - Pure simulation; does not open sockets or send real packets

---

## Design Decisions

### Adjacency Matrix Input

- Simple square matrix format allows arbitrary cost metrics  
- Zero ⇒ no link (converted internally to `INF` for non‑diagonal entries)

### “Metric” Heading

- Uniform table heading “Metric” used in both DVR and LSR for clarity

### Convergence Detection

- DVR: repeat until no distance updates in a full pass  
- LSR: single invocation of Dijkstra’s algorithm per source

---

## Implementation Details

### High‑Level Overview

#### Core Functions

- **`readGraphFromFile(filename)`**  
  - Parses first line as `n`, then reads `n×n` matrix  
  - Converts zeros off‑diagonal to `INF = 9999`

- **`simulateDVR(graph)`**  
  - `dist = graph`; `nextHop[i][j] = j` if direct link  
  - Triple‑nested loops to relax via all intermediate `k` until no change  
  - Calls `printDVRTable(node, dist, nextHop)` for each node

- **`simulateLSR(graph)`**  
  - For each `src`: run Dijkstra with `dist[src]=0`, `prev[]` array  
  - Calls `printLSRTable(src, dist, prev)` for each source node

- **`printDVRTable(...)` / `printLSRTable(...)`**  
  - Formats “Dest\tMetric\tNext Hop” rows, with “–” for self or unreachable

#### Code Flow Diagrams

```mermaid
flowchart LR
    subgraph DVR
      A0[Init dist & nextHop] --> B0[Repeat until no update]
      B0 --> C0{For u,v,k}
      C0 -->|if dist[u][v] > dist[u][k]+dist[k][v]| D0[Update dist & nextHop]
      C0 -->|else| E0[No change]
      D0 --> B0
      E0 --> B0
    end

    subgraph LSR
      A1[For each src] --> B1[Init dist[src]=0]
      B1 --> C1[Select unvisited u with min dist]
      C1 --> D1[Relax neighbors v]
      D1 --> C1
      C1 --> E1[Done → print table]
    end
---

## Execution Steps

1. **Compile**  
   ```bash
   g++ routing_sim.cpp -o routing_sim
   ```
2. **Run**  
   ```bash
   ./routing_sim input.txt
   ```
3. **Observe**  
   - First, all DVR tables appear under  
     `--- Distance Vector Routing Simulation ---`  
   - Then, all LSR tables under  
     `--- Link State Routing Simulation ---`

---

## Building and Running

```bash
# Compile
g++ routing_sim.cpp -o routing_sim

# Run with your adjacency matrix file
./routing_sim input.txt
```

> **Note:** `input.txt` must begin with node‐count `n`, followed by an `n×n` whitespace‑separated matrix.  
> Off‑diagonal zeros are treated as no‑link (`INF = 9999`).

---

## Technical Details

- **Language:** C++  
- **Infinite Cost:** Represented by `const int INF = 9999`  
- **Data Structures:**  
  - `vector<vector<int>> dist, nextHop` for DVR  
  - `vector<int> dist, prev`; `vector<bool> visited` for LSR  
- **Algorithm Complexity:**  
  - DVR: *O(n³)* per iteration, converges in ≤*n* iterations  
  - LSR: *O(n²)* per source (simple array‑based Dijkstra)

---

## Contribution

👤 **Palagiri Tousif Ahamad (220744):** 100% Contribution

---

## 🔹 References

- Kurose & Ross, _Computer Networking: A Top-Down Approach_  
- RFC 2453: RIP Version 2 (Distance Vector Example)  
- Dijkstra’s Original Paper, 1959  
```
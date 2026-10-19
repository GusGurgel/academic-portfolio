# Search Algorithms - Artificial Intelligence Assignment

This project implements and evaluates classic search algorithms for pathfinding in a grid-based city. It was developed for the Artificial Intelligence course in the Computer Science program at the Federal University of Ceará (UFC).

The project includes an interactive command-line interface for manually testing search configurations, as well as experiments that compare the algorithms using randomly generated start and goal positions.

## Overview

The environment represents a city as a grid with integer coordinates from `0` to `30` on both axes. The agent can move one position at a time in four directions: left, right, down, and up. Depending on the experiment, horizontal and vertical movements may have different costs, and some routes must pass through a pharmacy before reaching the destination.

## Implemented Algorithms

- **Breadth-First Search (BFS)**
- **Depth-First Search (DFS)**
- **Uniform-Cost Search (UCS)**, also known as Dijkstra's algorithm in this context
- **Greedy Best-First Search**
- **A* Search**
- **A* Search with an Additional Stop**, which requires the route to pass through at least one pharmacy before reaching the goal

The implementations report pathfinding results and track search statistics, such as generated and visited nodes.

## Cost Functions and Heuristics

Four cost functions are used to model different movement-cost scenarios:

| Function | Movement cost |
| --- | --- |
| `c1` | Every move costs `10`, regardless of direction. |
| `c2` | Vertical moves cost `10`; horizontal moves cost `15`. |
| `c3` | Vertical moves cost `10`; horizontal moves have a depth-dependent cost: `10 + (abs(5 - t) % 6)`. |
| `c4` | Vertical moves cost `10`; horizontal moves have a depth-dependent cost: `5 + (abs(10 - t) % 11)`. |

In `c3` and `c4`, `t` represents the number of edges from the root of the search tree to the node being evaluated.

The informed search algorithms use the following heuristics:

- **`h1` - Euclidean distance:** `10 * sqrt((x1 - x2)^2 + (y1 - y2)^2)`
- **`h2` - Manhattan distance:** `10 * (abs(x1 - x2) + abs(y1 - y2))`

The effectiveness and admissibility of a heuristic can depend on the cost function used in an experiment.

## Project Structure

```text
.
├── AT1 - Algoritmos de Busca.pdf
├── cli_interativo
│   ├── main.py
│   ├── node_a_star.py
│   ├── node.py
│   ├── result_a_star_with_stop.py
│   ├── result.py
│   ├── searches.py
│   └── settings.py
├── experimentos
│   ├── parte1
│   ├── parte2
│   ├── parte3
│   ├── parte4
│   └── parte5
├── README.md
└── Trabalho_Ia_Buscas-2_Documentação.pdf
```

- `cli_interativo/` contains the interactive CLI, node representations, search algorithms, configuration, and result-handling code.
- `experimentos/parte1/` through `experimentos/parte5/` contain the experiment scripts and supporting files for each part of the assignment.
- `AT1 - Algoritmos de Busca.pdf` contains the assignment specification.
- `Trabalho_Ia_Buscas-2_Documentação.pdf` contains the project report, experimental methodology, results, and conclusions.

## Requirements

- Python 3
- No third-party Python packages are required; the project uses Python's standard library.

## Running the Interactive CLI

From the project root, run:

```bash
cd cli_interativo
python main.py
```

Follow the prompts to select the search algorithm, start and goal coordinates, cost function (`c1` to `c4`), and heuristic (`h1` or `h2`) when applicable. Coordinates must be integers between `0` and `30`, entered in the format `x,y`.

For **A* with an additional stop**, provide the pharmacy coordinates when prompted. The CLI accepts up to four pharmacy positions, separated by spaces and written in the `x,y` format.

If your environment uses `python3` instead of `python`, run `python3 main.py`.

## Running the Experiments

Each experiment is stored in its own directory under `experimentos/`. Navigate to the desired part and run its `main.py` script:

```bash
cd experimentos/parte1
python main.py
```

Repeat the command from the corresponding directory for `parte2`, `parte3`, `parte4`, or `parte5`.

The experiment scripts generate random start and goal coordinates, so results may differ between runs. According to the project report, experiment results are saved as CSV files in a `resultado/` directory within each experiment folder.

### Experiment Summary

1. **Part 1 - BFS vs. DFS vs. UCS:** compares breadth-first, depth-first, and uniform-cost search under different cost functions.
2. **Part 2 - UCS vs. A*:** compares uniform-cost search with A* using the available cost functions and heuristics.
3. **Part 3 - Greedy vs. A*:** evaluates greedy best-first search and A* with different heuristics and cost configurations.
4. **Part 4 - BFS vs. DFS with Randomized Neighbors:** investigates how randomizing the order in which neighbors are explored affects the results.
5. **Part 5 - A* with a Pharmacy Stop:** searches for a route from the starting point to the destination that passes through at least one pharmacy.

## Results and Evaluation

The experiments are designed to compare the algorithms using metrics such as:

- Whether a valid path was found
- The returned path and its total cost
- The number of generated nodes
- The number of visited nodes

The interactive CLI also displays the search result and execution time. For the experimental analysis and conclusions, see `Trabalho_Ia_Buscas-2_Documentação.pdf`.

## Documentation

- [Assignment Specification](<AT1 - Algoritmos de Busca.pdf>)
- [Project Report](<Trabalho_Ia_Buscas-2_Documentação.pdf>)

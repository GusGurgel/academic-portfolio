# Quadratic Assignment Problem Solver with Genetic Algorithms

This repository contains a Python implementation of a **Genetic Algorithm (GA)** for the **Quadratic Assignment Problem (QAP)**. It was developed as the **first assignment for the Artificial Intelligence course** in the Computer Science program at the **Federal University of Ceará (UFC), Brazil**.

The project explores different genetic operators, tests alternative parameter configurations, and compares GA solutions with a greedy baseline. The accompanying report documents the implementation, experiments, and parameter choices.

## Overview

The Quadratic Assignment Problem consists of assigning facilities to locations while minimizing the total cost determined by the flow between facilities and the distance between locations. A solution is represented as a permutation, and the algorithm searches for assignments with lower cost (fitness).

The implementation supports several alternatives for the main stages of a genetic algorithm:

- **Selection:** biased roulette and tournament selection.
- **Crossover:** two-point crossover and majority-based crossover.
- **Mutation:** global swap and local swap.
- **Elitism:** preserving the best individual(s) or using biased roulette.

The solver reports fitness statistics for each generation, including the best, worst, mean, and mode fitness. It can also compare the result against a greedy solution and save output files for later analysis.

## Project Structure

```text
.
├── README.md
├── Relatorio_Resolucao_QAP_Usando_GA.pdf
└── src/
    ├── config/                   # Configuration utilities
    ├── expecific_tests/          # Specific test scripts and test data
    ├── ga_inputs/                # JSON input configurations
    ├── ga_outputs/               # Saved solver results
    ├── genetic_algorithms/       # Chromosome, population, and GA logic
    ├── input_generators/         # Input generation utilities
    ├── qap/                      # QAP representation and cost calculation
    ├── utils/                    # Shared helper functions
    ├── ga_solver_qap.py          # Runs the GA for one input
    └── multi_ga_solver_qap_tester.py  # Repeated runs and input comparison
```

## Requirements

- Python 3
- No third-party Python packages are required; the project uses Python's standard library.

## Input Configuration

Input configurations are JSON files stored in `src/ga_inputs/`. Each file specifies the problem size, the genetic operators, and the algorithm parameters. The distance and flow matrices can be supplied in the input; when they are omitted, the implementation generates them randomly.

Example configuration:

```json
{
  "n": 10,
  "selection_function": "SELECTION_WITH_TOURNAMENT",
  "crossover_function": "CROSSOVER_WITH_TWO_POINTS",
  "mutation_function": "MUTATION_WITH_GLOBAL_SWAP",
  "elitism_function": "ELITISM_WITH_ONLY_BEST",
  "mutation_prob": 0.05,
  "generation_limit": 50,
  "generation_size": 60,
  "tournament_size": 3,
  "crossover_majority_size": 15
}
```

Available configuration values for the genetic operators are:

| Parameter | Supported values |
| --- | --- |
| `selection_function` | `SELECTION_WITH_ADDICTED_ROULETTE`, `SELECTION_WITH_TOURNAMENT` |
| `crossover_function` | `CROSSOVER_WITH_TWO_POINTS`, `CROSSOVER_WITH_MAJORITY` |
| `mutation_function` | `MUTATION_WITH_GLOBAL_SWAP`, `MUTATION_WITH_LOCAL_SWAP` |
| `elitism_function` | `ELITISM_WITH_ONLY_BEST`, `ELITISM_WITH_ADDICTED_ROULETTE` |

Other parameters include `n` (problem size), `mutation_prob`, `generation_limit`, and `generation_size`. `tournament_size` is used for tournament selection, while `crossover_majority_size` controls how many individuals contribute to majority crossover.

The parameter study in the report recommended the following values for its experiments with `n = 10`: `generation_limit = 50`, `generation_size = 60`, `mutation_prob = 0.05`, `tournament_size = 3`, and `crossover_majority_size = 15`. These are experimental recommendations, not universal settings for every QAP instance.

## Running the Solver

Run the commands from the `src/` directory so the input and output directories are resolved correctly:

```bash
cd src
```

### Run a single input

The single-run solver accepts an input filename from `ga_inputs/`. For example:

```bash
python ga_solver_qap.py parte1.json
```

Use `--help` to see the available command-line options:

```bash
python ga_solver_qap.py --help
```

The documented options include:

- `--verbose`: display additional execution details.
- `--step`: print generation statistics step by step.
- `--save`: save the result under `ga_outputs/`.

For example, these options can be combined with an input file:

```bash
python ga_solver_qap.py parte1.json --verbose --step --save
```

### Compare repeated runs

`multi_ga_solver_qap_tester.py` runs and compares two input configurations multiple times, reporting average performance relative to the greedy baseline and average execution time. The number of runs must be greater than one.

```bash
python multi_ga_solver_qap_tester.py parte1.json parte2.json 10
```

Check its help output for the available options:

```bash
python multi_ga_solver_qap_tester.py --help
```

## Report

The project report is available in [**Relatorio_Resolucao_QAP_Usando_GA.pdf**](Relatorio_Resolucao_QAP_Usando_GA.pdf). It describes the algorithm design, parameter tuning, experiments comparing the available genetic operators, and an estimate of execution time for larger instances.

## Academic Context

- **Course:** Artificial Intelligence
- **Program:** Computer Science
- **Institution:** Federal University of Ceará (UFC), Brazil
- **Project:** First course assignment — solving the Quadratic Assignment Problem with Genetic Algorithms

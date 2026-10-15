# Grundy Coloring: Mathematical Modeling

This repository contains the final project for the **Computational Mathematics** course. The project compares two integer programming formulations for the **Grundy coloring problem** on randomly generated graphs:

- **Rodrigues formulation**
- **Carvalho formulation**

The implementations use the OR-Tools optimization solver to maximize the number of colors subject to the constraints defined by each formulation.

## Project Overview

The experiments compare both formulations on graphs with **10, 13, 15, 18, and 20 vertices**, using two edge probabilities:

- `p = 0.5` — lower edge probability
- `p = 0.8` — higher edge probability

For each instance, the notebook records the objective value (number of colors), execution time, and solver iterations. Each solver run has a time limit of **30 minutes**. Functions are also provided to visualize a graph and its coloring.

## Repository Contents

- `Modelagem_Coloracao_De_Grundy.ipynb` — Jupyter Notebook containing the mathematical formulations, Python implementations, experiments, recorded results, and conclusions.

## Requirements

- Python 3
- Jupyter Notebook or JupyterLab
- Python packages: `ortools`, `networkx`, `matplotlib`, and `graphviz`
- The **Graphviz system application** for graph rendering

Install the Python packages with:

```bash
pip install ortools networkx matplotlib graphviz
```

On Ubuntu or Debian, install the Graphviz system application with:

```bash
sudo apt update
sudo apt install graphviz
```

On other operating systems, install Graphviz using the instructions for your platform. The Python package alone may not be sufficient for rendering graphs.

## Running the Project

1. Clone or download this repository.
2. Install the requirements listed above.
3. Open `Modelagem_Coloracao_De_Grundy.ipynb` in Jupyter Notebook, JupyterLab, or Google Colab.
4. Run the notebook cells from top to bottom to load the helper functions, inspect the formulations, and review the recorded experiments.

After the function definitions have been executed, you can create a random graph and run either formulation with code like this:

```python
import networkx as nx

G = nx.gnp_random_graph(10, 0.5, seed=42)

Rodrigues(G, draw=True)
Carvalho(G, draw=True)
```

Setting a seed makes the generated graph repeatable. Results can still vary with solver versions and hardware.

## Results Summary

The notebook reports the following average execution times and iteration counts for its experiments:

| Formulation | Edge probability (`p`) | Average time | Average iterations |
|---|---:|---:|---:|
| Rodrigues | 0.5 | 2.09 min | 980,342 |
| Carvalho | 0.5 | 7.46 min | 2,239,603 |
| Rodrigues | 0.8 | 12.44 min | 4,923,511 |
| Carvalho | 0.8 | 15.01 min | 2,393,939 |

In the recorded sparse-graph experiments (`p = 0.5`), Rodrigues was faster on average and required fewer iterations. For the denser graphs (`p = 0.8`), Rodrigues was faster on average, while Carvalho used fewer iterations. Both formulations reached the 30-minute time limit on some of the larger, denser instances.

These figures describe the runs recorded in the notebook; they are not guaranteed to be reproduced exactly on every machine or with newly generated random graphs.

## Authors

- Gustavo Gurgel Medeiros
- Mário Martins Aragão

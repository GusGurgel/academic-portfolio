# Rice Grain Classification

A machine learning project that compares classification algorithms for distinguishing **Cammeo** and **Osmancik** rice grains using numerical features extracted from grain images.

This repository contains the notebook developed for **Machine Learning — Practical Assignment 1**.

## Project Overview

The goal is to build, tune, and evaluate binary classification models using the [Rice (Cammeo and Osmancik) dataset](https://archive.ics.uci.edu/dataset/545/rice+cammeo+and+osmancik) from the UCI Machine Learning Repository.

- **Task:** Binary classification
- **Dataset size:** 3,810 instances
- **Input features:** 7 numerical features
- **Target classes:** `Cammeo` and `Osmancik`
- **Notebook:** Jupyter Notebook (`.ipynb`)

## Dataset

Each instance describes a rice grain using these seven features:

| Feature | Description |
|---|---|
| `Area` | Grain area measured from its image |
| `Perimeter` | Grain perimeter |
| `Major_Axis_Length` | Length of the grain's major axis |
| `Minor_Axis_Length` | Length of the grain's minor axis |
| `Eccentricity` | Measure of how elongated the grain is |
| `Convex_Area` | Area of the grain's convex hull |
| `Extent` | Ratio describing how much of its bounding rectangle is occupied by the grain |

The notebook creates a binary target named `isCammeo`: `1` for Cammeo and `0` for Osmancik.

The dataset is downloaded from the UCI repository automatically when the expected ARFF file is not already present. The notebook extracts it into a local `data/` directory.

## Models and Methods

The notebook explores and compares the following classifiers:

- **Logistic Regression**
- **Support Vector Classifier (SVC / SVM)**
- **Random Forest Classifier**

The workflow includes:

1. Loading and inspecting the dataset.
2. Exploratory data analysis and feature visualization.
3. Splitting the data into training (70%) and test (30%) sets, using stratification and a fixed random seed.
4. Comparing models trained with and without feature scaling using `StandardScaler`.
5. Hyperparameter tuning with `GridSearchCV` and, for Random Forest, `RandomizedSearchCV`.
6. Evaluating the models using accuracy, precision, recall, F1-score, ROC-AUC, confusion matrices, and ROC curves.
7. Comparing training and test results to help assess generalization and potential overfitting.

Hyperparameter searches use ROC-AUC as the selection metric. Scaling is fitted on the training data and then applied to the test data to avoid data leakage.

## Main Findings

Based on the results reported in the notebook:

- **Logistic Regression without feature scaling** achieved the best overall test performance, with an **F1-score of 0.9344** and **ROC-AUC of 0.9797**.
- Logistic Regression with scaling performed similarly, suggesting that scaling did not provide a meaningful improvement for this model on this dataset.
- Random Forest models were also competitive, with test F1-scores around **0.925**.
- SVM performance was strongly affected by scaling: the scaled model achieved an F1-score of **0.9189**, while the unscaled version achieved **0.7312**.

These findings are specific to the split, preprocessing, and tuning procedures used in this notebook.

## Requirements

The project uses Python and the following libraries:

- NumPy
- pandas
- Matplotlib
- SciPy
- scikit-learn
- Jupyter Notebook

## Getting Started

### 1. Clone or download the project

Place the notebook in your project directory.

### 2. Create and activate a virtual environment (recommended)

```bash
python -m venv .venv
```

Activate it on Linux/macOS:

```bash
source .venv/bin/activate
```

Activate it on Windows PowerShell:

```powershell
.venv\Scripts\Activate.ps1
```

### 3. Install dependencies

```bash
python -m pip install numpy pandas matplotlib scipy scikit-learn notebook
```

### 4. Launch Jupyter Notebook

```bash
jupyter notebook
```

Open the assignment notebook in the Jupyter interface and run the cells from top to bottom. The notebook downloads and extracts the dataset automatically if it is not already available.

**Note:** Hyperparameter searches—especially Random Forest randomized search—may take some time depending on your hardware.

## Project Structure

A typical layout after the dataset has been downloaded is:

```text
rice-grain-classification/
├── README.md
├── <assignment-notebook>.ipynb
└── data/
    └── Rice_Cammeo_Osmancik.arff
```

The notebook filename can be kept as provided or renamed to something descriptive, such as `rice-grain-classification.ipynb`.

## Authors

- Gustavo Gurgel Medeiros
- Mário Martins Aragão
- Matheus Conrado Pires

## References

- UCI Machine Learning Repository: [Rice (Cammeo and Osmancik)](https://archive.ics.uci.edu/dataset/545/rice+cammeo+and+osmancik)
- scikit-learn documentation: [Preprocessing data](https://scikit-learn.org/stable/modules/preprocessing.html), [Model selection and evaluation](https://scikit-learn.org/stable/model_selection.html)

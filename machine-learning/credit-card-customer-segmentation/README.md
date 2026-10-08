# Credit Card Customer Segmentation

A machine learning project that explores unsupervised learning techniques to segment credit card customers based on their spending and payment behavior.

This repository contains the notebook developed for **Machine Learning — Practical Assignment 2**.

## Project Overview

The goal is to identify groups of customers with similar financial behavior using clustering algorithms. These segments can help inform customer analysis and marketing strategies.

- **Task:** Unsupervised learning / customer segmentation
- **Dataset:** Credit Card Dataset for Clustering
- **Instances:** 8,950 customers
- **Features:** 18 columns in the original dataset
- **Notebook:** Jupyter Notebook (`.ipynb`)

## Dataset

The project uses the [Credit Card Dataset for Clustering](https://www.kaggle.com/datasets/arjunbhasin2013/ccdata), which contains customer credit-card behavior over a period of six months.

The dataset includes information such as:

- Account balance and balance update frequency
- Total purchases, one-off purchases, and installment purchases
- Cash advances and cash-advance frequency
- Purchase frequency and transaction counts
- Credit limit and payment amounts
- Minimum payments, full-payment percentage, and account tenure

`CUST_ID` identifies each customer and is not a behavioral feature for clustering.

## Data Preparation and Exploration

The notebook explores the data through descriptive statistics, feature histograms, and a correlation visualization.

Two columns contain missing values:

- `MINIMUM_PAYMENTS`
- `CREDIT_LIMIT`

The missing values are imputed using each column's mean. The numerical behavioral features are then standardized with `StandardScaler` so that features with larger numeric ranges do not dominate distance-based clustering.

## Clustering Algorithms

Three clustering approaches are implemented and compared:

### K-Means

- Uses the elbow and silhouette visualizers to investigate candidate values for the number of clusters.
- Compares candidate cluster counts using silhouette, Davies–Bouldin, and Calinski–Harabasz scores.
- Uses **k = 3** for the reported K-Means evaluation.
- Visualizes the resulting groups using PCA and t-SNE in two and three dimensions.

### DBSCAN

- Groups points based on density and can label outliers as noise (`-1`).
- Starts with an initial parameter configuration and then searches across `eps` and `min_samples` values.
- Selects the best tested configuration using the silhouette score.
- Uses PCA and t-SNE projections to visualize the resulting clusters.

### Hierarchical Clustering

- Uses a Ward-linkage dendrogram to explore possible cluster counts.
- Evaluates an agglomerative clustering model with **4 clusters**.
- Visualizes the clusters using PCA and t-SNE.

## Evaluation Metrics

The models are compared using three internal clustering metrics:

| Metric | Preferred direction | What it measures |
|---|---|---|
| Silhouette Score | Higher is better | How well-separated and cohesive the clusters are |
| Davies–Bouldin Index | Lower is better | Similarity between clusters, considering their spread |
| Calinski–Harabasz Index | Higher is better | Ratio of between-cluster dispersion to within-cluster dispersion |

These metrics evaluate cluster structure without requiring predefined class labels. Their scales differ, so they should be interpreted individually rather than compared directly with one another.

## Reported Results

The notebook's final comparison reports the following values:

| Algorithm | Configuration | Silhouette Score | Davies–Bouldin Index | Calinski–Harabasz Index |
|---|---|---:|---:|---:|
| K-Means | `k = 3` | 0.2506 | 1.5973 | 1604.40 |
| Hierarchical | `n_clusters = 4` | 0.1547 | 1.7762 | 1255.6049 |
| DBSCAN | Best tested parameters | 0.7274 | 0.3376 | 87.5421 |

According to the notebook's reported comparison, **DBSCAN performs best on silhouette and Davies–Bouldin**, suggesting more cohesive and better-separated clusters under that evaluation. K-Means has the highest Calinski–Harabasz score.

The metrics do not all favor the same model. Also, DBSCAN can classify some observations as noise, so its scores should be interpreted in light of how noise points were handled during evaluation. The results describe this notebook's preprocessing and parameter search; they do not establish that one algorithm is universally best for customer segmentation.

## Requirements

The notebook uses Python and the following libraries:

- `kagglehub`
- `pandas`
- `numpy`
- `matplotlib`
- `seaborn`
- `scikit-learn`
- `yellowbrick`
- `scipy`

## Getting Started

### 1. Clone or download the project

Place the notebook in the project directory.

### 2. Create and activate a virtual environment (recommended)

```bash
python -m venv .venv
```

On Linux/macOS:

```bash
source .venv/bin/activate
```

On Windows PowerShell:

```powershell
.venv\Scripts\Activate.ps1
```

### 3. Install dependencies

```bash
python -m pip install kagglehub pandas numpy matplotlib seaborn scikit-learn yellowbrick scipy notebook
```

### 4. Configure Kaggle access

The notebook downloads the dataset using `kagglehub`. Follow the [KaggleHub authentication instructions](https://github.com/Kaggle/kagglehub) if your environment asks you to authenticate or accept dataset access requirements.

### 5. Launch Jupyter Notebook

```bash
jupyter notebook
```

Open the assignment notebook and run the cells from top to bottom. The dataset is downloaded by the notebook when the data-loading cell runs.

**Note:** The parameter search for DBSCAN evaluates many combinations and may take some time depending on your hardware.

## Project Structure

A typical repository layout is:

```text
credit-card-customer-segmentation/
├── README.md
└── <assignment-notebook>.ipynb
```

The notebook filename can be kept as provided or renamed to something descriptive, such as `credit-card-customer-segmentation.ipynb`.

## Authors

- Gustavo Gurgel Medeiros
- Mário Martins Aragão
- Matheus Conrado Pires

## References

- Kaggle: [Credit Card Dataset for Clustering](https://www.kaggle.com/datasets/arjunbhasin2013/ccdata)
- scikit-learn: [Clustering](https://scikit-learn.org/stable/modules/clustering.html)
- scikit-learn: [Clustering performance evaluation](https://scikit-learn.org/stable/modules/clustering.html#clustering-performance-evaluation)
- KaggleHub: [Documentation and authentication](https://github.com/Kaggle/kagglehub)

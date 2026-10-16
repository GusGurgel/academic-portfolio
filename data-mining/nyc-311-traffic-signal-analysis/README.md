# Traffic Signal Complaint Analysis in New York City

Final project for the **Data Mining** course. This project explores New York City's 311 service requests to identify where traffic-signal issues are reported most often and which types of problems recur at high-volume locations.

## Research Question

**Which areas of New York City have the highest number of traffic-signal complaints, and what are the most frequently reported problems?**

Understanding these patterns can help identify locations that may merit closer inspection and support discussions about traffic-signal maintenance, street safety, and urban mobility.

## Dataset

The analysis uses a filtered extract of the **311 Service Requests from 2020 to Present** dataset published by the [New York City Open Data Portal](https://data.cityofnewyork.us/Social-Services/311-Service-Requests-from-2020-to-Present/erm2-nwe9/about_data).

The notebook focuses on records categorized as **Traffic Signal Condition** and covers the period from **January 1, 2020, to February 25, 2025**, according to the dataset extract used in the analysis.

- **Publisher:** NYC Open Data / NYC 311
- **Geographic scope:** New York City's five boroughs
- **Main fields used:** borough, location, latitude, longitude, address type, intersection streets, and problem descriptor
- **Dataset file expected by the notebook:** `data/Traffic_Sigal_Condition.csv`

The full 311 dataset is updated regularly, so current downloads may differ from the extract used in this project. For reproducible results, use the same CSV snapshot or create a new filtered extract and document its date and filtering criteria. You can also consult the city's [DOT Street Lights and Traffic Signals dataset](https://data.cityofnewyork.us/dataset/jwvp-gyiq) for related data.

## Analysis Workflow

The notebook performs the following steps:

1. Loads the traffic-signal subset into a pandas DataFrame.
2. Removes fields that are unnecessary for the analysis or contain little usable information.
3. Cleans records with missing descriptors, boroughs, or locations.
4. Creates a standardized incident-location field. For intersections, the two street names are combined; otherwise, the incident address is used.
5. Explores geographic and categorical patterns through visualizations.

## Visualizations

The notebook includes four main views:

1. **Incidents by borough** — compares the number and share of traffic-signal reports across New York City's boroughs.
2. **Geographic density map** — highlights areas with higher concentrations of reported incidents.
3. **High-frequency locations in Brooklyn and Queens** — focuses on locations with more than 150 reports to identify potential hotspots.
4. **Problem types at five high-frequency intersections** — compares the reported problem descriptors at selected intersections.

## Key Findings

Based on the dataset extract analyzed in the notebook:

- **Brooklyn and Queens account for 63.6% of the reports combined.** Brooklyn represents 35.4% and Queens 28.2% of the incidents counted in the borough comparison.
- The geographic density map also highlights concentrations in **Brooklyn, Queens, and Manhattan**.
- Five intersections in Brooklyn and Queens stand out with more than 150 reports each, substantially above the notebook's reported average of **11.77 incidents per location**.
- **Controller-related issues account for 61.38% of the problem reports analyzed across those selected intersections**, making them the most prominent descriptor in that subset.

These findings describe patterns in 311 service requests, not necessarily independently verified equipment failures. Report counts alone do not establish the underlying cause of an issue or measure risk-adjusted failure rates.

## Technologies

- **Python** — analysis and data processing
- **pandas** — data manipulation
- **Matplotlib** and **Seaborn** — static charts
- **Plotly Express** — interactive geographic density map
- **scikit-learn** — preprocessing pipeline
- **Jupyter Notebook** — interactive analysis environment

## Getting Started

### 1. Clone the repository

```bash
git clone <repository-url>
cd <repository-directory>
```

### 2. Create and activate a virtual environment

```bash
python -m venv .venv
source .venv/bin/activate
```

On Windows, activate the environment with:

```powershell
.venv\Scripts\Activate.ps1
```

### 3. Install dependencies

```bash
pip install pandas matplotlib seaborn plotly scikit-learn jupyter
```

### 4. Prepare the data

Place the filtered CSV at the following path, which is referenced by the notebook:

```text
data/Traffic_Sigal_Condition.csv
```

The file should contain the traffic-signal records used for the analysis. If you generate it from the full 311 dataset, filter for the traffic-signal condition category and keep a note of the extraction date and time range.

### 5. Run the notebook

```bash
jupyter notebook 04.E1-Exercicio-Visualizacao-de-Dados.ipynb
```

Run the cells in order to reproduce the data preparation steps and visualizations.

## Intended Audience

This exploration may be useful to city transportation and infrastructure departments, traffic-safety teams, urban researchers, mobility organizations, and residents interested in public-service reporting patterns.

## Limitations

- The analysis uses a specific extract ending on February 25, 2025; it does not automatically represent newer requests.
- 311 reports are service requests and may not correspond one-to-one with confirmed technical faults.
- Raw report counts do not account for differences in population, traffic volume, reporting behavior, or the time each signal has been in service.
- Missing or inconsistent location information may affect geographic comparisons.

## Data Source

- [311 Service Requests from 2020 to Present — NYC Open Data](https://data.cityofnewyork.us/Social-Services/311-Service-Requests-from-2020-to-Present/erm2-nwe9/about_data)
- [DOT Street Lights and Traffic Signals — NYC Open Data](https://data.cityofnewyork.us/dataset/jwvp-gyiq)

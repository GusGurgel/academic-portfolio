# Sparse Matrix in C++ and CLI App

Implementation of the Abstract Data Type (ADT) **SparseMatrix** in C++ using orthogonal circular singly-linked lists (rows and columns) with sentinel nodes. Developed for the Data Structures course (QXD0010) at Universidade Federal do Ceará (UFC) - Campus Quixadá.

## Repository Documents

- [📄 Project Specification (PDF)](./projeto-matrizes-esparsas.pdf)
- [📄 Technical Report (PDF)](./relatorio.pdf)

---

## CLI Commands (`main.cpp`)

<p align="center" >
  <img width="400" src="./matrix-manipulator-showcase.gif" alt="Project Showcase">
</p>

| Command | Description |
| :--- | :--- |
| `create [m] [n]` | Creates a new matrix with dimensions $m \times n$. |
| `create_by_read [file_name]` | Loads a matrix from a `.txt` file. |
| `create_by_sum [idx1] [idx2]` | Stores a new matrix resulting from $idx1 + idx2$. |
| `create_by_mult [idx1] [idx2]` | Stores a new matrix resulting from $idx1 \times idx2$. |
| `insert [idx] [i] [j] [val]` | Inserts a value at cell $(i, j)$ of matrix `idx`. |
| `print [idx]` / `printAll` | Displays the matrix at index `idx` or all matrices. |
| `sum [idx1] [idx2]` / `mult [idx1] [idx2]` | Prints the operation result without storing. |
| `delete [idx]` | Deallocates and removes the matrix from the vector. |
| `exit` | Terminates the application. |

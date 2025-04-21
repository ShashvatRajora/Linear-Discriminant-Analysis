# 🧠 Linear Discriminant Analysis (LDA) from Scratch in C

## 🔍 Overview

This project implements **Linear Discriminant Analysis (LDA)** entirely in **pure C** to perform supervised dimensionality reduction on a dataset of 80 grayscale face images with 1024 pixel features each.

We compute the top LDA directions and project the data into:
- **1D** (for classification or histogram)
- **2D** (for visualization via scatter plot)

No external C libraries (like GSL or LAPACK) were used — only clean C code with custom matrix math and power iteration.

---

## 🧠 Why LDA and Not PCA?

| LDA                          | PCA                          |
|-----------------------------|------------------------------|
| Uses class labels           | Ignores class labels         |
| Maximizes class separation  | Maximizes variance           |
| Best for classification     | Best for compression         |
| Outputs ≤ (n_classes - 1)   | Outputs ≤ min(samples, features) |

PCA doesn’t know what class your data belongs to — LDA does.

---

## 🧾 Dataset

- **Samples**: 80
- **Features**: 1024 (each sample is a 32×32 grayscale image)
- **Classes**: 2 (first 40 = class 0, last 40 = class 1)
- **Format**: `unsigned char image[80][1024]` in `data-face80.h`

---

## ⚙️ Implementation Details

### 🔧 Files

| File | Purpose |
|------|---------|
| `main.c` | Entry point |
| `lda.c` / `lda.h` | Compute means, SW, SB |
| `matrix.c` / `matrix.h` | Basic matrix functions |
| `pure_math.c` / `pure_math.h` | Power iteration, Gauss-Jordan inversion |
| `lda_eigen.c` / `lda_eigen.h` | 1D projection (SB-only LDA) |
| `lda_2d.c` / `lda_2d.h` | 2D projection via Gram-Schmidt |
| `lda_projection.csv` | 1D projection output |
| `lda_2d_projection.csv` | 2D projection output |
| `lda_2d_plot.py` | 2D visualization in Python |

---

### 🧪 Steps Performed

1. Convert image data to `double`
2. Compute:
   - Per-class mean vectors
   - Overall mean
   - Scatter matrices (SW and SB)
3. Skip inversion (SW is singular) and run **power iteration on SB**
4. Project data to:
   - 1D: dominant eigenvector
   - 2D: orthogonalized second vector
5. Save to `.csv`
6. Visualize with `matplotlib`

---

## 🧠 Challenges Faced

- **Matrix inversion failed** due to `features > samples` (SW not full rank)
- Solved by:
  - Removing inversion step
  - Using **power iteration on SB**
- Needed to implement:
  - Gauss-Jordan elimination manually
  - Eigenvector estimation (power iteration)
  - Orthogonalization (Gram-Schmidt)

---

## 💾 How to Compile & Run (Pure C)

Before running the files , remove all files from each dedicated folder and place inside a single folder , then execute the command .

```bash
gcc -o lda.exe main.c lda.c matrix.c lda_eigen.c lda_2d.c pure_math.c -lm
./lda.exe

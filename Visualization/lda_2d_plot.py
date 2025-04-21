import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load projection data
df = pd.read_csv("lda_2d_projection.csv", header=None, names=["x", "y", "label"])

# Split classes
class0 = df[df["label"] == 0]
class1 = df[df["label"] == 1]

# Plot data points
plt.figure(figsize=(8, 6))
plt.scatter(class0["x"], class0["y"], color='red', label="Class 0", alpha=0.7, edgecolors='k')
plt.scatter(class1["x"], class1["y"], color='blue', label="Class 1", alpha=0.7, edgecolors='k')

# Calculate class means
mean0 = class0[["x", "y"]].mean()
mean1 = class1[["x", "y"]].mean()

# Midpoint between class centers
midpoint = (mean0 + mean1) / 2

# Direction vector between class means
direction = mean1 - mean0

# Orthogonal direction (rotate 90°)
normal = np.array([-direction["y"], direction["x"]])
normal = normal / np.linalg.norm(normal)

# Create line in orthogonal direction
line_length = 5000
line_x = np.linspace(midpoint["x"] - line_length * normal[0], midpoint["x"] + line_length * normal[0], 100)
line_y = np.linspace(midpoint["y"] - line_length * normal[1], midpoint["y"] + line_length * normal[1], 100)

# Plot discriminant line
plt.plot(line_x, line_y, 'k--', label='Discriminant Boundary', linewidth=2)

# Finish plot
plt.xlabel("LDA Component 1")
plt.ylabel("LDA Component 2")
plt.title("2D LDA Projection with Discriminant Line")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

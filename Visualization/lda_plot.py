import matplotlib.pyplot as plt
import pandas as pd

# Load CSV
df = pd.read_csv("lda_projection.csv", header=None, names=["projection", "label"])

# Split by class
class0 = df[df["label"] == 0]["projection"]
class1 = df[df["label"] == 1]["projection"]

# Plot
plt.figure(figsize=(10, 4))
plt.hist(class0, bins=20, alpha=0.7, label="Class 0")
plt.hist(class1, bins=20, alpha=0.7, label="Class 1")
plt.xlabel("Projection Value")
plt.ylabel("Frequency")
plt.title("LDA 1D Projection of Face Images")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

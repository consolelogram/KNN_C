# K-Nearest Neighbors (KNN) from Scratch in C

This project is a **from-scratch implementation of K-Nearest Neighbors (KNN) in C**, built to understand how ML algorithms actually work at the memory and systems level
## What this does

* Implements **KNN classification** in pure C
* Uses **Euclidean distance (squared)** for efficiency
* Works for **N-dimensional points**

This is a *lazy learner*: there is no training phase beyond storing the dataset.

## Dataset used
Two classes, encoded as integers:
* `0` → blue
* `1` → red
Each point is 2-dimensional.
Example query point: (3, 3)

## Code structure
* **Point**
  * dynamic array of floats
  * dimension metadata

* **LabeledPoint**
  * a `Point`
  * an integer label

* **Dataset**
  * array of `LabeledPoint`
  * count

* **KNN**
  * `k` (number of neighbors)
  * pointer to `Dataset`

* **Distance computation**
  * squared Euclidean distance (no `sqrt`, ordering preserved)

* **Prediction**
  * compute distance to all points
  * sort `(distance, label)` pairs
  * vote among top `k`
  * return predicted label

## How to build and run

```bash
gcc knn.c -o knn -lm
./knn
```

Expected output includes:

* distances from query to each dataset point
* predicted label
* predicted class name

## What this is *not*
* Not optimized
* Not generic over arbitrary label sets

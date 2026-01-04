# K-Nearest Neighbors (KNN) from Scratch in C

This project is a **from-scratch implementation of K-Nearest Neighbors (KNN) in C**, built to understand how ML algorithms actually work at the memory and systems level — **including on microcontrollers**.

## What this does

* Implements **KNN classification** in pure C
* Uses **squared Euclidean distance** (no `sqrt`, ordering preserved)
* Works for **N-dimensional points**
* Includes a **desktop C version** and an **Arduino-compatible embedded version**

This is a *lazy learner*: no training phase beyond storing the dataset.

## Dataset used

Two classes, encoded as integers:

* `0` → blue
* `1` → red

Each point is 2-dimensional.
Example query point: `(3, 3)`

## Code structure (Desktop C)

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

  * squared Euclidean distance

* **Prediction**

  * compute distance to all points
  * sort `(distance, label)` pairs
  * vote among top `k`
  * return predicted label

## Arduino KNN (Embedded Version)

A **memory-constrained KNN implementation** adapted for Arduino-class devices.

Key differences from desktop version:

* **Static arrays only** (no `malloc`)
* Fixed:

  * number of points
  * dimensionality
  * `k`
* Uses `float` math supported by AVR
* Classification result is mapped to **hardware output**

  * e.g. **LED color** (red / blue)

### What the Arduino version demonstrates

* ML inference on **bare-metal hardware**
* How algorithmic ideas survive without libraries
* Tradeoffs forced by RAM, flash, and clock speed
* Practical edge ML, not toy pseudocode

This version proves KNN can run on devices with **kilobytes of memory**, not just laptops.

## How to build and run (Desktop)

```bash
gcc knn.c -o knn -lm
./knn
```

Expected output includes:

* distances from query to each dataset point
* predicted label
* predicted class name

## How to run (Arduino)

* Upload via Arduino IDE
* Open Serial Monitor to view distances and prediction
* LED output reflects predicted class

## What this is *not*

* Not optimized
* Not probabilistic
* Not generic over arbitrary label sets

It’s intentionally raw — the point is **understanding**, not speed.

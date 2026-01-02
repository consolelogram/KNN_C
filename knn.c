#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float *values;   // dynamic array of coordinates
    int dim;         // number of dimensions
} Point;

typedef struct {
    Point point;     // the actual point
    int label;       // class label 0 for blue 1 for red on and on 
} LabeledPoint;

typedef struct {
    LabeledPoint *points;  // array of labeled points
    int count;             // number of points
} Dataset;
typedef struct {
    int k;
    Dataset *dataset;
} KNN;


float euclidean_distance_sq(const float *p, const float *q, int dim);
KNN *knn_create(int k);
void knn_fit(KNN *knn, Dataset *ds);
Dataset make_dataset();

Dataset make_dataset() {
		Dataset ds;
		ds.count = 10;
		ds.points = malloc(ds.count * sizeof(LabeledPoint));

		float blue[][2] = {{2,4},{1,3},{2,3},{3,2},{2,1}};
		float red[][2]  = {{5,6},{4,5},{4,6},{6,6},{5,4}};

		int idx = 0;

		// blue = label 0
		for (int i = 0; i < 5; i++) {
			ds.points[idx].label = 0;
			ds.points[idx].point.dim = 2;
			ds.points[idx].point.values = malloc(2 * sizeof(float));
			ds.points[idx].point.values[0] = blue[i][0];
			ds.points[idx].point.values[1] = blue[i][1];
			idx++;
		}

		// red = label 1
		for (int i = 0; i < 5; i++) {
			ds.points[idx].label = 1;
			ds.points[idx].point.dim = 2;
			ds.points[idx].point.values = malloc(2 * sizeof(float));
			ds.points[idx].point.values[0] = red[i][0];
			ds.points[idx].point.values[1] = red[i][1];
			idx++;
		}

		return ds;
	}


int main(){
	
	Point new_point;
	new_point.dim = 2;
	new_point.values = malloc(2 * sizeof(float));
	new_point.values[0] = 3.0f;
	new_point.values[1] = 3.0f;
	
	Dataset ds = make_dataset();
	
	// calling 
	KNN *knn = knn_create(3);
	knn_fit(knn, &ds);
	
	//for (int i = 0; i < ds.count; i++) {
        //float d = euclidean_distance_sq(ds.points[i].point.values, new_point.values, ds.points[i].point.dim);
        //printf("distance %d = %f\n", i, d);
    //}
	
	typedef struct {
    float distance;
    int label;
	} DistLabel;

	int cmp_dist(const void *a, const void *b) {
		float d1 = ((DistLabel *)a)->distance;
		float d2 = ((DistLabel *)b)->distance;
		return (d1 > d2) - (d1 < d2);
	}

	int knn_predict(KNN *knn, Point *query) {
		Dataset *ds = knn->dataset;
		int n = ds->count;
		DistLabel *pairs = malloc(n * sizeof(DistLabel));

		// compute distances
		for (int i = 0; i < n; i++) {
			pairs[i].distance = euclidean_distance_sq(ds->points[i].point.values, query->values, query->dim);
			pairs[i].label = ds->points[i].label;
		}

		// sort by distance
		qsort(pairs, n, sizeof(DistLabel), cmp_dist);

		// vote (assume small number of labels, like your example)
		int counts[10] = {0};   // supports labels 0–9
		for (int i = 0; i < knn->k; i++) {
			counts[pairs[i].label]++;
		}

		// find max
		int best_label = 0;
		for (int i = 1; i < 10; i++) {
			if (counts[i] > counts[best_label]) {
				best_label = i;
			}
		}
		free(pairs);
		return best_label;
	}
	
	int pred = knn_predict(knn, &new_point);
	printf("predicted label = %d\n", pred);

	const char *names[] = {"blue", "red"};
	printf("predicted class = %s\n", names[pred]);

	
	// free up memory for all three 	
	for (int i = 0; i < ds.count; i++) {
        free(ds.points[i].point.values);
	}
	free(ds.points);
	free(new_point.values);	
	free(knn);
}

float euclidean_distance_sq(const float *p, const float *q, int dim) {
    float sum = 0.0f;
    for (int i = 0; i < dim; i++) {
        float diff = p[i] - q[i];
        sum += diff * diff;
    }
    return sum;
}

// initialize
KNN *knn_create(int k) {
    KNN *knn = malloc(sizeof(KNN));
    knn->k = k;
    knn->dataset = NULL;
    return knn;
}
// fitting 
void knn_fit(KNN *knn, Dataset *ds) {
    knn->dataset = ds;
}

#define MAX_POINTS 10
#define DIM 2
#define K 3
#define LED_RED  9
#define LED_BLUE 8


// Each point is [x, y]
float points[MAX_POINTS][DIM] = {
    {2.0f, 4.0f},
    {1.0f, 3.0f},
    {2.0f, 3.0f},
    {3.0f, 2.0f},
    {2.0f, 1.0f},

    {5.0f, 6.0f},
    {4.0f, 5.0f},
    {4.0f, 6.0f},
    {6.0f, 6.0f},
    {5.0f, 4.0f}
};

int labels[MAX_POINTS] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
float query[DIM] = {3.0f, 3.0f};

float best_dist[K];
int best_idx[K];

float euclidean_distance_sq(const float a[DIM], const float b[DIM]) {
    float sum = 0.0f;
    for (int i = 0; i < DIM; i++) {
        float d = a[i] - b[i];
        sum += d * d;
    }
    return sum;
}

int vote_knn(void) {
    int count0 = 0;
    int count1 = 0;

    for (int i = 0; i < K; i++) {
        int idx = best_idx[i];
        if (idx < 0) continue;   // safety

        if (labels[idx] == 0)
            count0++;
        else
            count1++;
    }

    return (count1 > count0) ? 1 : 0;
}

void setup() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, HIGH);

  for (int i = 0; i < K; i++) {
    best_dist[i] = 1e9;   // effectively infinity
  }

  for (int i = 0; i < MAX_POINTS; i++) {
      float d = euclidean_distance_sq(points[i], query); 
      if (d < best_dist[K - 1]) {
          int j = K - 1;
          // shift larger distances to the right
          while (j > 0 && d < best_dist[j - 1]) {
              best_dist[j] = best_dist[j - 1];
              best_idx[j]  = best_idx[j - 1];
              j--;
          }
          // insert new distance and index
          best_dist[j] = d;
          best_idx[j]  = i; 
      }
  }
  int predicted_label = vote_knn();
   // LED output (COMMON ANODE: LOW = ON)
  if (predicted_label == 0) {
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
  }
  else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_BLUE, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

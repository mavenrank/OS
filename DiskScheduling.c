#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    printf("\nFCFS Order of Requests: %d", head);

    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (FCFS): %d\n", total_movement);
}

void sstf(int requests[], int n, int head) {
    int total_movement = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nSSTF Order of Requests: %d", head);

    for (int i = 0; i < n; i++) {
        int min_distance = __INT_MAX__;
        int closest = -1;

        // Find the closest unvisited request
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - head) < min_distance) {
                min_distance = abs(requests[j] - head);
                closest = j;
            }
        }

        visited[closest] = 1; // Mark the closest request as visited
        total_movement += min_distance;
        head = requests[closest];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total_movement);
}

void scan(int requests[], int n, int head, int direction) {
    int total_movement = 0;
    int sorted_requests[n];
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];

    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    // Find the position of the head in the sorted list
    int pos = 0;
    while (pos < n && sorted_requests[pos] < head) pos++;

    printf("\nSCAN Order of Requests: %d", head);

    if (direction == 1) {  // Moving right initially
        // Move right to the end of the requests
        for (int i = pos; i < n; i++) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }

        // Reverse direction and move left
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
    } else {  // Moving left initially
        // Move left to the beginning of the requests
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }

        // Reverse direction and move right
        for (int i = pos; i < n; i++) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement (SCAN): %d\n", total_movement);
}

int main() {
    int n, head, direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter head direction for SCAN (0 for left, 1 for right): ");
    scanf("%d", &direction);

    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, direction);

    return 0;
}

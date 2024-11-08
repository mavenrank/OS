#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    bool processed[n];
    for (int i = 0; i < n; i++) processed[i] = false;

    int total_movement = 0;
    printf("\nSSTF Order of Requests: %d", head);

    for (int i = 0; i < n; i++) {
        int min_distance = __INT_MAX__, closest_request = -1;

        for (int j = 0; j < n; j++) {
            if (!processed[j] && abs(requests[j] - head) < min_distance) {
                min_distance = abs(requests[j] - head);
                closest_request = j;
            }
        }

        total_movement += min_distance;
        head = requests[closest_request];
        processed[closest_request] = true;
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total_movement);
}

void scan(int requests[], int n, int head, bool direction) {
    int total_movement = 0;
    printf("\nSCAN Order of Requests: %d", head);

    int sorted_requests[n];
    for (int i = 0; i < n; i++) sorted_requests[i] = requests[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }

    int pos = 0;
    while (pos < n && sorted_requests[pos] < head) pos++;

    if (direction) {  
        for (int i = pos; i < n; i++) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
        for (int i = pos; i < n; i++) {
            total_movement += abs(sorted_requests[i] - head);
            head = sorted_requests[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement (SCAN): %d\n", total_movement);
}

int main() {
    int n, head;
    bool direction;

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

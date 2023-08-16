#include <stdio.h>
#include <string.h>

// Structure to represent an event
struct Event {
    char name[50];  // Event name
    int start;      // Start time (PM)
    int end;        // End time (PM)
};

// Merge two subarrays of events[].
// First subarray is events[l..m]
// Second subarray is events[m+1..r]
void merge(struct Event events[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Event L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = events[l + i];
    for (j = 0; j < n2; j++)
        R[j] = events[m + 1 + j];

    // Merge the temporary arrays back into events[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].end <= R[j].end) {
            events[k] = L[i];
            i++;
        } else {
            events[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        events[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        events[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function for events[]
void mergeSort(struct Event events[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(events, l, m);
        mergeSort(events, m + 1, r);

        // Merge the sorted halves
        merge(events, l, m, r);
    }
}

// Function to schedule events
void scheduleEvents(struct Event events[], int n) {
    int schedule[12] = {0}; // Array to represent the schedule (12 slots from 1 PM to 12 PM)

    // Iterate through each event
    for (int i = 0; i < n; i++) {
        // Check if the event can be scheduled and completed before 7 PM
        if (events[i].end <= 7) {
            int canSchedule = 1;
            for (int j = events[i].start; j < events[i].end; j++) {
                if (schedule[j] == 1) {
                    canSchedule = 0; // Event conflicts with another event
                    break;
                }
            }

            // If the event can be scheduled, update the schedule
            if (canSchedule) {
                for (int j = events[i].start; j < events[i].end; j++) {
                    schedule[j] = 1;
                }
                printf("Scheduled event %s from %d PM to %d PM\n", events[i].name, events[i].start, events[i].end);
            } else {
                printf("Could not schedule event %s\n", events[i].name);
            }
        } else {
            printf("Could not schedule event %s as it extends beyond 7 PM\n", events[i].name);
        }
    }
}

int main() {
    printf("Enter the number of events\n");
    int n;
    scanf("%d", &n);

    // Checks if the number of events is at least 8
    if (n >= 8) {
        struct Event events[n];
        printf("Enter details of %d events \n", n);
        for (int i = 0; i < n; i++) {
            printf("\nEvent %d\n", (i + 1));
            printf("Name: ");
            scanf("%s", events[i].name);
            printf("Start time: ");
            scanf("%d", &events[i].start);
            printf("End time: ");
            scanf("%d", &events[i].end);
            printf("\n");
        }

        // Sort the events based on end time (ascending order)
        mergeSort(events, 0, n - 1);

        // Schedule the events
        scheduleEvents(events, n);
    } 
    else {
        printf("Wrong Input\n");
    }
    return 0;
}
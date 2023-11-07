#include <stdio.h>

int n, nf;
int in[100];
int p[50];
int hit = 0;
int i, j, k;
int pgfaultcnt = 0;

void getData() {
    printf("\nEnter length of page reference sequence: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &in[i]);
    printf("Enter number of frames: ");
    scanf("%d", &nf);
}

void initialize() {
    pgfaultcnt = 0;
    for (i = 0; i < nf; i++)
        p[i] = -1; // Use -1 to indicate that all pages are initially empty.
}

int isHit(int data) {
    hit = 0;
    for (j = 0; j < nf; j++) {
        if (p[j] == data) {
            hit = 1;
            break;
        }
    }
    return hit;
}

void dispPages() {
    printf("Pages in frames: ");
    for (k = 0; k < nf; k++) {
        if (p[k] != -1)
            printf("%d ", p[k]);
    }
    printf("\n");
}

void dispPgFaultCnt() {
    printf("Total number of page faults: %d\n", pgfaultcnt);
}

void fifo() {
    initialize();
    int front = 0;

    for (i = 0; i < n; i++) {
        printf("For %d: ", in[i]);

        if (isHit(in[i]) == 0) {
            p[front] = in[i];
            front = (front + 1) % nf;
            pgfaultcnt++;
            dispPages();
        } else {
            printf("No page fault\n");
        }
    }
    dispPgFaultCnt();
}



void lru() {
    initialize();
    int least[50]; // Store the least recently used indices

    for (i = 0; i < n; i++) {
        printf("\nFor %d :", in[i]);

        if (isHit(in[i]) == 0) {
            int min = 9999;
            int repindex = -1;

            for (j = 0; j < nf; j++) {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--) {
                    if (pg == in[k]) {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    least[j] = -9999;
                }
            }

            for (j = 0; j < nf; j++) {
                if (least[j] < min) {
                    min = least[j];
                    repindex = j;
                }
            }

            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages();
        } else {
            printf("No page fault");
        }
    }
    dispPgFaultCnt();
}

int main() {
    int choice;
    while (1) {
        printf("\nPage Replacement Algorithms\n1. Enter data\n2. LRU\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                getData();
                break;
            case 2:
                lru();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

// optimal  




#include <stdio.h>

int n, nf;
int in[100];
int p[50];
int pgfaultcnt = 0;
int i, j;

void getData() {
    printf("Enter length of page reference sequence: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }

    printf("Enter no of frames: ");
    scanf("%d", &nf);
}

int isHit(int data, int m) {
    for (j = 0; j < m; j++) {
        if (p[j] == data) {
            return 1; // Page hit
        }
    }
    return 0; // Page miss
}

void dispPgFaultCnt() {
    printf("Total no of page faults: %d\n", pgfaultcnt);
}

void optimal() {
    int near[50];
    for (i = 0; i < n; i++) {
        printf("For %d: ", in[i]);

        if (!isHit(in[i], nf)) {
            int replaceIndex = -1;
            int found = 0;
            for (j = 0; j < nf; j++) {
                int page = p[j];
                found = 0;

                for (int k = i + 1; k < n; k++) {
                    if (page == in[k]) {
                        near[j] = k;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    near[j] = n + 1; // Page won't be referenced in the future
                }
            }

            int max = -1;
            for (j = 0; j < nf; j++) {
                if (near[j] > max) {
                    max = near[j];
                    replaceIndex = j;
                }
            }

            if (replaceIndex != -1) {
                p[replaceIndex] = in[i];
                pgfaultcnt++;
            }

            for (j = 0; j < nf; j++) {
                if (p[j] != -1) {
                    printf("%d ", p[j]);
                }
            }
        } else {
            printf("No page fault");
        }

        printf("\n");
    }

    dispPgFaultCnt();
}

int main() {
    int choice;
    getData();

    printf("Page Replacement Algorithms\n1. Optimal\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            optimal();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}




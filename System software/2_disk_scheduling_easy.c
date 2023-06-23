#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int tracks, head, prevHead, requestQ[100], requestSize, seekTime, directionRight, choice;

void FCFS() {
    int previousValue = head;
    printf("\nSeek Sequence: ");
    for (int i = 0; i < requestSize; i++) {
        printf("%d ", requestQ[i]);
        seekTime += abs(previousValue - requestQ[i]);
        previousValue = requestQ[i];
    }
    printf("\nFCFS Seek Time: %d", seekTime);
}

void SCAN() {
    int min_left_of_head = INT_MAX, max_right_of_head = INT_MIN;

    for (int i = 0; i < requestSize; i++) {
        if (requestQ[i] < min_left_of_head && requestQ[i] < head)
            min_left_of_head = requestQ[i]; // Minimum request to the left of HEAD
        if (requestQ[i] > max_right_of_head && requestQ[i] > head)
            max_right_of_head = requestQ[i]; // Maximum request to the right of HEAD
    }

    if (directionRight) {
        seekTime += abs(head - (tracks - 1));
        if (min_left_of_head != INT_MAX)
            seekTime += abs(min_left_of_head - (tracks - 1));
    } else if (!directionRight) {
        seekTime += abs(head - 0);
        if (max_right_of_head != INT_MIN)
            seekTime += abs(max_right_of_head - 0);
    }
    printf("\nSCAN Seek Time: %d", seekTime);
}

void CSCAN() {
    int min_right_of_head = INT_MAX, max_left_of_head = INT_MIN;

    for (int i = 0; i < requestSize; i++) {
        if (requestQ[i] < min_right_of_head && requestQ[i] > head)
            min_right_of_head = requestQ[i]; // Minimum request to the right of HEAD (here Head moves right,left,right)
        if (requestQ[i] > max_left_of_head && requestQ[i] < head)
            max_left_of_head = requestQ[i]; // Maximum request to the left of HEAD (here Head moves left,right,left)
    }

    if (directionRight) {
        seekTime += abs(head - (tracks - 1)) + abs(0 - (tracks - 1));
        if (max_left_of_head != INT_MIN)
            seekTime += abs(max_left_of_head - 0);
    } else if (!directionRight) {
        seekTime += abs(head - 0) + abs(0 - (tracks - 1));
        if (min_right_of_head != INT_MAX)
            seekTime += abs(min_right_of_head - (tracks - 1));
    }

    printf("\nCSCAN Seek Time: %d", seekTime);
}

void main() {
    printf("Enter the no. of tracks: ");
    scanf("%d", &tracks);

    printf("\nEnter previous location of head: ");
    scanf("%d", &prevHead);

    printf("Enter current location of R/W head: ");
    scanf("%d", &head);

    if (head > prevHead)
        directionRight = 1;
    else
        directionRight = 0;

    printf("\nEnter no. of requests: ");
    scanf("%d", &requestSize);

    printf("Enter the requests: ");
    for (int i = 0; i < requestSize; i++) {
        scanf("%d", &requestQ[i]);
    }

    while (choice != 4) {
        printf("\n\n1.FCFS\n2.SCAN\n3.C-SCAN\n4.Exit\n\nEnter Choice:");
        scanf("%d", &choice);

        seekTime = 0;

        switch (choice) {
        case 1:
            FCFS();
            break;
        case 2:
            SCAN();
            break;
        case 3:
            CSCAN();
            break;
        }
    }
}
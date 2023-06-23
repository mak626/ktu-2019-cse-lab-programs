#include <stdio.h>
#include <stdlib.h>

int tracks, head, prevHead, requestQ[100], requestSize, previousValue, seekTime, directionRight, choice;

int compareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SCAN() {
    int curTrack, left[1000], right[1000], l = 0, r = 0, header = head;
    seekTime = 0;

    if (directionRight)
        right[r++] = tracks - 1;
    else
        left[l++] = 0;

    for (int i = 0; i < requestSize; i++) {
        if (requestQ[i] < header)
            left[l++] = requestQ[i];
        else
            right[r++] = requestQ[i];
    }

    qsort(left, l, sizeof(int), compareInt);
    qsort(right, r, sizeof(int), compareInt);

    printf("\nSeek Sequence: ");
    for (int run = 0; run < 2; run++) {

        if (directionRight) {
            for (int i = 0; i < r; i++) {
                curTrack = right[i];
                printf("%d ", curTrack);
                seekTime += abs(curTrack - header);
                header = curTrack;
            }
            directionRight = 0;

        } else {
            for (int i = l - 1; i >= 0; i--) {
                curTrack = left[i];
                printf("%d ", curTrack);
                seekTime += abs(curTrack - header);
                header = curTrack;
            }
            directionRight = 1;
        }
    }

    printf("\nSCAN Seek Time: %d", seekTime);
}

void CSCAN() {
    int curTrack, left[1000], right[1000], l = 0, r = 0, header = head;
    seekTime = 0;

    right[r++] = tracks - 1;
    left[l++] = 0;

    for (int i = 0; i < requestSize; i++) {
        if (requestQ[i] < header)
            left[l++] = requestQ[i];
        else
            right[r++] = requestQ[i];
    }

    qsort(left, l, sizeof(int), compareInt);
    qsort(right, r, sizeof(int), compareInt);

    printf("\nSeek Sequence: ");

    if (directionRight) {
        for (int i = 0; i < r; i++) {
            curTrack = right[i];
            printf("%d ", curTrack);
            seekTime += abs(curTrack - header);
            header = curTrack;
        }

        header = 0;
        seekTime += (tracks - 1);

        for (int i = 0; i < l; i++) {
            curTrack = left[i];
            printf("%d ", curTrack);
            seekTime += abs(curTrack - header);
            header = curTrack;
        }

    } else {
        for (int i = l - 1; i >= 0; i--) {
            curTrack = left[i];
            printf("%d ", curTrack);
            seekTime += abs(curTrack - header);
            header = curTrack;
        }

        header = tracks - 1;
        seekTime += (tracks - 1);

        for (int i = r - 1; i >= 0; i--) {
            curTrack = right[i];
            printf("%d ", curTrack);
            seekTime += abs(curTrack - header);
            header = curTrack;
        }
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
            previousValue = head;
            printf("\nSeek Sequence: ");
            for (int i = 0; i < requestSize; i++) {
                printf("%d ", requestQ[i]);
                seekTime += abs(previousValue - requestQ[i]);
                previousValue = requestQ[i];
            }
            printf("\nFCFS Seek Time: %d", seekTime);
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
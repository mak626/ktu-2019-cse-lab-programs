/*
    M Aswin Kishore
    S5 CS2 41
    Paging
*/

// LFU 4 9 5 0 1 3 2 4 1 0 5
// FIFO 3 7 1 3 0 3 5 6 3
// LRU 4 13 7 0 1 2 0 3 0 4 2 3 0 3 2

#include <limits.h>
#include <stdio.h>

int front = -1, rear = -1, q[100];

void enQueue(int x, int limit)
{
    if (rear == -1)
        rear = front = 0;
    else
        rear = (rear + 1) % limit;

    q[rear] = x;
}

int deQueue(int limit)
{
    int temp = q[front];
    if (rear == front)
        rear = front = -1;
    else
        front = (front + 1) % limit;
    return temp;
}

int deQueuePosition(int limit, int position)
{
    for (int i = position; i != rear; i = (i + 1) % limit)
    {
        q[i] = q[(i + 1) % limit];
    }
    if (rear == front)
        rear = front = -1;
    else if (rear == 0)
        rear = limit - 1;
    else
        rear = rear - 1;
}

int queueContains(int x, int limit)
{
    if (rear == -1)
        return 0;

    if (q[rear] == x)
        return 1;
    for (int i = front; i != rear; i = (i + 1) % limit)
    {
        if (q[i] == x)
            return 1;
    }
    return 0;
}

int isQueueFull(int limit)
{
    return (rear + 1) % limit == front;
}

void initQueue(int limit)
{
    front = rear = -1;
    for (int i = 0; i < limit; i++)
    {
        q[i] = -1;
    }
}

void printQue(int limit, int page, int hit)
{
    if (rear == -1)
        return;

    if (hit)
        printf("%d %c: ", page, 'H');
    else
        printf("%d %c: ", page, 'M');

    for (int j = front;; j = (j + 1) % limit)
    {
        printf("%d ", q[j]);
        if (j == rear)
        {
            printf("\n");
            break;
        }
    }
}

void fcfsPageReplacement(int frames, int page_count, int pages[])
{
    int page_fault = 0;
    printf("\nFCFS Page Replacement\n");
    initQueue(frames);

    for (int i = 0; i < page_count; i++)
    {
        if (queueContains(pages[i], frames))
        {
            printQue(frames, pages[i], 1);
            continue;
        }
        else
        {
            page_fault++;
            if (isQueueFull(frames))
            {
                deQueue(frames);
                enQueue(pages[i], frames);
            }
            else
            {
                enQueue(pages[i], frames);
            }
        }
        printQue(frames, pages[i], 0);
    }
    printf("Page faults:%d\n", page_fault);
    printf("Page hits:%d\n", page_count - page_fault);
}

void leastFrequentlyUsedReplacement(int frames, int page_count, int pages[])
{
    int page_fault = 0;
    printf("\nLeast Frequently Used Page Replacement\n");

    initQueue(frames);
    int hash_table[10000] = {0};

    for (int i = 0; i < page_count; i++)
    {
        if (queueContains(pages[i], frames))
        {
            printQue(frames, pages[i], 1);
            hash_table[pages[i]]++;
            continue;
        }
        else
        {
            page_fault++;
            if (isQueueFull(frames))
            {
                int minFreq = INT_MAX;
                int queReplacePosition;

                for (int j = rear;;)
                {
                    if (hash_table[q[j]] <= minFreq)
                    {
                        minFreq = hash_table[q[j]];
                        queReplacePosition = j;
                    }

                    if (j == front)
                        break;

                    if (j == 0)
                        j = frames - 1;
                    else
                        j--;
                }

                hash_table[q[queReplacePosition]]--;
                deQueuePosition(frames, queReplacePosition);
                enQueue(pages[i], frames);
                hash_table[pages[i]]++;
            }
            else
            {
                enQueue(pages[i], frames);
                hash_table[pages[i]]++;
            }
        }

        printQue(frames, pages[i], 0);
    }
    printf("Page faults:%d\n", page_fault);
    printf("Page hits:%d\n", page_count - page_fault);
}

void leastRecentlyUsedReplacement(int frames, int page_count, int pages[])
{
    int page_fault = 0;
    printf("\nLeast Recently Used Replacement\n");
    initQueue(frames);

    for (int i = 0; i < page_count; i++)
    {
        if (queueContains(pages[i], frames))
        {
            printQue(frames, pages[i], 1);
            continue;
        }
        else
        {
            page_fault++;
            if (isQueueFull(frames))
            {
                int farthestPagePosition = INT_MAX;
                int queReplacePosition = INT_MAX;

                for (int j = front;; j = (j + 1) % frames)
                {
                    for (int k = i - 1; k >= 0; k--)
                    {
                        if (pages[k] == q[j])
                        {
                            if (k < farthestPagePosition)
                            {
                                farthestPagePosition = k;
                                queReplacePosition = j;
                            }
                            break;
                        }
                    }

                    if (j == rear)
                        break;
                }

                q[queReplacePosition] = pages[i];
            }
            else
            {
                enQueue(pages[i], frames);
            }
        }
        printQue(frames, pages[i], 0);
    }
    printf("Page faults:%d\n", page_fault);
    printf("Page hits:%d\n", page_count - page_fault);
}

void main()
{
    int frames, page_count, choice = 0;
    printf("Enter frames no. and page count:");
    scanf("%d %d", &frames, &page_count);
    int pages[100];
    printf("Enter pages:");
    for (int i = 0; i < page_count; i++)
        scanf("%d", &pages[i]);

    while (choice != 4)
    {

        printf("\n\n1.FCFS\n2.LFU\n3.LRU\n4.Exit\n\nEnter Choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfsPageReplacement(frames, page_count, pages);
            break;
        case 2:
            leastFrequentlyUsedReplacement(frames, page_count, pages);
            break;
        case 3:
            leastRecentlyUsedReplacement(frames, page_count, pages);
            break;
        }
    }
}

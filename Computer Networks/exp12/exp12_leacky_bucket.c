#include <stdio.h>

void printBucketSize(int currentBucketSize, int bucketSize)
{
    printf("\nBucket buffer size: %d/%d", currentBucketSize, bucketSize);
}

int main()
{
    int incomingPacketSize, outgoingRate, bucketSize, currentBucketSize = 0, outflow, choice = 1;

    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);
    printf("Enter outgoing rate: ");
    scanf("%d", &outgoingRate);

    while (choice)
    {
        printf("\nEnter the incoming packet size: ");
        scanf("%d", &incomingPacketSize);

        if (incomingPacketSize <= (bucketSize - currentBucketSize))
        {
            currentBucketSize += incomingPacketSize;
        }
        else
        {
            printf("\nDropped packets of size: %d", incomingPacketSize - (bucketSize - currentBucketSize));
            currentBucketSize = bucketSize;
        }

        printBucketSize(currentBucketSize, bucketSize);

        if (currentBucketSize < outgoingRate)
        {
            outflow = currentBucketSize;
            currentBucketSize = 0;
        }
        else
        {
            outflow = outgoingRate;
            currentBucketSize = currentBucketSize - outgoingRate;
        }

        printf("\nOutgoing packet size: %d", outflow);
        printBucketSize(currentBucketSize, bucketSize);

        printf("\n\nDo you want to continue (1/0): ");
        scanf("%d", &choice);
    }
}

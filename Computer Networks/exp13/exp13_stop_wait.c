// Stop-and-Wait Protocol

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int packetSize, packetRecieved, ackRecieved, i;
    printf("\nEnter no.of packets : ");
    scanf("%d", &packetSize);

    srand(time(0)); // sets seed for rand to current_time

    for (i = 1; i <= packetSize; i++)
    {
        printf("\n-> Sending Packet %d", i);

        ackRecieved = rand() % 2;

        if (ackRecieved)
        {
            printf("\n\tAcknowledgement received for Packet %d", i);
        }
        else
        {
            printf("\n\tMissing Acknowledgement for Packet %d", i);
            i--;
        }
    }

    printf("\n");
}

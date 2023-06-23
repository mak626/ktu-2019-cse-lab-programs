#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int packetSize, windowSize, packetsSend = 0, ackRecieved, i;
    printf("Enter number of packets: ");
    scanf("%d", &packetSize);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    srand(time(0));

    while (packetsSend < packetSize)
    {
        int lastTransmittedPacket = packetsSend;

        for (i = 0; i < windowSize; i++)
        {
            if (packetSize == packetsSend)
            {
                break;
            }
            printf("\n-> Sending Packet %d", ++packetsSend);
        }

        for (i = lastTransmittedPacket; i < packetsSend; i++)
        {
            ackRecieved = rand() % 2;
            if (ackRecieved)
            {
                printf("\n\tAcknowledgement received for Packet %d", i + 1);
            }
            else
            {
                printf("\n\tMissing Acknowledgement for Packet %d", i + 1);
                printf("\n\tRetransmitting Window");
                packetsSend = i;
                break;
            }
        }
    }

    printf("\n");
}

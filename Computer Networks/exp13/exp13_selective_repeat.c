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

    int packetState[10000] = {0}, remainingResent = 0;
    // DEFAULT= 0, ACK= 1, NACK= -1

    srand(time(0));

    while (packetsSend < packetSize || remainingResent != 0)
    {
        for (i = 0; i < windowSize; i++)
        {
            if (packetSize == packetsSend)
            {
                break;
            }
            printf("\n-> Sending Packet %d", ++packetsSend);
        }

        for (i = 0; i < packetsSend; i++)
        {
            if (packetState[i] == 1) // Already acknowledged packet
            {
                continue;
            }

            ackRecieved = rand() % 2;
            if (ackRecieved)
            {
                printf("\n\tAcknowledgement received for Packet %d", i + 1);

                if (packetState[i] == -1) // Retransmitted packet
                {
                    remainingResent--;
                }

                packetState[i] = 1;
            }
            else
            {
                printf("\n\tMissing Acknowledgement for Packet %d", i + 1);
                printf("\n-> Retransmitting Packet %d", i + 1);

                if (packetState[i] == 0) // First time transmitted packet
                {
                    remainingResent++;
                }
                packetState[i] = -1;
            }
        }
    }

    printf("\n");
}

#include <stdio.h>

void enque(int priorityQ[], int valueQ[], int size, int rear, int front)
{
    if ((rear + 1) % size == front)
        printf("DeQueue full !");
    else
    {
        int entered_P, entered_V;
        //Get priority and value of new item from user into  entered_P, entered_V respectively

        if (rear == front == -1)
        {
            front = rear = 0;
            priorityQ[rear] = entered_P;
            valueQ[rear] = entered_V;
        }
        else
        {
            int location_to_insert;

            if (priorityQ[rear] <= p)
                // 1 2 3 4 5
                // entered_P = 5 or 6
                // final 1 2 3 4 5 5(or 6)
                location_to_insert = rear + 1;
            else
            {
                // 1 3 4 5
                // entered_P = 2
                // final - 1 2 3 4 5

                // example 2
                // 1 2(old) 3 4 5
                // entered_P = 2(new)
                // final - 1 2(old) 2(new) 3 4 5

                for (int i = front; i != rear; i = (i + 1) % size)
                {

                    //This is a MIN priority que i.e 1 has greater priority than 2
                    if (priorityQ[i] > p) //2 > 1   // > only (refer example 2)
                    {
                        int prev_P = priorityQ[i];
                        int prev_V = valueQ[i];

                        //Shifting all elements to right
                        for (int j = i; j != rear; (j + 1) % size)
                        {
                            int temp_P = priorityQ[(j + 1) % size];
                            int temp_V = valueQ[(j + 1) % size];

                            priorityQ[(j + 1) % size] = prev_P;
                            valueQ[(j + 1) % size] = prev_V;
                            prev_P = temp_P;
                            prev_V = temp_V;
                        }

                        location_to_insert = i;
                        break;
                    }
                }
            }

            priorityQ[location_to_insert] = entered_P;
            valueQ[location_to_insert] = entered_V;
            rear = (rear + 1) % size;
        }
    }
}
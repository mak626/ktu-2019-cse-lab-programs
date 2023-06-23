/*
Write a Java program for the following: 
    1) Create a doubly linked list of elements.
    2) Delete a given element from the above list.
    3) Display the contents of the list after deletion.
*/

import java.util.*;

class DoublyLinkedList
{

    private final LinkedList<Integer> list = new LinkedList<Integer>();

    public boolean isNotEmpty()
    {
        if (list.isEmpty())
            System.out.println("List is empty");

        return !list.isEmpty();
    }

    public void insertAtEnd(int data)
    {
        list.add(data);
    }

    public void insertAtFront(int data)
    {
        list.add(0, data);
    }

    public void insertAtBetween(int data, int key)
    {
        int index = list.indexOf(key);
        if (index != -1)
        {
            list.add(index + 1, data);
        }
        else
        {
            System.out.println("Key not found.Inserting at end");
            insertAtEnd(data);
        }
    }

    public void deleteAtFront()
    {
        list.removeFirst();
    }

    public void deleteAtEnd()
    {
        list.removeLast();
    }

    public void deleteKey(int key)
    {
        int index = list.indexOf(key);
        if (index == -1)
            System.out.println("Key not found");
        else
            list.remove(index);

    }

    public void display(boolean reverse)
    {
        ListIterator<Integer> it;

        System.out.print("\n");

        if (reverse)
        {
            for (it = list.listIterator(list.size()); it.hasPrevious();)
            {
                int data = it.previous();
                if (data == list.getFirst())
                    System.out.print(data + "\n");
                else
                    System.out.print(data + " -> ");
            }
        }
        else
        {
            for (it = list.listIterator(); it.hasNext();)
            {
                int data = it.next();
                if (data == list.getLast())
                    System.out.print(data + "\n");
                else
                    System.out.print(data + " -> ");
            }
        }

    }

}

public class lab16
{

    public static void main(String args[])
    {
        DoublyLinkedList obj = new DoublyLinkedList();
        int data, key, ch;

        do
        {
            System.out.print("\nMenu\n");
            System.out.print("\n1.Insert At Front");
            System.out.print("\n2.Insert In Between");
            System.out.print("\n3.Insert At End");
            System.out.print("\n4.Delete From Front");
            System.out.print("\n5.Delete A Node Of Particular Key");
            System.out.print("\n6.Delete From End");
            System.out.print("\n7.Traversal");
            System.out.print("\n8.Reversal");
            System.out.print("\n9.Exit");
            System.out.print("\n\nEnter choice:");

            Scanner cin = new Scanner(System.in);
            ch = cin.nextInt();

            if (ch == 1)
            {
                System.out.print("Enter data:");
                data = cin.nextInt();
                obj.insertAtFront(data);
            }
            else if (ch == 2)
            {
                System.out.print("Enter data:");
                data = cin.nextInt();
                System.out.print("Enter key:");
                key = cin.nextInt();
                obj.insertAtBetween(data, key);
            }
            else if (ch == 3)
            {
                System.out.print("Enter data:");
                data = cin.nextInt();
                obj.insertAtEnd(data);
            }
            else if (ch == 4 && obj.isNotEmpty())
            {
                obj.deleteAtFront();
            }
            else if (ch == 5 && obj.isNotEmpty())
            {
                System.out.print("Enter key:");
                key = cin.nextInt();
                obj.deleteKey(key);
            }
            else if (ch == 6 && obj.isNotEmpty())
            {
                obj.deleteAtEnd();
            }
            else if (ch == 7 && obj.isNotEmpty())
            {
                obj.display(false);

            }
            else if (ch == 8 && obj.isNotEmpty())
            {
                obj.display(true);
            }

        } while (ch != 9);

    }
}

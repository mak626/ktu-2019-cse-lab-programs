/*
Write a Java program that implements Quick sort algorithm for sorting a list of names in ascending order.
*/

import java.util.*;

public class lab17
{
    public static void main(String args[])
    {

        String data;
        int ch;

        QuickSortArray obj = new QuickSortArray();

        do
        {
            System.out.print("\n\n1.Insert");
            System.out.print("\n2.Display");
            System.out.print("\n3.Quick Sort");
            System.out.print("\n4.Exit");
            System.out.print("\n\nEnter choice:");

            Scanner cin = new Scanner(System.in);
            ch = cin.nextInt();
            cin.nextLine(); // Clearing Buffer

            if (ch == 1)
            {
                System.out.print("Enter data (string):");
                data = cin.nextLine();
                obj.add(data);
            }
            else if (ch == 2)
            {
                obj.print();
            }
            else if (ch == 3)
            {
                obj.sort();
                System.out.println("Array has been sorted in ascending order");
            }

        } while (ch != 4);
    }
}

class QuickSortArray
{
    ArrayList<String> list = new ArrayList<String>();

    void add(String str)
    {
        list.add(str);
    }

    void print()
    {
        System.out.print("\n");
        for (String str : list)
        {
            System.out.println(str);
        }
    }

    void sort()
    {
        quickSort(list, 0, list.size() - 1);
    }

    // quickSort

    void swap(ArrayList<String> arr, int x, int y)
    {
        String temp = arr.get(x);
        arr.set(x, arr.get(y));
        arr.set(y, temp);
    }

    int partition(ArrayList<String> arr, int l, int r)
    {
        String pivot = arr.get(l);
        int start = l;
        int end = r;

        while (start < end)
        {
            try
            {
                while (arr.get(start).compareTo(pivot) <= 0)
                    start++;
                while (arr.get(end).compareTo(pivot) > 0)
                    end--;
            }
            catch (Exception e)
            {
            }

            if (start < end)
                swap(arr, start, end);
        }

        swap(arr, l, end);
        return end;
    }

    void quickSort(ArrayList<String> arr, int l, int r)
    {
        if (l >= r)
            return;

        int pivot = partition(arr, l, r);

        quickSort(arr, l, pivot - 1);
        quickSort(arr, pivot + 1, r);
    }

}
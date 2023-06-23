/*
Write a Java program that implements the binary search algorithm.
*/

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class lab18
{
    public static void main(String[] args)
    {
        Array obj = new Array();
        int search_element, ch, data, index;
        Scanner cin = new Scanner(System.in);

        do
        {
            System.out.print("\n\n1.Add\n2.Delete\n3.Print\n4.Binary Search\n5.Exit\nEnter choice:");
            ch = cin.nextInt();
            if (ch == 1)
            {
                System.out.print("\nEnter number:");
                data = cin.nextInt();
                obj.add(data);
                obj.sort();
            }
            else if (ch == 2)
            {
                System.out.print("\nEnter index:");
                index = cin.nextInt();
                obj.delete(index);
            }
            else if (ch == 3)
            {
                obj.print();
            }
            else if (ch == 4)
            {

                System.out.print("\nEnter search value:");
                search_element = cin.nextInt();

                // int x = Collections.binarySearch(obj.arr, search_element);
                // if (x >= 0)
                // System.out.print("\nElement Found");
                // else
                // System.out.print("\nElement Not Found");
                // OR

                if (obj.binarySearch(search_element, 0, (obj.getSize() - 1)))
                    System.out.print("\nElement Found");
                else
                    System.out.print("\nElement Not Found");
            }
        } while (ch != 5);

    }
}

class Array
{
    ArrayList<Integer> arr = new ArrayList<Integer>();

    public void add(int data)
    {
        arr.add(data);
    }

    public void delete(int index)
    {
        try
        {
            arr.remove(index);
        }
        catch (Exception e)
        {
        }
    }

    public void print()
    {
        System.out.print("\n");
        for (int data : arr)
        {
            System.out.print(data + " ");
        }
    }

    public int getSize()
    {
        return arr.size();
    }

    public void sort()
    {
        Collections.sort(arr);

    }

    public boolean binarySearch(int search_element, int l, int r)
    {
        if (l > r)
            return false;

        int mid = l + (r - l) / 2;

        if (arr.get(mid) == search_element)
            return true;
        else if (arr.get(mid) < search_element)
            return binarySearch(search_element, mid + 1, r);
        else
            return binarySearch(search_element, l, mid - 1);

    }

}
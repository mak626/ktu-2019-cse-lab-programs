//Write a Java program that reads a line of integers, and then displays each integer, and the sum of all the integers (Use String Tokenizer class of java.util)

import java.util.*;

public class lab9
{
    public static void main(String[] args)
    {
        int sum = 0, x;

        Scanner cin = new Scanner(System.in);
        System.out.println("Enter the numbers seperated by spaces:");
        String str = cin.nextLine();
        cin.close();

        StringTokenizer st = new StringTokenizer(str);

        System.out.println("The numbers are: ");
        while (st.hasMoreTokens())
        {
            x = Integer.parseInt(st.nextToken());
            System.out.print(x + " ");
            sum += x;
        }

        System.out.println("\nSum: " + sum);
    }

}

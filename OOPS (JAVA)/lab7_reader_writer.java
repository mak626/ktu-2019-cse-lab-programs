//Write a file handling program in Java with reader/writer

import java.io.*;
import java.util.*;

class lab7
{
    public static void main(String args[]) throws IOException
    {
        try
        {
            int c;

            Scanner cin = new Scanner(System.in);
            System.out.print("\nEnter data to be entered into the file: ");
            String x = cin.nextLine();
            cin.close();

            FileWriter fout = new FileWriter("data.txt");
            fout.write(x);
            fout.close();

            System.out.print("\nReading contents from file:\n");
            FileReader fin = new FileReader("data.txt");

            while ((c = fin.read()) != -1)
            {
                System.out.print((char) c);
            }

            fin.close();

        }
        catch (Exception e)
        {
            System.out.println("Error");
        }
        ;

    }
}

//Write a Java program that read from a file and write to file by handling all file related exceptions

import java.io.*;

class lab8
{
    public static void main(String args[]) throws IOException
    {
        try
        {
            System.out.println("Opening input.txt");
            FileReader fin = new FileReader("input.txt");

            FileWriter fout = new FileWriter("output.txt");
            System.out.println("Copying contents of input.txt to output.txt");

            int c;
            while ((c = fin.read()) != -1)
            {
                fout.write((char) c);
            }

            fin.close();
            fout.close();

        }
        catch (FileNotFoundException e)
        {
            System.out.println("File Not Found");
        }
        catch (IOException e)
        {
            System.out.println("Input Output Error");
        }
        catch (Exception e)
        {
            System.out.println("Error");
        }
        ;

    }
}

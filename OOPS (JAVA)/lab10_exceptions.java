
//Write a Java program that shows the usage of try, catch, throws and finally
import java.io.*;

class lab10
{
    public static void main(String args[]) throws IOException
    {
        try
        {
            int c;

            FileReader fin = new FileReader("data.txt");

            System.out.println("Reading data from file data.txt : ");
            while ((c = fin.read()) != -1)
            {
                System.out.print((char) c);
            }

            fin.close();

        }
        catch (Exception e)
        {
            System.out.println("\nError");
        }
        finally
        {
            System.out.println("\nProgram Terminated");
        }
        ;

    }
}

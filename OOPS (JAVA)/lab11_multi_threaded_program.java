
/*
    Write a Java program that implements a multi-threaded program which has three threads.
    First thread generates a random integer every 1 second. 
    If the value is even ,second thread computes the square of the number and prints. 
    If the value is odd  ,third thread will print the value of cube of the number.
*/
import java.util.Random;

public class lab11
{
    public static void main(String args[])
    {
        Thread1 t1 = new Thread1();
        t1.start();
    }
}

class Thread1 extends Thread
{

    public void run()
    {
        Random rand = new Random();

        for (int i = 0; i < 10; i++)
        {
            int x = rand.nextInt(10);

            if (x % 2 == 0)
            {
                Thread2 t2 = new Thread2(x);
                t2.start();
            }
            else
            {
                Thread3 t3 = new Thread3(x);
                t3.start();
            }

            try
            {
                Thread.sleep(1000);
            }
            catch (InterruptedException e)
            {
                System.out.println(e);
            }

        }
    }
}

class Thread2 extends Thread
{
    int x;

    Thread2(int data)
    {
        this.x = data;
    }

    public void run()
    {
        int y = x * x;
        System.out.println("Square of " + x + " is " + y);
    }

}

class Thread3 extends Thread
{
    int x;

    Thread3(int data)
    {
        this.x = data;
    }

    public void run()
    {
        int y = x * x * x;
        System.out.println("Cube of " + x + " is " + y);
    }

}
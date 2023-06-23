//Write a Java program that shows thread synchronization

public class lab12
{
    public static void main(String args[])
    {
        PrintMultiples obj = new PrintMultiples();

        Thread1 t1 = new Thread1(obj);
        Thread2 t2 = new Thread2(obj);
        t1.start();
        t2.start();
    }
}

class PrintMultiples
{
    synchronized void print(int x)
    {
        for (int i = 1; i <= 5; i++)
            System.out.println(x + "*" + i + " =" + x * i);
        System.out.println();
    }
}

class Thread1 extends Thread
{
    PrintMultiples obj;

    Thread1(PrintMultiples x)
    {
        this.obj = x;
    }

    public void run()
    {
        obj.print(5);
    }

}

class Thread2 extends Thread
{
    PrintMultiples obj;

    Thread2(PrintMultiples x)
    {
        this.obj = x;
    }

    public void run()
    {
        obj.print(2);
    }

}
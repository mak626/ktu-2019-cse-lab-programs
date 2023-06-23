//Garbage collector

class lab6
{
    public static void main(String args[])
    {
        Test ob1 = new Test(15, 20.3f);
        Test ob2 = new Test(343, 32.1f);
        Test ob3 = new Test(23, 10.1f);

        // Ways to unreference an object
        ob1 = null; // Nulling the reference
        System.gc();
        System.runFinalization();

        ob2 = ob3; // Assigning a reference to another object
        System.gc();
        System.runFinalization();

        new Test(2, 2f); // anonymous object
        System.gc();
        System.runFinalization();
    }
}

class Test
{
    int a;
    float b;

    Test(int i, float j)
    {
        a = i;
        b = j;
    }

    @Override
    protected void finalize()
    {
        System.out.println("Garbage Collector called");
        System.out.println("Object garbage collected : " + this);
    }
}
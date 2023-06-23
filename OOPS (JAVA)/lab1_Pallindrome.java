//Pallindrome

public class lab1
{
    public static void main(String[] args)
    {
        char x[] = { 'm', 'a', 'l', 'a', 'y', 'a', 'l', 'a', 'm' };
        System.out.print("String: ");
        for (int i = 0; i < x.length; i++)
            System.out.print(x[i]);

        boolean flag = true;
        for (int i = 0; i < x.length / 2; i++)
        {
            if (x[i] != x[x.length - i - 1])
            {
                System.out.print("\nNot a pallindrome");
                flag = false;
                break;
            }
        }
        if (flag)
            System.out.print("\nIt is a pallindrome");
    }
}
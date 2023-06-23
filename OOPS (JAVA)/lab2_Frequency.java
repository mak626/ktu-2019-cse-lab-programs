//Frequency

public class lab2 {
    public static void main(String args[]) {
        char ch = 'z';
        char x[] = { 'm', 'a', 'l', 'a', 'y', 'a', 'l', 'a', 'm' };
        System.out.print("String: ");
        for (int i = 0; i < x.length; i++)
            System.out.print(x[i]);

        System.out.print("\nElement whose frequency need to be searched: " + ch);
        int count = 0;
        for (int i = 0; i < x.length; i++)
            if (x[i] == ch)
                count++;
        System.out.printf("\nElement '" + ch + "' has a frequency : " + count);
    }
}
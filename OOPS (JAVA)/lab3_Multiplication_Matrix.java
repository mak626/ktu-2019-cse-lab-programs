//Multiplication Matrix

public class lab3
{
    public static void main(String[] args)
    {
        int x[][] = { { 6, 2, 7 }, { 4, 3, 2 }, { 7, 2, 9 } };
        int y[][] = { { 5, 3, 1 }, { 2, 5, 0 }, { 2, 5, 7 } };
        int r1 = x.length, r2 = y.length, c1 = x[0].length, c2 = y[0].length;

        if (c1 == r2)
        {
            int m[][] = new int[r1][c2];
            int i, j, k;

            System.out.print("Product of two matrix:");
            for (i = 0; i < r1; i++)
            {
                System.out.print("\n");
                for (j = 0; j < c2; j++)
                {
                    m[i][j] = 0;
                    for (k = 0; k < c1; k++)
                        m[i][j] += x[i][k] * y[k][j];
                    System.out.print(m[i][j] + " ");
                }

            }
        }
        else
            System.out.print("\nMatrix multiplication not possible");
    }
}
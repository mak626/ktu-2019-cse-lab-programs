//Shapes

public class lab5
{
    public static void main(String args[])
    {
        Rectangle r = new Rectangle();
        Triangle t = new Triangle();
        Hexagon h = new Hexagon();
        r.numberOfSides();
        t.numberOfSides();
        h.numberOfSides();

    }
}

abstract class Shapes
{
    abstract void numberOfSides();
}

class Rectangle extends Shapes
{
    void numberOfSides()
    {
        System.out.println("No. of sides in a rectangle: 4");
    }
}

class Triangle extends Shapes
{
    void numberOfSides()
    {
        System.out.println("No. of sides in a triangle: 3");
    }
}

class Hexagon extends Shapes
{
    void numberOfSides()
    {
        System.out.println("No. of sides in a Hexagon: 6");
    }
}
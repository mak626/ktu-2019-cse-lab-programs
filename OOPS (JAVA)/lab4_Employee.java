//Employee

public class lab4
{
    public static void main(String args[])
    {
        Officer obj1 = new Officer("Jack", "221B Baker Street", 22, 9038898420l, 22000.98f, "Data Science");
        Manager obj2 = new Manager("Vladamir", "X54 Hendsworth Street", 56, 7838898420l, 120000, "CSE");
        obj1.print();
        obj2.print();
    }
}

class Employee
{
    String name, address;
    int age;
    long phone;
    float salary;

    void print()
    {
        System.out.print("Name:" + name);
        System.out.print("\nAddress:" + address);
        System.out.print("\nAge:" + age);
        System.out.print("\nPhone:" + phone);
    }

    void printSalary()
    {
        System.out.print("\nSalary:" + salary + "\n\n");
    }

    Employee(String a, String b, int c, long d, float e)
    {
        name = a;
        address = b;
        age = c;
        phone = d;
        salary = e;
    }

}

class Officer extends Employee
{

    String specialization;

    Officer(String a, String b, int c, long d, float e, String s)
    {
        super(a, b, c, d, e);
        specialization = s;

    }

    void print()
    {
        super.print();
        System.out.print("\nSpecialization:" + specialization);
        printSalary();
    }

}

class Manager extends Employee
{

    String department;

    Manager(String a, String b, int c, long d, float e, String s)
    {
        super(a, b, c, d, e);
        department = s;
    }

    void print()
    {
        super.print();
        System.out.print("\nDepartment:" + department);
        printSalary();
    }

}

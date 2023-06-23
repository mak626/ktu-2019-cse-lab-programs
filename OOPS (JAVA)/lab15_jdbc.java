// Write a Java program to display all records from a table using Java Database Connectivity (JDBC).  

import java.sql.*;

//After compiling Run following command to run the code
//java -classpath ".;sqlite-jdbc-3.34.0.jar" lab15  

public class lab15
{
    public static void main(String args[])
    {
        try
        {
            Connection con = DriverManager.getConnection("jdbc:sqlite:database.db");
            System.out.println("Connected to database.db");

            Statement stmt = con.createStatement();

            System.out.println("Retrieving data from database.db");
            ResultSet rs = stmt.executeQuery("select * from student");

            System.out.printf("\n------------------------------------");
            System.out.printf("\n|%-10s |%-10s |%-10s|", "Roll", "Name", "Marks");
            System.out.printf("\n------------------------------------");

            while (rs.next())
                System.out.printf("\n|%-10d |%-10s |%-10d|", rs.getInt(1), rs.getString(2), rs.getInt(3));

            System.out.printf("\n------------------------------------");

            con.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }
}

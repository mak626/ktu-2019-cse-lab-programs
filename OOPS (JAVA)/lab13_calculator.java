
/*  
Write a Java program that works as a simple calculator. 
Arrange Buttons for digits and the + - * % operations properly. 
Add a text field to display the result. Handle any possible exceptions like divide by zero. Use Java Swing.
*/
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class lab13 implements ActionListener
{
    char operator;
    double num1, num2, result;
    String temp;
    JFrame f;
    JButton b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16, b17,b[];
    JPanel p;
    JTextField tf;

    lab13()
    {
        f = new JFrame("Calculator");
        p = new JPanel();

        f.setLayout(new FlowLayout());

        b1 = new JButton("0");
        b1.addActionListener(this);
        b2 = new JButton("1");
        b2.addActionListener(this);
        b3 = new JButton("2");
        b3.addActionListener(this);
        b4 = new JButton("3");
        b4.addActionListener(this);
        b5 = new JButton("4");
        b5.addActionListener(this);
        b6 = new JButton("5");
        b6.addActionListener(this);
        b7 = new JButton("6");
        b7.addActionListener(this);
        b8 = new JButton("7");
        b8.addActionListener(this);
        b9 = new JButton("8");
        b9.addActionListener(this);
        b10 = new JButton("9");
        b10.addActionListener(this);

        b11 = new JButton("+");
        b11.addActionListener(this);
        b12 = new JButton("-");
        b12.addActionListener(this);
        b13 = new JButton("*");
        b13.addActionListener(this);
        b14 = new JButton("/");
        b14.addActionListener(this);
        b15 = new JButton("%");
        b15.addActionListener(this);
        b16 = new JButton("=");
        b16.addActionListener(this);
        b17 = new JButton("C");
        b17.addActionListener(this);

        tf = new JTextField(11);
        tf.setFont(new Font("Times New Roman", Font.BOLD, 33));
        f.add(tf);

        p.setLayout(new GridLayout(4, 4, 10, 20));
        p.add(b1);
        p.add(b2);
        p.add(b3);
        p.add(b4);
        p.add(b5);
        p.add(b6);
        p.add(b7);
        p.add(b8);
        p.add(b9);
        p.add(b10);
        p.add(b11);
        p.add(b12);
        p.add(b13);
        p.add(b14);
        p.add(b15);
        p.add(b16);
        p.add(b17);
        p.setPreferredSize(new Dimension(300, 300));

        f.addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                f.dispose();
            }
        });

        f.add(p);
        f.setSize(350, 420);
        f.setVisible(true);
    }

    public void actionPerformed(ActionEvent e)
    {

        // Operations

        if (e.getSource() == b11) // +
        {
            num1 = Double.parseDouble(tf.getText());
            tf.setText("");
            operator = '+';

        }
        else if (e.getSource() == b12) // -
        {
            num1 = Double.parseDouble(tf.getText());
            tf.setText("");
            operator = '-';

        }
        else if (e.getSource() == b13) // *
        {
            num1 = Double.parseDouble(tf.getText());
            tf.setText("");
            operator = '*';

        }
        else if (e.getSource() == b14) // /
        {
            num1 = Double.parseDouble(tf.getText());
            tf.setText("");
            operator = '/';

        }
        else if (e.getSource() == b15)// %
        {
            num1 = Double.parseDouble(tf.getText());
            tf.setText("");
            operator = '%';

        }

        else if (e.getSource() == b16) // =
        {
            num2 = Double.parseDouble(tf.getText());

            if (operator == '+')
            {
                result = num1 + num2;
                tf.setText(String.valueOf(result));
            }
            else if (operator == '-')
            {
                result = num1 - num2;
                tf.setText(String.valueOf(result));
            }
            else if (operator == '*')
            {
                result = num1 * num2;
                tf.setText(String.valueOf(result));
            }

            if (operator == '/')
            {
                try
                {
                    if (num2 != 0)
                    {
                        result = num1 / num2;
                        tf.setText(String.valueOf(result));
                    }
                    else
                    {
                        tf.setText("Infinite");
                    }
                }
                catch (Exception i)
                {
                }
            }
            if (operator == '%')
            {
                result = num1 % num2;
                tf.setText(String.valueOf(result));
            }
        }
        else if (e.getSource() == b17) // C
        {
            tf.setText("");
        }
        else // Numbers
        {
            temp = tf.getText() + e.getActionCommand();
            tf.setText(temp);
        }
    }

    public static void main(String[] args)
    {
        new lab13();
    }
}

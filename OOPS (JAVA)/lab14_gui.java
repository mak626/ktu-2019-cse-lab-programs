
/*
Write a Java program that simulates a traffic light. The program lets the user select one of three lights: red, yellow, or green. 
When a radio button is selected, the light is turned on, and only one light can be on at a time. No light is on when the program starts
*/
import java.awt.*;
import java.awt.event.*;

public class lab14 extends Frame implements ItemListener
{

    Checkbox red, yellow, green;
    CheckboxGroup cbg;

    lab14()
    {

        cbg = new CheckboxGroup();
        red = new Checkbox("Red", cbg, false);
        yellow = new Checkbox("Yellow", cbg, false);
        green = new Checkbox("Green", cbg, false);

        red.addItemListener(this);
        yellow.addItemListener(this);
        green.addItemListener(this);

        add(red);
        add(yellow);
        add(green);

        repaint();

        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                dispose();
            }
        });

        setSize(300, 300);
        setVisible(true);
        setLayout(new FlowLayout());

    }

    @Override
    public void itemStateChanged(ItemEvent e)
    {
        repaint();
    }

    @Override
    public void paint(Graphics g)
    {

        g.drawOval(130, 80, 50, 50);
        g.drawOval(130, 140, 50, 50);
        g.drawOval(130, 200, 50, 50);

        if (cbg.getSelectedCheckbox() == red)
        {
            g.setColor(Color.red);
            g.fillOval(130, 80, 50, 50);
        }
        else if (cbg.getSelectedCheckbox() == yellow)
        {
            g.setColor(Color.yellow);
            g.fillOval(130, 140, 50, 50);
        }
        else if (cbg.getSelectedCheckbox() == green)
        {
            g.setColor(Color.green);
            g.fillOval(130, 200, 50, 50);
        }

    }

    public static void main(String[] args)
    {
        new lab14();
    }
}

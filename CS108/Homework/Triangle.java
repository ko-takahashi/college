//CS108 HW3 Kosuke Takahashi
//No Arraylist
public class Triangle
{
    //Instance variables, assume all are double
    public double a;
    public double b;
    private double c;

    private int numMade;
    
    //Instance method (accessor and mutator)
    //getC: accessor method for the c property
    //setC: mutator for the c property, sets the value of c
    //setC should do data validation (so no c = 0 or c < 0)
    
    public double getC()
    {
	return this.c;
    }

    public void setC(double d)
    {
	if(d <= 0)
	    {
		System.out.println("Input a positive number");
	    }
	else
	    {
		this.c = d;
	    }
    }

    //Instance method
    //isRightTriangle: returns true/false if it is a right triangle
    //hint: a*a + b*b == c*c

    public boolean isRightTriangle()
    {
	if(a*a + b*b == c*c)
	    {
		return true;
	    }
	else
	    {
		return false;
	    }
    }

    //Constructor methods
    //default constructor: sets a, b, and c to 3, 4, and 5
    //customizable constructor: no data validation needed

    public Triangle()
    {
	this.a = 3;
	this.b = 4;
	this.c = 5;
    }

    public Triangle(double A, double B, double C)
    {
	this.a = A;
	this.b = B;
	this.c = C;
    }

    //Class variables
    //numMade: starts at 0, but increases by 1 for every new triangle
    //the variable should be int and private

    //private int numMade = 0;

    //Class methods
    //getNumMade: accessor method, returns value of numMade
    
    public int getNumMade()
    {
	numMade++;
	return numMade;
    }
}
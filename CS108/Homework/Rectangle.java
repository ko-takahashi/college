public class Rectangle
{
    //public instance variables
    public double x;   //x coordinate of upper-left point
    public double y;   //y coordinate of upper-left point

    //private instance variables
    private double length; 
    private double width;

    //PI = 3.14
    public final double PI = 3.14;

    //Constructors
    //default Constructor
    public Rectangle()
    {
	x = 1;
	y = 1;
	length = 1;
	width = 1;
    }
    //customizing constructor
    public Rectangle(double a, double b, double c, double d)
    {
	x = a;
	y = b;

	if(c < 0)
	    {
		System.out.println("That's impossible");
		length = 1;
	    }
	else
	    {
		length = c;
	    }

	if(d < 0)
	    {
		System.out.println("That's impossible");
		width = 1;
	    }
	else
	    {
		width = d;
	    }
    }

    //Instance Methods
    //shiftHorizontally(inc): x increases by inc
    public void shiftHorizontally(double inc)
    {
	x = x + inc;
    }
    //shiftVertically(inc): y increases by inc
    public void shiftVertically(double inc)
    {
	y = y + inc;
    }
    //talk(): outputs the phrase "Hi, I'm a Rectangle"
    public void talk()
    {
	System.out.println("Hi, I'm a Reactangle");
    }

    //Accesor Methods
    //getLength()
    public double getLength()
    {
	return this.length;
    }
    //getWidth()
    public double getWidth()
    {
	return this.width;
    }

    //Mutator Methods
    //setLength(L): ignore a negative L
    public void setLength(double L)
    {
	if(L < 0)
	    {
		System.out.println("That's negative buddy");
	    }
	else
	    {
		this.length = L;
	    }
    }
    //setWidth(W): ignore a negative W
    public void setWidth(double W)
    {
	if(W < 0)
	    {
		System.out.println("That's negative buddy");
	    }
	else
	    {
		this.width = W;
	    }
    }

    //getArea(): returns area, but no area property
    public double getArea()
    {
	double theArea = this.length * this.width;
	return theArea;
    }

    //Class Methods
    //calcArea(double len, double wdt): computes and returns area
    public double calcArea(double len, double wdt)
    {
	double area = len * wdt;
	return area;
    }
}
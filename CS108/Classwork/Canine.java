public class Canine
{
    public String name;
    public String color;
    private int numlegs;

    public static double population = 6.5e10;
    
    public Canine()
    {
	this.name = "Stray Dog";
	this.color = "Gray";
	this.numlegs = 4;
    }

    public Canine(String a, String b, int c)
    {
	this.name = a;
	this.color = b;
	this.numlegs = c;

	if(c < 0)
	    {
		System.out.println("You lost the right to give a numlegs");
		this.numlegs = 4;
	    }
	else
	    {
		this.numlegs = c;
	    }
    }

    public void speak()
    {
	System.out.println("Bark");
    }
    
    public void multispeak(int n)
    {
	for(int i = 1; i <= n; i++)
	    {
		this.speak();
	    }
    }

    public static void changePopulation(double p)
    {
	if (p >= 0)
	    {
		Canine.population = p;
	    }
    }

    //accessor method: aka 'get' method
    //instance method
    public int getNumlegs()
    {
	return this.numlegs;
    }

    //mutator method: aka 'set' method
    //instance method
    public void setNumlegs(int n)
    {
	if (n < 0)
	    {
		System.out.println("Ignoring numlegs");
	    }
	else
	    {
		this.numlegs = n;
	    }
    }
}   //class

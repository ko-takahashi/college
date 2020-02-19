public class Feline
{

    public String name;
    public String color;
    public int numlegs;
    public static double population = 6.5e10;
    
    public Feline()
    {
	this.name = "Stray Cat";
	this.color = "Gray";
	this.numlegs = 4;
    }

    public Feline(String a, String b, int c)
    {
	this.name = a;
	this.color = b;
	this.numlegs = c;
    }

    public Feline(String a)
    {
	this.name = a;
	this.color = "Gray";
	this.numlegs = 4;
    }

    public void speak()
    {
	System.out.println("Meow");
    }

    public void multispeak(int n)
    {
	for(int i = 1; i <= n; i++)
	    {
		System.out.println("Meow");   //or this.speak(); or speak();
	    }
    }

    public static void changePopulation(double p)
    {
	if(p >=  0)
	    {
		Feline.population = p;
	    }
    }
}
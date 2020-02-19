public class Wolf extends Canine
{
    //name, color, numlegs: copied for free
    //population: copied for free

    public boolean isItAWerewolf;

    public Wolf()
    {
	super("Stray Wolf", "Gray", 4);
	//this.name = "Stray Wolf";
	//this.color = "Gray";
	//this.setNumlegs(4);
	this.isItAWerewolf = false;
    }

    public Wolf(String a, String b, int c, boolean d)
    {
	super(a, b, c);
	//this.name = a;
	//this.color = b;
	//this.setNumlegs(c);
	this.isItAWerewolf = d;
    }
    
    public void speak()
    {
	System.out.println("Howl!");
    }

    public void bipedal()
    {
	this.isItAWerewolf = true;
	this.setNumlegs(2);
    }
}   //class
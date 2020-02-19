public class DroidProg1 implements GameCharacter
{
    public int x;
    public int y;

    public DroidProg1(int t1, int t2)
    {
	this.x = t1;
	this.y = t2;
    }

    public void drawOnScreen()
    {
	System.out.println("Drawing a droid at coordinates: " + this.x+ "," + this.y);
    }

    public void makeSound()
    {
	System.out.println("Beep Boop!");
    }
}
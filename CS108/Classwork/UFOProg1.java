public class UFOProg1 implements GameCharacter
{
    public int x;
    public int y;

    public UFOProg1(int t1, int t2)
    {   
	this.x = t1;
	this.y = t2;
    }

    public void drawOnScreen()
    {
	System.out.print("Drawing a UFO  at coordinates: " + this.x+ ", "); 
			 System.out.println(this.y);
    }

    public void makeSound()
    {
        System.out.println("Breeeeeee!");
    }
}
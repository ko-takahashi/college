public class StarCruiserProg1  implements GameCharacter
{
    public int x;
    public int y;

    public StarCruiserProg1(int t1, int t2)
    {   
	this.x = t1;
	this.y = t2;
    }

    public voiddrawOnScreen()
    {
	System.out.println("Drawing a Star Cruiser  at coordinates: " + this.x+ "," + t\
			   his.y);
    }

    public void makeSound()
    {
        System.out.println("Whoooosh");
    }
}
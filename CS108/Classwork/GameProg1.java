public class GameProg1
{
    public static void main(String args[])
    {
	//declare generally
	GameCharacter[] enemies = new GameCharacter[5];

	//initialize specifically
	//Object(x,y) -> the coordinates
	enemies[0] = new DroidProg1(10,20);
	enemies[1] = new DroidProg1(100,120);
	enemies[2] = new UFOProg1(60,50);
	enemies[3] = new StarCruiserProg1(10,100);
	enemies[4] = new DroidProg1(100,20);

	for(int i = 0; i <= 4; i++)
	    {
		enemies[i].drawOnScreen();
		enemies[i].makeSound();
	    }
    }
}
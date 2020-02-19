//tictactoe
import java.util.*;
public class ttt
{
    public static void main(String [] args)
    {
	Scanner scan = new Scanner(System.in);
	System.out.println("Do you want to be X or O?");
	String s = scan.nextLine();
	s = s.trim();
	s = s.toUpperCase();

	String playerchar, pcchar;
	if(s.equals("X"))
        {
	    playerchar = "X";
	    pcchar = "O";
        }
	else
        {
	    playerchar = "O";
	    pcchar = "X";
	}

	System.out.println("Do you want to be PLayer 1 or Player 2");
	int currplayer = scan.nextInt();
	if(currplayer != 1 && currplayer != 2)
	    currplayer = 2;

	int[]gb = new int[9];

	while(true)
        {
	    if(currplayer == 1)
		{
		    showgameboard(gb, playerchar, pcchar);
		    System.out.println("Pick a square, 1-9:");
		    
		    int t;
		    do
			{
			    t = scan.nextInt();
			}
		    while(t<1 || t>9 || gb[t-1] != 0);

			gb[t-1] = 1;
		    
		    if(isitawin(gb,1))
			{
			    System.out.println("You win");
			    showgameboard(gb, playerchar, pcchar);
			    return;
			}
		    if(allsqrsfilled(gb))
			{
			    System.out.println("Tie game");
			    showgameboard(gb, playerchar, pcchar);
			    return;
			}
		    
		    currplayer = 2;
		}
	    
	    if(currplayer == 2)
		{
		    int t;
		    do
			{
			    t = (int)(Math.random()*9);
			}
		    while(gb[t-1] != 0);

		    gb[t-1] = 2;

		    if(isitawin(gb, 2))
			{
			    System.out.println("Computer wins");
			    showgameboard(gb, playerchar, pcchar);
			    return;
			}
		    
		    if(allsqrsfilled(gb))
			{
			    System.out.println("Tie game");
			    showgameboard(gb, playerchar, pcchar);
			    return;
			}

		    currplayer = 1;
		}
        }
    }

    public static void showgameboard(int[] gb, String playerchar, String pcchar)
    {
	String[] sgb = new String[9];
	for(int i = 0; i <=8; i++)
	    {
		if (gb[i] == 1)
		    {
			sgb[i] = playerchar;
		    }
		else if (gb[i] == 2)
		    {
			sgb[i] = pcchar;
		    }
		else
		    {
			sgb[i] = "E";
		    }
		
		System.out.println(" " + sgb[0] + " | " + sgb[1] + " | " + sgb[2]);
		System.out.println(" " + sgb[3] + " | " + sgb[4] + " | " + sgb[5]);
		System.out.println(" " + sgb[6] + " | " + sgb[7] + " | " + sgb[8]);
	    }
    }

    public static boolean isitawin(int[] gb, int p)
    {
	if(gb[0] == p && gb[1] == p && gb[2] == p)
	    return true;    
        if(gb[3] == p && gb[4] == p && gb[5] == p)
	    return true;
        if(gb[6] == p && gb[7] == p && gb[8] == p)
      	    return true;
        if(gb[0] == p && gb[4] == p && gb[8] == p)
	    return true;
	if(gb[2] == p && gb[4] == p && gb[6] == p)
      	    return true;
	if(gb[0] == p && gb[3] == p && gb[6] == p)     
	    return true;
        if(gb[4] == p && gb[1] == p && gb[7] == p)
	    return true;
	if(gb[8] == p && gb[5] == p && gb[2] == p)     
	    return true;
	return false;
    }

    public static boolean allsqrsfilled(int[] gb)
    {
	for(int i = 0; i <= 8; i++)
	    {
		if(gb[i] == 0)
		    return false; 
	    }
	return true;
    }
}

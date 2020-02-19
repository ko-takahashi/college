//Kosuke Takahashi
//CS-108
//Section #: 1
//Bajic

import java.util.*;
public class Homework1
{
    public static void main (String[] args)
    {
	Scanner scan = new Scanner(System.in);
	ArrayList list = new ArrayList();

	//ask user to type stuff until they type stop
	String w = "";
	String stop = "STOP";
	while(!w.equals(stop))
        {
	    System.out.println("Input word here [type STOP to stop]: ");
	    w  = scan.nextLine();
	    w = w.trim();
	    w = w.toUpperCase();
	    list.add(w);
        }
	
	//output the ArrayList using the .toString() method
	System.out.println(list.toString());

	//output the ArrayList using a FOR loop
	int n = list.size();
	for(int i = 0; i < n; i++)
        {
	    System.out.println(list.toString());
        }
    } //main
} //class
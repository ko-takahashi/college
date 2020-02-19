import java.util.*;
public class nonGenAL
{
    public static void main(String args[])
    {
	ArrayList<String> list1 = new ArrayList<String>();
	
	//if you don't use generics, you secretly get:
	//ArrayList<Object>

	list1.add("Hi");
	list1.add("Hello");
	list1.add("Welcome");

	String s = list1.get(2);  //no casting needed
	System.out.println(s);

	s = list1.remove(2);  //no casting needed
	System.out.println(s);
    }
}
import java.util.*;
public class sorting1
{
    public static void main (String[] args)
    {
	int[] a = {10, 1, 100, 1, 9, 99};

	System.out.println(a);   //prints gibberish
	System.out.println(Arrays.toString(a));   //prints correctly

	Arrays.sort(a);   //sorts smallest to largest
	System.out.println(Arrays.toString(a));
    }
}
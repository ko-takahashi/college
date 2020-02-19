import java.util.*;
public class bubblesort
{
    public static void main(String args[])
    {
	int[] a = {10, 1, 100, 1, 9, 99};
	int N = a.length;

	for(int p = 1; p <= N-1; p++)
	    {
		for(int L = 0; L <= N-2; L++)
		    {
			if(a[L] > a[L+1])
			    {
				//swap them
				int t = a[L];
				a[L] = a[L+1];
				a[L+1] = t;
			    }
		    }
	    }
	System.out.println(Arrays.toString(a));
    }
}
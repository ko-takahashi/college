public class RecursionFact
{
    public static void main(String[] args)
    {
	System.out.println(fact(5));
	System.out.println(fact(0));
	System.out.println(fact(1));
	System.out.println(fact(10));
	System.out.println(fact(11));
    }

//not using recursion
//standard factorial function from CS 107
public static long fact(int n)
{
    long prod = 1;
    for(int i = 2; i <= n; i++)
	{
	    prod = prod * i;
	}
    return prod;
}
}
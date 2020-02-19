public class RecursionFact2
{
    public static void main(String[] args)
    {
        System.out.println(fact(5));
        System.out.println(fact(0));
        System.out.println(fact(1));
        System.out.println(fact(10));
        System.out.println(fact(11));
    }

    //with recursion
    //for ease, assume n is always >= 0
    public static long fact(int n)
    {
	if(n == 0)
	    {
		return 1;
	    }
	//reduction step
	return n * fact(n-1);
    }
}
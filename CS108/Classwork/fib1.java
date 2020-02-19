public class fib1
{
    public static void main(String args[])
    {
	System.out.println(fib(1));
	System.out.println(fib(2));
	System.out.println(fib(5));
	System.out.println(fib(6));
	System.out.println(fib(10));

	System.out.println(fib(100));
	//get AOF here bec the answer is too large to fit into a long
    }
    //we'll run this code anyways to show the SPEED of the calculation
    
    public static long fib(int t)
    {
	if(t==1 || t==2)
	    {
		return 1;
	    }
	long L = 1;
        long R = 1;
	for(int i = 3; i<t; i++)
	    {
		long next = L+R;
		L = R;
		R = next;
	    }
	return R;
    }
}
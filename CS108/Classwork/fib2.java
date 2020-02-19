public class fib2
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
    
    //recursion
    public static long fib(int t)
    {
	if(t == 1 || t == 2)   //base case
	    {
		return 1;
	    }
	return fib(t-1) + fib(t-2);   //reduction
    }
}
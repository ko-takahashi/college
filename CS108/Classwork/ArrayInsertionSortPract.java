import java.util.*;
public class ArrayInsertionSortPract
{
    //this is going to be the rough draft of the code
    public static void main(String args[])
    {
	int[] arr = {5,16,16,20,30,0,0,0,0,0};
	int N=5;

	inssort(arr,N,19);
	N++;
	inssort(arr,N,100);
        N++;
	inssort(arr,N,1);
        N++;
	inssort(arr,N,1);
        N++;
	inssort(arr,N,19);
        N++;
	
	System.out.println(Array.toString(arr));
	//1,1,5,16,16,19,19,20,30,100
    }   //main
    
    //exam prep
    pulbic static void inssort(int[] a, int N, int x)
    {
	//if data item x can't fit:
	if(N==a.length)
	    {
		System.out.println("Array is full");
		return;
	    }

	//if data item x is the first:
	if(N==0)
	    {
		a[0] = x; 
		return;
	    }
	
	//if data item x should be put back of array's data:
	if(x >= a[N-1])
	    {
		a[N] = x;
		return;
	    }

	//roll across array's data, looking for a larger item
	//when you hit it, shift all data rightward
	//starting at that location
	//then put x into that location
	int idx = 0;
	while(a[idx] <= x)
	    {
		idx++;
	    }
	
	for(int i = N-1; i>=idx; i--)
	    {
		a[i+1] = a[i];
	    }
	
	a[idx] = x;
    }
}
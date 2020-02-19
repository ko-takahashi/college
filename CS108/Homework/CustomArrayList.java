import java.util.*;
public class CustomArrayList<T>
{
    //instance variables
    //private array arr, size 100, stores generics type T
    private T[] arr;
    private int numitems;   // stores the number of data items in the list

    //default constructor
    public CustomArrayList()
    {
	numitems = 0;
	arr = (T[]) new Object[100];
    }

    //instance methods
    public boolean add(T element)
    {
        //adds data item 'element' to the back of the array
        //if the array is full, shout output "Array full, ignoring"
        //if the add is successful, output true, if it is full, output false
	if(arr.length == numitems)
	{
	    System.out.println("Array full, ignoring.");
	    return false;
        }
	else
        {
	    arr[numitems] = element;
	    numitems++;
	    return true;
        }	
    } 

    public void add(int index, T element)   //FIX
    {
        //insert data items to the position index
        //If it is full, add routine should output "Array full, ignoring"
        //super complex, read Specs
	if(index == arr.length)
	{
	    System.out.println("Array full, ignoring.");
	    return;
	}
	if(index < 0 || index > arr.length+1)
	{
	    System.out.println("Illegal index, ignoring.");
	}

	for(int loc = 0; loc < arr.length; loc++)
	{
	    //code
	}
        for(int i =  arr.length; i >= index; i--)
	{
	    arr[i+1] = arr[i];
        }
	arr[index] = element;
    }

    public T get(int index)
    {	
        //returns data item at position index
        //if out of range, output "illegal index"
	if(index > arr.length)
	    System.out.println("Illegal index.");
	return arr[index];
    } 
  
    public T set(int index, T element)   //FIX
    {
        //sets the data item at position index to element
           //and returns data item that was there before
        //if out of range, output "illegal index"
	T a = arr[index];
	if(index > arr.length || index < arr.length)
	    System.out.println("Illegal index.");
	return a;
    }
    
    public T remove(int index)   //FIX
    {   
        //out of range, output "illegal index"
	//slightly similar to the insertion sort code
	if(index > arr.length  || index < arr.length)
	    System.out.println("Illegal index.");
	else
	    arr[index] = null;
	return arr[index];
    }
    
    public int size()
    {
       //outputs the size of the Arraylist
	return arr.length;
    } 
    
   public boolean isEmpty()
   {
       //outputs if Arraylist is empty or not
       for(int i = 0; i <= arr.length; i++)
       {
	   if(arr[i] != null)
	       return false;
       }
       return true;
   } 
   
   public String toString()
   {
       String str = "";
       for(int i = 0; i < arr.length; i++)
	   str = str + arr[i] + ", ";
       return "[" + str + "]";
   }
}
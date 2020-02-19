public class CustomArrayListTest
{
    public static void main(String[] args)
    {
	//This tester is really similar to the testers for ArrayList
	//CustomArrayList is like coding ArrayList from scratch
	
	CustomArrayList<String> list1 = new CustomArrayList<String>();
	list1.add("Hi");
	list1.add("Hello");
	list1.add("Welcome");
	
	String s = list1.get(2);   //generics, so no casting needed
	System.out.println(s);   //should output Welcome
	
	s = list1.remove(2);   //generics, so no casting needed
	System.out.println(s);   //Welcome

	list1.add(2, "Welcome");   //insert, but at back of data items

	System.out.println(list1);   //same as printing list1.toString()

	list1.set(2, "Welcome!!!");   //using subroutine call instead of function call

	System.out.println(list1.size());   //3
	System.out.println(list1.isEmpty());   //false
	System.out.println(list1.toString());   //[Hi, Hello, Welcome!!!]

	for(int i = 0; i < list1.size(); i++)
        {
	    System.out.println(list1.get(i));
	}

	s = list1.remove(1);
	System.out.println(s);   //Hello

	list1.add(1, "Hello!!");   //insert

	System.out.println(list1);   //[Hi, Hello!!!, Welcome!!!]
    }
}
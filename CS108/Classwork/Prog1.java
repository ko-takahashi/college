public class Prog1
{
    public static void main(String[] args)
    {
	Feline cat1 = new Feline();
	Feline cat2 = new Feline();
	Feline cat3 = new Feline("Garfield", "Orange", 4);
	Feline cat20 = new Feline("Felix");

	System.out.println(cat1.name);
	System.out.println(cat1.color);
	System.out.println(cat1.numlegs);

	cat1.name = "Mittens";
	cat1.color = "Green";

	cat1.speak();
	cat1.multispeak(10);

	System.out.println(Feline.population);
	Feline.population = 7.0e10;

	Feline.changePopulation(8.0e10);
	System.out.println(Feline.population);
    }
}

//public class Feling<T>
//{
//public T name;
//public String color;
//public in numlegs;
//public class Feline()
//{
//this.name = null;
//this.color = "Gray";
//this.numlegs = 4;
//}
//public Feline(String a, String b, int c)
//{
//this.name = a;
//this.color = b;
//this.numlegs = c:
//}
//etc.
//}
//}
//idk where the fuck this code is supposed to go tbh
//i also don't know wtf is going on

import java.util.*;

public class homework1 {
    public static void main (String args[]) {
        System.out.print("Number: ");
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int N = 1;

        /* Question 1
        while(n > 0) {
            System.out.println( N + ". Do it");
            N = N + 1;
            n = n - 2;
        */

        /* Question 2
        for( int row = 0; row < n; row++) {
            for( int col = 0; col < n; col++) {
                System.out.println( N + ". Hi there");
                N++;
            }
        }
        */

        /* Question 3
        while(n > 0) {
            System.out.println(N + ". Party Cannon");
            N++;
            n = n >> 1;
        }
        */

        Character sidekick = new Archer();
        Character shopkeep = new Character();
        ArchMage headOfSchool;
        headOfSchool = new ArchMage();
        Warrior trainer = new Warrior();

        /* Question 5a
        System.out.println(sidekick.getType());

        // Question 5b
        sidekick = trainer;
        System.out.println( sidekick );

        // Question 5c
        System.out.println( headOfSchool.castSpell() );

        // Question 5d
        String toOut;
        toOut = String.format("[%s]\n[%s]\n[%s]\n", shopkeep, headOfSchool, trainer);
        System.out.println( toOut );
        */
    }
}
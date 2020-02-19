//import java.util.*;

import javax.swing.JOptionPane;

public class homework2 {
    public static void main(String[] args){
        /*
        int[] dataToSort = [1, 4, 1, 5, 9, 2, 6, 5, 3, 5];
        void sort(int toSort[]) {
            int n = toSort.length;

            for(int curIndex = 0; curIndex < n-1; curIndex++) {
                int minIndex = curIndex;
                for (int checkIndex = curIndex + !; checkIndex < n; checkIndex++) {
                    if (toSort[checkIndex] < toSort[minIndex])
                        minIndex = checkIndex;
                    }

                int temp = toSort[minIndex];
                toSort[minIndex] = toSort[curIndex];
                toSort[curIndex] = temp;

                //TEST POINT
                System.out.println(toSort);
                System.out.println("Test");
                }
            }
        }
        */

        /*
        List<Integer> targetList = new ArrayList<Integer>();
        List<String> other = new ArrayList<String>();
        List<Integer> scores = new LinkedList<Integer>();

        LinkedList<String> names = new LinkedList<String>();
        ArrayList<Integer> exile;

        exile = scores;
        exile = new List<Integer>();
        targetList = other;
        targetList = scores;
        other = new List<Integer>();
        scores = exile;
        scores = new ArrayList<Integer>();
        exile = targetList;
        */

        /*
        String str = JOptionPane.showInputDialog("Please enter a String:");
        int n = str.indexOf("srhs");
        String srhs = str.substring(n, n+4).toUpperCase();
        String before = str.substring(0,n);
        String after = str.substring(n+4);
        System.out.println(str);
        System.out.println(before + srhs + after);
        */

        /*
        String str = JOptionPane.showInputDialog("Please enter your full name:");

        String initial = str.substring(0,1);
        int space = str.indexOf(" ");

        String initial2 = str.substring(space+1,space+2);
        int space2 = str.indexOf(" ");

        String rest = str.substring(space2+1,str.length());
        int space3 = rest.indexOf(" ");
        String initial3 = rest.substring(space3+1,space3+2);

        System.out.println(initial + "." + initial2 + "." + initial3 + ".");
        */
    }
}

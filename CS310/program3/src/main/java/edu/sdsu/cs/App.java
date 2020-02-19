/*
Program #3

Tyler Nguyen
cssc0790

Kosuke Takahashi
cssc0758
*/

package edu.sdsu.cs;

import edu.sdsu.cs.datastructures.DirectedGraph;
import edu.sdsu.cs.datastructures.IGraph;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class App 
{
    private static IGraph<String> graph;
    private static List<String> neighbors;
    private static Map<String, String> vertex;
    private static BufferedReader buffer;

    public static void main(String[] args) {
        graph = new DirectedGraph<>();      //Number 2
        neighbors = new LinkedList<>();
        vertex = new TreeMap<>();
        FileReader file;
        //BufferedReader buffer;

        if(args.length == 0) {
            file = fileTest("layout.csv");
            buffer = new BufferedReader(file);
            try {
                mapGenerator(file);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else if(args.length == 1) {
            file = fileTest(args[0]);
            buffer = new BufferedReader(file);
            try {
                mapGenerator(file);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else {
            System.out.println("-- NO FILE FOUND --");
            return;
        }
    }

    /**
     * Verifies that the file is valid
     * File Test
     * Number 1
     */
    public static FileReader fileTest(String file) {
        try {
            return new FileReader(file);
        }
            catch (IOException e) {
                System.out.println("-- INVALID FILE --\n" + file);
                System.exit(-1);
        }
        return null;
    }

    /**
     * Declares + Instantiates a DirectedGraph object of type IGraph
     * Number 2
     */

    /**
     * Reads the input file and builds a graph
     * Number 3
     */
    public static void mapGenerator(FileReader file) throws IOException {
        System.out.println("-- VALID FILE --\n" + file);
        System.out.println("-- GENERATING MAP --");

        while(buffer.readLine() != null) {
            String[] vertex = buffer.readLine().split("\n");
            if(vertex.length < 1)
                break;
            graph.add(vertex[0]);
            for(int i = 1; i < vertex.length; i++) {
                if(!graph.contains(vertex[i]))
                    graph.add(vertex[i]);
                else
                    graph.connect(vertex[i-1],vertex[i]);
            }
//            String cell = buffer.readLine();
//            String prevCell = null;
//            if(!graph.contains(prevCell)) {
//                graph.add(prevCell);
//            }
//            else
//                graph.connect(prevCell, cell);
        }
    }

    /**
     * Displays information about the Graph using toString()
     * i.e. vertices, connections, degree of each vertex
     * Number 4
     */
//    public String toString() {
//        String vert, con = "", deg = "";
//        vert = String.valueOf(graph.vertices());
//
//        return "Vertices: " + vert + "\n" +
//                "Connections: " + con + "\n" +
//                "Degree of each vertex: " + deg ;
//    }

    /**
     * User selects starting and ending vertices
     * Shortest path Test
     * Number 5
     */
    public void shortestPathTest(String start, String end) {
        List<String> shortestPath = new LinkedList<>();
        String visited = "";

        //shortestPath = graph.shortestPath(start, end);
        int distance = shortestPath.size();
        for(String vert : shortestPath) {
            visited += vert + " ";
        }
        System.out.println("Vertices visited: " + visited);
        System.out.println("Total distance: " + distance);
    }

    /**
     * Terminates with grace
     * Number 5
     */
}
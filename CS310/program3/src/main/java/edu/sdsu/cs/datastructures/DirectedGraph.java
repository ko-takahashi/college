/*
Program #3

Tyler Nguyen
cssc0790

Kosuke Takahashi
cssc0758
*/

package edu.sdsu.cs.datastructures;

import java.util.*;

public class DirectedGraph<V> implements IGraph<V> {

    private LinkedList<V> neighbors;
    private Map<V, LinkedList<V>> graph = new TreeMap<>();

    @Override
    public void add(V vertexName) {
        if (graph.containsKey(vertexName))
            return;
        graph.put(vertexName, new LinkedList<V>());
    }

    @Override
    public void connect(V start, V destination) {
        if (!contains(start) || !contains(destination))
            throw new NoSuchElementException("-- NO ELEMENTS --");
        graph.get(start).add(destination);
        //graph.get(V) gets the appropriate LinkedList
    }

    @Override
    public void clear() {
        graph.clear();
    }

    @Override
    public boolean contains(V label) {
        return graph.containsKey(label);
    }

    @Override
    public void disconnect(V start, V destination) {
        if (!contains(start) || !contains(destination))
            throw new NoSuchElementException("-- NO ELEMENTS --");
        graph.get(start).remove(destination);
    }

    @Override
    public boolean isConnected(V start, V destination) {
        if (!contains(start) || !contains(destination))
            throw new NoSuchElementException("-- NO ELEMENTS --");

        if (graph.get(start).contains(destination))
            return true;
        LinkedList<V> visited = new LinkedList<>();
        LinkedList<V> queue = new LinkedList<>();

        visited.add(start);
        queue.add(start);
        while (!queue.isEmpty()) {
            V curr = queue.remove();
            if (curr.equals(destination))
                return true;
            for (V neighbor : neighbors(curr)) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
        return false;
    }

    @Override
    public Iterable<V> neighbors(V vertexName) {
        if (!contains(vertexName))
            throw new NoSuchElementException("-- NO ELEMENTS --");
        return graph.get(vertexName);
    }

    @Override
    public void remove(V vertexName) {
        if (!contains(vertexName))
            throw new NoSuchElementException("-- NO ELEMENTS --");
        for (V vertex : vertices()) {
            if (isConnected(vertexName, vertex))
                disconnect(vertexName, vertex);
            if (isConnected(vertex, vertexName))
                disconnect(vertex, vertexName);
        }
        graph.remove(vertexName);

//        Map<V, LinkedList<V>> temp = graph;
//        for(Map.Entry<V, LinkedList<V>> entry : temp.entrySet()) {
//            if (temp.get(entry).equals(vertexName))
//                temp.get(entry).remove(vertexName);
//        }
    }

    @Override
    public List<V> shortestPath(V start, V destination) {
        if (!contains(start) || !contains(destination))
            throw new NoSuchElementException("-- NO ELEMENTS --");

        LinkedList<V> path = new LinkedList<>();
        Set<V> visited = new HashSet<>();
        LinkedList<V> queue = new LinkedList<>();
        Map<V, V> nextV = new TreeMap<>();

        visited.add(start);
        queue.add(start);
        V curr = start;
        visited.add(curr);
        while (!queue.isEmpty()) {
            curr = queue.remove();
            if (curr.equals(destination))
                break;
            for (V next : neighbors(curr)) {
                if (!visited.contains(next)) {
                    visited.add(next);
                    queue.add(next);

                    nextV.put(curr, next);
                }
            }
        }
        if (!curr.equals(destination))
            throw new RuntimeException("-- NO PATH --");

        for (V next = start; next != null; next = nextV.get(next))
            path.add(next);
        return path;
    }

    @Override
    public int size() {
        return graph.size();
    }

    @Override
    public Iterable<V> vertices() {
        return graph.keySet();
    }

    @Override
    public IGraph<V> connectedGraph(V origin) {
        if (!contains(origin))
            throw new NoSuchElementException("-- NO ELEMENTS --");
        DirectedGraph<V> originGraph = new DirectedGraph<>();
        originGraph.add(origin);
        for (V vert : vertices()) {
            if (isConnected(origin, vert)) {
                originGraph.add(vert);
                originGraph.connect(origin, vert);
            }
        }
        return originGraph;
    }

    /**
     * Displays information about the Graph using toString()
     * i.e. vertices, connections, degree of each vertex
     * Number 4
     */
    @Override
    public String toString() {
        String vert, conn = "", deg = "";
        String all;

        vert = String.valueOf(vertices());
        for(V v : vertices()) {
            conn += String.valueOf(neighbors(v));
            deg = "1";
        }
        all = "Vertices: " + vert + "\n" +
                "Connections: " + conn + "\n" +
                "Degree: " + deg + "\n";
        return all;
    }
}
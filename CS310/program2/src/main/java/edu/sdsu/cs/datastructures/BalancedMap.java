package edu.sdsu.cs.datastructures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.TreeMap;
import java.util.ConcurrentModificationException;

public class BalancedMap<K extends Comparable<K>, V> implements IMap {
    private int currSize;
    private TreeMap<Comparable, Object> map;
    private int iterIndex;
    private long modCounter;

    public BalancedMap(TreeMap<Comparable, Object> source) {
        this.map = source;
        currSize = map.size();
        modCounter = 0;
    }

    public BalancedMap() {
        this.map = new TreeMap<Comparable, Object>();
        currSize = 0;
        modCounter = 0;
    }

    @Override
    public boolean contains(Comparable key) {
    //.equals() checks the address
        return map.containsKey(key);
    }

    @Override
    public boolean add(Comparable key, Object value) {
        if(map.containsKey(key))
            return false;
        else {
            map.put(key, value);
            currSize++;
            modCounter++;
            return true;
        }
    }

    @Override
    public Object delete(Comparable key) {
        if(this.currSize == 0)
            return null;
        else {
            modCounter++;
            currSize--;
            return map.remove(key);
        }
    }

    @Override
    public Object getValue(Comparable key) {
        return map.get(key);
    }

    @Override
    public Comparable getKey(Object value) {
        return (Comparable) map.keySet().toArray()[0];
    }

    @Override
    public Iterable getKeys(Object value) {
        return map.getKeys(value);
    }

    @Override
    public int size() {
        /*
        int size = 0;
        for(Map.Entry<K,V> entry: map.entrySet()) {
            size++;
        }
        */
        return map.size();
    }

    @Override
    public boolean isEmpty() {
        return map.size() == 0;
    }

    @Override
    public void clear() {
        //this.map = new TreeMap<K,V>();
        map.clear();
    }

    @Override
    public Iterable keyset() {
        return map.keySet();
        /*
        Iterator<K> iteratorK = (Iterator<K>)map;

        return (Iterable)iteratorK;
        */
    }

    @Override
    public Iterable values() {
        return map.values();
        /*
        for(Comparable<V> v: map)
        return null;
        */
    }

    // Iterator help that is not part of IMap.java
    class IteratorHelper implements Iterator<E> {
        int iterIndex;
        E[] localArray
        long modificationCounter;

        public IteratorHelper() {
            iterIndex = 0;
            localArray = (E[]) new Object[currSize];
            modificationCounter = modCounter;

            for(int i = 0; i < currSize; i++)
                localArray[i] = map[i];
            localArray = sort(localArray);
        }

        public boolean hasNext() {
            if(modificationCounter != modCounter)
                throw new ConcurrentModificationException();
            return iterIndex < currSize;
        }

        public E next() {
            if(!hasNext())
                throw new NoSuchElementException();
            return localArray[iterIndex++];
        }

        public void remove() {
            throw new UnsupportedOperationException();

        private void sort(E[] obj) {
            // insert some sort code
            }
        }
    }
}

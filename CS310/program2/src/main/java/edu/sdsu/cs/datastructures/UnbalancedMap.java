package edu.sdsu.cs.datastructures;
import java.util.LinkedList;
import java.util.List;

public class UnbalancedMap<K extends Comparable<K>, V> implements IMap {
    private int currSize;
    private Node<K,V> root;

    private class Node<K, V> {
        private K key;
        private V value;
        private Node<K,V> leftchild;
        private Node<K,V> rightchild;

        private Node(K k, V v) {
            key = k;
            value = v;
            leftchild = rightchild = null;
        }
    }

    public UnbalancedMap(IMap<K,V> source) {
        for(K keys: source.keyset()) {
            V value = source.getValue(keys);
            add(keys,value);
        }
    }

    public UnbalancedMap() {
        clear();
    }

    @Override
    public boolean contains(Comparable key) {
        return false;
    }

    @Override
    public boolean add(K key, V value) {
        Node<K,V> current = root;
        Node<K,V> newNode = new Node<K,V>(key,value);
        if(root == null) {
            root = newNode;
        }
        else {
            if (key.compareTo(current.key) < 0) {
                current = current.leftchild;
                if (current.leftchild != null) {
                    //current.leftchild.add(key, value);

                } else {
                    current.leftchild = new Node<K, V>(key, value);
                }
            } else if (key.compareTo(current.key) > 0) {
                if (current.rightchild != null) {
                    //current.rightchild.add(key, value);
                } else {
                    current.rightchild = new Node<K, V>(key, value);
                }
            } else {
                this.value = value;
            }
            return false;
        }
        return false;
    }

    private Node delete(Node<K,V> node, K key) {
        //root = node;
        if(node == null)
            //return null;
            return node;
        if(key.compareTo(node.key) < 0)
            node.leftchild = delete(node.leftchild, key);
        else if(key.compareTo(node.key) > 0)
            node.rightchild = delete(node.rightchild, key);
        else {
            if(node.leftchild == null && node.rightchild == null) {
                currSize--;
                return null;
            }
            else if(node.leftchild == null) {
                currSize--;
                return node.rightchild;
            }
            else if(node.rightchild == null) {
                currSize--;
                return node.leftchild;
            }
            K minKey = null;
            while(node.leftchild != null) {
                minKey = node.leftchild.key;
                node = node.leftchild;
            }
            node.key = minKey;
            node.rightchild = delete(node.rightchild, minKey);
            node.value = getValue(key);
        }
        return node;
        //return root.value;
    }

    @Override
    public V delete(K key) {
        Node<K,V> deleter = root;
        deleter = delete(deleter, key);
        return deleter.value;
    }

    @Override
    public V getValue(K key) {
        Node<K, V> current = root;
        if (current.key.compareTo(key)) {
            return current.value;
        }

        if (key.compareTo(current.key) < 0) {
            return current.leftchild == null ? null : current.leftchild.getValue(key);
        } else {
            return rightchild == null ? null : rightchild.get(key);
        }
        return root.value;
    }

    @Override
    public Comparable getKey(Object value) {
        return null;
    }

    private V keys(Node<K,V> node, V value) {
        root = node;
        //List<V> keys = new LinkedList<V>;
        if(value.equals(node.value))
            return node.value;
        else
            return null;
    }

    @Override
    public Iterable getKeys(Object value) {

    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return root == null;
    }

    @Override
    public void clear() {
        root = null;
        currSize = 0;
    }

    private Iterable<K> getkeyset(List<K> toReturn, Node<K,V> curr) {
        if(curr == null)
            return toReturn;
        getkeyset(toReturn,curr.leftchild);
        toReturn.add(curr.key);
        getkeyset(toReturn,curr.rightchild);
        return toReturn;
    }

    @Override
    public Iterable keyset() {
        List<K> LLkeys = new LinkedList<K>();
        return getkeyset(LLkeys,root);
    }

    @Override
    public Iterable values() {
        return null;
    }

    // Iterator help that is not part of IMAP
    class IteratorHelper implements Iterator<E> {
        int iterIndex;
        long modCounter;

        public IteratorHelper() {
            iterIndex = 0;
        }

        public boolean hasNext() {
            return iterIndex < currSize;
        }
    }



}

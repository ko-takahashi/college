//Kosuke Takahashi
//cs0943
//Riggins
//CS310
//prog2

package data_structures;

import java.util.Iterator;
import java.util.ConcurrentModificationException;
import java.util.NoSuchElementException;

public class UnorderedLinkedListPriorityQueue<E extends Comparable<E>> implements PriorityQueue<E> {
	private class Node<E> {
		E data;
		Node<E> next;

		public Node(E d) {
			data = d;
			next = null;
		}
	}

	//public static final int DEFAULT_MAX_CAPACITY = 1000;
	public int currentSize;
	public Node<E> head;
	protected int modCounter;

	//  Inserts a new object into the priority queue.  Returns true if
	//  the insertion is successful.  If the PQ is full, the insertion
	//  is aborted, and the method returns false.
	public boolean insert(E object) {
		Node<E> newNode = new Node<E>(object);
		newNode.next = head;
		head = newNode;
		currentSize++;
		modCounter++;
		return true;
	}

	//  Removes the object of highest priority that has been in the
	//  PQ the longest, and returns it.  Returns null if the PQ is empty.
	public E remove() {
		Node<E> prev = null, curr = head, minPrev = null, minCurr = head;
		if (isEmpty())
			return null;
		E temp = head.data;
		while (curr != null) {
			if (curr.data.compareTo(temp) <= 0) {
				temp = curr.data;
				minPrev = prev;
				minCurr = curr;
			}
			prev = curr;
			curr = curr.next;
		}
		if (minPrev == null)
			head = head.next;
		else
			minPrev.next = minCurr.next;
		currentSize--;
		modCounter++;
		return temp;
	}

	//  Deletes all instances of the parameter obj from the PQ if found, and
	//  returns true.  Returns false if no match to the parameter obj is found.
	public boolean delete(E obj) {
		if(isEmpty() || !contains(obj))
			return false;
		Node<E> curr = head, prev = head;
		while(curr != null) {
			if (currentSize == 1) {
				clear();
				return true;
			} else if (curr.data.compareTo(obj) == 0) {
				prev.next = curr.next;
				currentSize--;
			}
			curr = curr.next;
		}
		modCounter++;
		return true;
	}

	//  Returns the object of highest priority that has been in the
	//  PQ the longest, but does NOT remove it.
	//  Returns null if the PQ is empty.
	public E peek() {
		Node<E> curr = head;
		if(isEmpty())
			return null;
		E temp = head.data;

		while(curr != null) {
			if(curr.data.compareTo(temp) <= 0)
				temp = curr.data;
			curr = curr.next;
		}
		return temp;
	}


	//  Returns true if the priority queue contains the specified element
	//  false otherwise.
	public boolean contains(E obj) {
		Node<E> curr = head;
		while(curr != null) {
			if(curr.data.compareTo(obj) == 0)
				return true;
			curr = curr.next;
		}
		return false;
	}

	//  Returns the number of objects currently in the PQ.
	public int size() {
		return currentSize;
	}

	//  Returns the PQ to an empty state.
	public void clear() {
		head = null;
		currentSize = 0;
	}

	//  Returns true if the PQ is empty, otherwise false
	public boolean isEmpty() {
		return currentSize == 0;
	}

	//  Returns true if the PQ is full, otherwise false.  List based
	//  implementations should always return false.
	public boolean isFull() {
		return false;
	}

	//  Returns an iterator of the objects in the PQ, in no particular
	//  order.
	public Iterator<E> iterator() {
		return new IteratorHelper();
	}

	class IteratorHelper implements Iterator <E> {
		Node<E> iterIndex;
		Node<E> nxtIndex;
		long stateCheck;

		public IteratorHelper() {
			iterIndex = head;
			stateCheck = modCounter;
		}

		public boolean hasNext() {
			if(stateCheck != modCounter)
				throw new ConcurrentModificationException();
			return iterIndex != null;
		}

		public E next() {
			if(!hasNext())
				throw new NoSuchElementException();
			E tmp = iterIndex.data;
			iterIndex = iterIndex.next;
			return tmp;
		}
	}

} 

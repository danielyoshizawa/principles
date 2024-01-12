# Arrays and Strings (page 88)
## Hash Tables
A hash table is a data structure that maps keys to values for highly effeicient lookup. There are a number of ways of implmenting this. Here, we will describe a simple but common implementation.

In this simple implementation, we use an array of linked lists and a hash code function. To insert a key (which might be a string or essentially any other data type) and value, we do the following:

1. First, compute the key's hash code, which will usually be an int or long. Note that two different keys could have the same hash code, as there may be an infinite number of keys and a finite number of ints.
2. Then, map the hash code to an index in the array. This could be done with something like hash(key) % array_lenght. Two different hash codes could, of couser, map to the same index.
3. At this index, there is a linked list of keys and values. Store the key and value in this index. We must use a linked list because of collisions: you could have two different keys with the same hash code, or two different hash codes that map to the same index.

To retrieve the value pair by its key, you repeat this process. Compute the hash code from the key, and then compute the index from the hash code. Then, search through the linked list for the values with this key.

If the number of collision is very high, the worst case is O(N), where N is the number of keys. However, we generally assume a good implementation that keeps collisions to a minimum, in which case the lookup time is O(1).

!! Table is not working on my md processor, check that later

| Key | Hash | Array index | Linked List |
| --- | --- | --- |
| "hi" | 10320 | 0 | ["hi", "abc"] |
| "abc" | 980 | 0 | ["hi", "abc"] |
| "aa" | 897 | 2 | ["aa", "qs"] |
| "qs" | 897 | 2 | ["aa", "qs"] |
| "pl" | 63 | 3 |  ["pl"] |

Alternatively, we can implement the hash table with a balanced binary search tree. This gives us an O( log N) lookup time. The advantage of this is potentially using less space, since we no longer allocate a large array. We can also iterate through the keys in order, which can be useful sometimes.

## ArrayList & Resizable Arrays

In some languages, arrays (often called lists in this case) are automatically resizable. The array or list will grow as you append items. In other languages, like Java, arrays are fixed length. The size is defined when you create the array.

When you need an array-like data structure that offers dynamic resizing, you would usually use an ArrayList. An ArrayList is an array that resizes itself as needed while still providing O(1) access. A typical implementation is that when the array is full, the array doubles in size. Each doubling takes O(N) time, but happens so rarely that its amortized insertion time is still O(1).

```
ArrayList<String> merge(String[] words, String[] more) {
    ArrayList<String> sentence = new ArrayList<String>();
    for (String w : words) sentence.add(w);
    for (String w : more) sentence.add(w);
    return sentence;
}
```

This is an essential data structure for interviews. Be sure you are comfortable with dynamically resizable arrays/lists in whatever language you will be working with. Note that the name of the data structure as well as the "resizing factor" (which is 2 in Java) can vary.

### Why is the amortized insertion runtime O(1)?
Suppose you have an array of size N. We can work backwards to compute how many elements we copied at each capacity increase. Observe that when we increase the array to K elements, the array was previously half that size. Therefore, we need to copy k/2 elements.

- final capacity increase : n/2 elements to copy
- previous capacity increase : n/4 elements to copy
- previous capacity increase : n/8 elements to copy
- previous capacity increase : n/16 elements to copy
- ...
- second capacity increase : 2 elements to copy
- first capacity increase : 1 elements to copy

Therefore, the total number of copies to insert N elements is roughly n/2 + n/4 + n/8 ... + 2 + 1, which is just less than N.

> If the sum of this series isn't obviuous to you, imagine this: Suppose you have a kilometer-long walk to the store. You walk 0.5 kilometers, and then 0.25 kilometers, and then 0.125 kilometers, and so on. You will never exceed one kilometer (although you'll get very close to it).

Therefore, inserting N elements takes O(N) work total. Each insertions is O(1) on average, even though some insertions take O(N) time in the worst case.

## StringBuilder

Imagine you were concatenating a list of strings, as shown below. What would the running time of this code be? For simplicity, assume that the strings are all the same length (call this x) and that there are n strings.

```
String joinWords(String [] words) {
    String sequence = "";
    For (String w : words) {
        sentence = sentence + w;
    }
    return sentence;
}
```

On each concatenation, a new copy of the string is created, and the two strings are copied over, character by character. The first iteration requires us to copy x characters. The second iteration requires 2x characters. The third iteration requires 3x, and so on. The total time therefore is O(x + 2x + 3x + ... nx). This reduces to O(xn^2).

> Why is it O(xn^2)? Because 1+2+3+...+n equals n(n+1)/2, or O(n^2)

StringBuilder can help you avoid this problem. StringBuilder simply creates a resizable array of all the strings, copying them back to a string only when necessary.

```
String joinWords(String[] words) {
    StringBuilder sentence = new StringBuilder();
    for (String w : words) {
        sentence.append(w);
    }
    return sentence.toString();
}
```

A good exercise to practice strings, arrays, and general data structures is to implement your own version of StringBuilder, HashTable and ArrayList.

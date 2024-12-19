# Approach Documentation
The documentation has two parts, the first part is the “Implementation.” This explains how I implemented my solution from the ADTs that were provided. The second part is the “Test.” This shows how I tested each required function. Both sections will be discussed relative to the two files that I worked on, Abag.h and BDictionary.
 Before starting to work on my implementation and testing, I needed to understand the problem more thoroughly. To do that I drew a flowchart to see the inheritance of the different header files. This gave me a foundation to work on.

The approach I took was to reverse engineer the code conceptually. I had to figure out how the methods in BDictionary.h were supposed to work and backwards. I saw what functionality I needed in BDictionary.h and tailored my ABag.h to work with it. The following paragraphs show where Abag.h and BDictionary.h interact.
First lets look at the constructors in BDictionary (BDictionary(int cap)). The first step to getting the BDictionary to work was giving it the ability to initialize an Abag object which serves as the storage for the KVpair<Key,E> items. The instance has a dynamic allocation, and it is stored in the “dictionary “pointer.

Next naturally we would want destructors to deallocate the memory when the object is destroyed. This function

Now the first method that I needed to make work was the “clear()” method. Basically, I needed a method from the Abag.h file that I can call to reset the contests of dictionary. To do that I saw that the “emptyBag()” method would be the right fit.
Now within “emptyBag()”, to achieve this, I set the “currentSize” to zero.
To test it out I ended up just writing a separate test file. I created three Abag objects and used them to test my methods. 
The following code shows how I tested the emptyBag() with my test file.


With that, it was ready to be used by the “clear()” method in BDictionary.h.


The next method I worked on was the “insert()” method. The ADT functionality of this method is that it should be able to insert or add an object, in this case a KVpair to the dictionary. Logically, when looking through the different ATD methods for Abag.h, the “AddItem()” method was the method to use. The following code shows how it was implemented.
Bacially  if the ”currentSize" is less than the” capacity “, that means that there is space in the array. If so, it will add the item to the array and increment the ”currentSize” so that the capacity is accurately reflected.
Tested the above code in my test file: 


It was working right because in the previous line I cleared the array so adding the three items would make the count to 3.
This was then used in my insert method in BDictionary.h as show below.

The insert method creates a KVpair object with the specified key k and value e. It then uses ABag's addItem() method to add this key-value pair to the dictionary. The method returns true if the addition succeeds (i.e., if there is available capacity in dictionary), or false if the dictionary is full.
The next method I looked at was the remove() method. The remove method took a little bit to wrap my head around.  I know that it's simple job was to remove a KVpair from the array. This method actually calls two methods from the Abag.h file. In order to remove an item from the array, first we need to find it. This is where the find() method comes in handy. After we have found the item, we need to remove it, hence using the remove() method.
This is how it works, first in the remove() method in the BDictionary.h  creates a temporary KVpair with the k being the value searched and v just being a default value. Now the key part from my understanding, this value is put at the end of the array because it is the newest.  Using the find() method you can iterate through the list comparing k values with the k value in the temporary KVpair object.

Once the item is found we can use the remove function to remove it and replace it.
 
The above code basically removes the item and replaces it with the last item in the array which is the temporary KVpair object. This is show in the code before for the remove() method in BDictionary.

Again this was tested out with my test file.

The next method in BDictionary.h is removeAny(). From understanding the ADT, this method just removes any value from the array.
From looking at the different methods given in the Abag.h, it is most likely that it will use the removeTop() method. This will allow it to remove the last item in the array.
This just removes the last item in the array. The below code shows how the removeTop() is used in removeAny() function.

This was also tested out with my test file.


The next method I worked on in the BDictionary.h was the find() method. Now the replace() method I worked on previously, was similar to this. Basically, the find() method is just the replace() method without the remove function.

It calls the find() method in Abag.h.
It was also tested and shown in the replace() method.
The last method in the BDictionary file was size(). The basic idea of this method is that it counts the KVpair objects in the array and returns how many values are there. It utilizes the size() method in the Abag.h file.
Pretty straightforward. Also tested it with my test file and it works fine. The following code shows how it is called in the BDictionary.h.


Out of all the methods that were used in the Abag.h file, three methods were not used; the inspectTop(), operator+=() and the bagCapacity(). To demonstrate the functionality of these methods, the mybagDemo() method was created. It is called in the main.cpp.
InspectTop Allows viewing of the top item (last added item) without removing it. Assigns the item to item and returns true if the bag is not empty, or false if it is.
Bacically it is like remove() but does not remove the item.
Operator+=() Overloads the += operator to add an item to the bag, by internally calling addItem(addend), enabling syntax like bag += item.

BagCapacity() Returns the maximum capacity of the bag by returning capacity.

All this functionality is showed in the myBagDemo() method.

In summary, implemented and tested two main files, ABag.h and BDictionary.h, using a methodical approach based on understanding class relationships through a flowchart. By reverse-engineering BDictionary requirements, they tailored ABag to provide essential methods like emptyBag(), addItem(), find(), removeTop(), and size(), which BDictionary uses for storing and managing KVpair key-value pairs. Constructors set up dynamic allocation for storage, while methods like insert(), clear(), and remove() delegate functionality to ABag, ensuring items are managed according to ADT specifications. Testing confirmed each method’s functionality via custom test files, verifying behaviors like insertion, deletion, and capacity handling. Additionally, unused ABag methods—inspectTop(), operator+=(), and bagCapacity()—were showcased in a demonstration method, myBagDemo().
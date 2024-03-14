/* Ordered Set Implemented in an Unrolled (Doubly)-Linked List */
// File: OSULL.h

#include <iostream>
#include <cstring>
using namespace std;


template <typename T, int initNodeCapacity = 1000 > 
class OSULL
{
public:
   OSULL(){

      // set the node capacity  
      nodeCapacity = initNodeCapacity ;

      // make the front and back dummy nodes 
      front = new Node( nullptr, nullptr, nodeCapacity );
      back = new Node( front, nullptr, nodeCapacity );
      front->next = back;

      size = 0 ;
      nodeCount = 0 ; 
   }
   ~OSULL(){
      Node * cursor = front ;
      while( cursor != nullptr ){
         Node * current = cursor ;
         cursor = cursor-> next ;
         delete  current ;
      }
   }
   bool isEmpty(){ return size==0 ;}
   int get_size(){ return size ;}

   bool insert(T item){
      // inserts item into the list, if it is not there already
      // returns true if inserted; false if it was already there
      //
      // IMPLEMENT THIS
      //
      Node* cursor = front->next;
      if (cursor == back) {
         Node * initNode = new Node(front, back, front->capacity);
         nodeCount++;
         cursor = initNode;
         cursor->prev->next = cursor;
         cursor->next->prev = cursor;
      }
      while (cursor->getMax() < item && cursor != back) {
         cursor = cursor->next;
      }
      if (cursor->find(item) && cursor != back) {
         return false;
      } else {
         if (cursor->getMin() > item || cursor == back) {
            cursor = cursor->prev;
         }
         cursor->insert(item);
         if (cursor->getSize() == cursor->getCapacity()) {
            Node* newNode = new Node(cursor, cursor->next, nodeCapacity);
            cursor->next->prev = newNode;
            cursor->next = newNode;
            nodeCount++;
            for (int i = cursor->capacity/2; i < cursor->capacity; i++) {
               newNode->insert(cursor->data[cursor->capacity/2]);
               cursor->remove(cursor->data[cursor->capacity/2]);
            }
         }
         if (item%50000 == 49999) {
            cout << "item: " << item << endl;
         }
         return true;
      }
   }

   bool find(T item){ 
      // searches for item in the list
      // returns true if found; false otherwise 
      //
      // IMPLEMENT THIS 
      //
      Node* cursor = front->next;
      while (cursor->getMax() < item && cursor != back) {
         cursor = cursor->next;
      }
      return cursor->find(item);
   }

   bool remove(T item){
      // removes item from the list 
      // returns false if the item was not there; true if it was
      //
      // IMPLEMENT THIS
      //
      Node* cursor = front->next;
      while (cursor->getMax() < item && cursor != back) {
         cursor = cursor->next;
      }
      if (cursor->remove(item)) {
         if (cursor->getSize() < nodeCapacity/2) {
            if (cursor->next != back && cursor->next->getSize() > nodeCapacity/2) {
               cursor->insert(cursor->next->data[0]);
               cursor->next->remove(cursor->next->data[0]);
            } else if (cursor->prev != front && cursor->prev->getSize() > nodeCapacity/2) {
               cursor->insert(cursor->prev->data[cursor->prev->getSize()-1]);
               cursor->prev->remove(cursor->prev->data[cursor->prev->getSize()-1]);
            } else {
               Node* mergeNode;
               if (cursor->next != back) {
                  mergeNode = cursor->next;
               } else {
                  mergeNode = cursor->prev;
               }
               for (int i = 0; i < mergeNode->getSize(); i++) {
                  cursor->insert(mergeNode->data[i]);
               }
               cursor->next = mergeNode->next;
               mergeNode->next->prev = cursor;
               delete mergeNode;
               nodeCount--;
            }
         }
         return true;
      }
      return false;
   }

   T getMin(){// returns the minimum item in the lise
      // requires: size not 0 
      return front->next->getMin(); 
      } 

   T getMax(){// returns the maximum item in the list
      // requires: size not 0 
      return back->prev->getMax();
      }

   void display(){
      // prints out the list contents 
      Node * cursor = front-> next ;
      cout << "<" ;
      while( cursor != back ){
         cursor -> display() ; 
         cursor = cursor-> next ;
      }
      cout << " >\n" ;
   }
      
private:

   class Node{
      public: 
      Node( Node* prev, Node* next, int capacity ){
         // notice that we can use the constructor arguments to 
         // do most o the work of inserting a new node into the list 
         this->prev = prev ;
         this->next = next ;
         this->capacity = capacity ;
         data = new T[capacity] ;
         size = 0 ;
      }
      ~Node(){
         delete [] data ;
      }
      Node * prev ; // pointer to the next node 
      Node * next ; // pointer to the previous nodes 
      int capacity ; // capacity of this node 
      T * data ; // array of data items in this node 
      int size ; // current number of items in this node 
      int getCapacity(){// return the capacity of this node 
         return capacity; 
      }
      int getSize(){// return the number of items in this node
         return size; 
      }
      T getMin(){// return the smallest item in this node
         // requires: this->size not 0 
         return data[0] ; 
      }
      T getMax(){// return the largest item in this node 
         // requires: this->size not 0 
         return data[size-1] ; 
      }
      bool insert(T item){
         // inserts item into this node if it was not already there 
         // returns true if the item was inserted, false otherwise 
         // assumes that this node is not full
	 //
         // IMPLEMENT THIS 
         int i = size-1;
         while (i >= 0 && data[i] > item) {
            data[i+1] = data[i];
            i--;
         }
         data[i+1] = item;
         size++;
         return true;
	 //
      }
      bool find(T item){
         // searches for item in this node 
         // returns true if found, false otherwise 
	 //
         // IMPLEMENT THIS
	 //
         int low = 0;
         int high = size-1;
         while (low <= high) {
            int mid = (low + high) / 2;
            if (item == data[mid]) {
               return true;
            } else if (item < data[mid]) {
               high = mid - 1;
            } else {
               low = mid + 1;
            }
         }
         return false;
      }
      bool remove(T item){
         // remove item from this node
         // returns true if the item was removed, false otherwise 
         // assumes that this node is not empty
	 //
         // IMLEMENT THIS
         int pos;
         int low = 0;
         int high = size-1;
         while (low <= high) {
            int mid = 1+(low + high) / 2;
            if (item == data[mid]) {
               pos = mid;
               break;
            } else if (item < data[mid]) {
               high = mid - 1;
            } else {
               low = mid + 1;
            }
         }
         cout << "mid: " << data[pos] << endl;
         size--;
         while (pos < size) {
            cout << "data: " << data[pos] << " data+1: " << data[pos+1] << "pos: " << pos << "\n";
            data[pos] = data[pos+1];
            pos++;
         }
         
         return true;
	 //
      }
      void display(){// print the contents of this list 
	 // 
         // IMPLEMENT THIS
         cout << "Disp called at";
         for (int i = 0; i < size; i++) {
            cout << "loop\n";
            cout << " " << data[i];
         }
         

	 //
	 //
      } 
   };

   int size ; // current number of items 
   int nodeCount ; // current number of nodes 
   int nodeCapacity ; // capacity to assign to new nodes 
   Node * front ; // pointer to front dummy node 
   Node * back ;  // pointer to back dummy node 
};

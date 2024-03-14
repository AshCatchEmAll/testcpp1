#include "OSULL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
using namespace std;

static const int NUMS_PER_LINE = 14;


int main( )
{
    cout << "testing functionality...\n" ; 
    OSULL<int> * lst1 = new OSULL<int> ;
    // Tests adding items, covers adding items when node is full and causes split
    cout << "inserting 20 items into new list\n" ;
    for (int i = 0; i < 20; i++) {
        if(lst1->insert(i)) {
            cout << "inserted: " << i << "\n";
            lst1->display();
        };
        
    }
    
    // Tests finding items in beginning, end and middle of array in data. Also tests item not in list.
    cout << "\nfinding 0: " <<  ((lst1->find(0)) ? "yes": "no") << "\n" ;
    cout << "finding 9: " <<  ((lst1->find(9)) ? "yes": "no") << "\n" ;
    cout << "finding 16: " <<  ((lst1->find(16)) ? "yes": "no") << "\n" ;
    cout << "finding 29: " <<  ((lst1->find(29)) ? "yes": "no") << "\n" ;
    cout << "Adding another 10 ints (20-29) to list\n";
    for (int i = 20; i < 31; i++) {
        lst1->insert(i);
    }
    lst1->display();
    // Tests removing items from middle node (10-19), causing the node to pull one int from the next node
    // then also removes another item, causing two of three nodes to merge
    lst1->remove(19);
    lst1->display();
    lst1->remove(18);
    lst1->display();
    // Tests getting max and min of list
    cout << "\nmax: " << lst1->getMax();
    cout << "\n" ;
    cout << "min: " << lst1->getMin();
    cout << "\n" ;
    cout << "\n" ;

    // OSULL<int> * lst2 = new OSULL<int> ;
    // // Tests adding new item that is between two nodes (50 is between 0-9 and 90-99)
    // cout << "inserting 0-9, 90-99 into new list\n" ;
    // for (int i = 0; i < 10; i++) {
    //     lst2->insert(i);
    // }
    // for (int i = 90; i < 100; i++) {
    //     lst2->insert(i);
    // }
    // lst2->display();
    // cout << "inserting 50 into list\n" ;
    // lst2->insert(50);
    // lst2->insert(51);
    // lst2->display();
    // delete lst2; 
    // cout << "\n" ;

    // OSULL<int> * lst5 = new OSULL<int>;
    // time_t start, end;

    // for( int i = 1000000 ; i > 0 ; i-- )
    // {
    //     lst5->insert( i );
    //     // a[ i ] = j ;
    // }
    // start = time(NULL);
    // lst5->remove(999999);
    // end = time(NULL);
    // double diff = difftime(end, start);
    // cout << "Time to traverse 5000000 elements: " << fixed << diff << setprecision(5) << " seconds\n";

    
    // cout << "\n" ;
    // cout << "\n" ;
    // cout << "done\n";

    delete lst1;

    return 0;
}

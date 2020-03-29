#include <iostream>
#include "priorityqueue.h"
int main() {
    PriorityQueue pq(5);
    pq.insert(std::make_pair(5,std::make_pair(2,3)));
    pq.insert(std::make_pair(1,std::make_pair(3,4)));
    pq.insert(std::make_pair(4,std::make_pair(3,4)));

    // std::cout << pq.JSON().dump(2) << "\n";

   // pq.removeMin();
   // pq.removeMin();

   //pq.removeNode(1);
    std::cout << pq.JSON().dump(2) << "\n";
    return 0;
}
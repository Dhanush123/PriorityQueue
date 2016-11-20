//Programmer: Dhanush Patel
//Programmer ID: 1553428

#ifndef PRIORITYQUEUE_PRIORITYQUEUE_H
#define PRIORITYQUEUE_PRIORITYQUEUE_H

#include <algorithm>
using namespace std;

template <typename V>
class PriorityQueue{
  int siz;
  int cap;
  V* values;
  void capacity(int); //done

public:
  PriorityQueue(int=2); //done
  void push(const V&); // requires that less-than be defined, done
  V top() const{return values[0];} // returns a copy of the largest value, done
  int size(){return siz;} // initially zero, done
  bool empty(){return siz==0;} // there's no values -- size is zero, done
  void pop(); // void setter loses highest value, done
  void clear(){siz=0;} // setter that sets siz to zero, done

  PriorityQueue(const PriorityQueue<V>&); // done
  ~PriorityQueue() {delete [] values;} //done
  PriorityQueue<V>& operator=(const PriorityQueue<V>&); //done
};

template <typename V>
PriorityQueue<V>::PriorityQueue(int CAP) {
  this->cap = CAP;
  siz = 0;
  values = new V[cap];

  for (int index = 0; index < cap; index++){
    values[index] = V();
  }
}

template <typename V>
void PriorityQueue<V>::capacity(int newCap)
{
  V* temp = new V[newCap];

  // get the lesser of the new and old capacities
  int limit = min(newCap, cap);

  // copy the contents
  for (int i = 0; i < limit; i++){
    temp[i] = values[i];
  }

  // set added values to their defaults
  for (int i = limit; i < cap; i++){
    temp[i] = V();
  }

  // deallocate original array
  delete [] values;

  // switch newly allocated array into the object
  values = temp;

  // update the capacity
  cap = newCap;
}


template <typename V>
void PriorityQueue<V>::push(const V& e){
  if (siz >= cap){
    capacity(2 * cap);
  }
  values[siz] = e;
  int index = siz;
  int pIndex = ((index + 1) / 2) - 1;
  while (!(pIndex < 0 || values[index] < values[pIndex])){
    swap(values[index], values[pIndex]);
    index = pIndex;
    pIndex = ((index + 1) / 2) - 1;
  }
  siz++;
}

template <typename V>
void PriorityQueue<V>::pop(){
  siz--;
  int index = 0;
  while(true) {
    int lIndex = 2 * index + 1;
    int rIndex = 2 * index + 2;
    if(rIndex < siz){
      if(values[lIndex] < values[siz] && values[rIndex] < values[siz]){
        break;
      }
      else if(values[siz] < values[lIndex] && values[rIndex] < values[lIndex]){
        values[index] = values[lIndex];
        index = lIndex;
      }
      else{
        values[index] = values[rIndex];
        index = rIndex;
      }
    }
    else if(lIndex < siz){
      if(values[lIndex] < values[siz]){
        break;
      }
      else{
        values[index] = values[lIndex];
        index = lIndex;
      }
    }
    else{
      break; //all done
    }
  }
  values[index] = values[siz];
}

template <typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& original) {
  siz = original.siz; //still copy
  cap = original.cap; // still copy
  values = new V[cap]; // not copy, is new
  for (int i = 0; i < cap; i++){ // contents copy original to new
    values[i] = original.values[i];
  }
}

template <typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& original) {
  if (this != &original){ //check if copy or not, better not be tho
    // same as destructor
    delete [] values;

    // same as copy constructor
    cap = original.cap;
    siz = original.siz;
    values = new V[cap]; // not copy, is new
    for (int i = 0; i < cap; i++){ // contents copy original to new
      values[i] = original.values[i];
    }
  }
  return *this; // return self reference
}

#endif //PRIORITYQUEUE_PRIORITYQUEUE_H

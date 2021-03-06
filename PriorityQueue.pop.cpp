//Programmer: Dhanush Patel
//Programmer ID: 1553428

#include <iostream> // for cout, ios, and endl
#include <string> // for string
using namespace std;

#include <cassert> // for assert
#include <cmath> // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

#include "PriorityQueue.h"

int main(){
  srand(time(0)); rand(); // seed the random number generator (in case you need it)

  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;

  // programmer customization go here
  int n = 1000000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  const int nReps = n / 100; // one percent of starting n

  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  double expectedSeconds = 0;

  for(int cycle = 0; cycle < 4; cycle++, n*= 2){
    // problem setup goes here -- create a data structure of size n
    PriorityQueue<int> timeQ(n * 2);
    
    for(int i = 0; i < n; i++){
      timeQ.push(i);
    }

    // assert that n is the size of the data structure if applicable
    assert(timeQ.size() == n);

    //making 1 more...a copy
    PriorityQueue<int> timeQ2 = timeQ;
    while(!timeQ2.empty()){ //test pop for 2nd  and seeing if structure is legit
      int temp = timeQ2.top();
      timeQ2.pop();
      assert(temp >= timeQ2.top());
    }

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    for(int rep = 0; rep < nReps; rep++){ //now popping the 1st PQ for timing purposes
      timeQ.pop();
    }

    // do something where n is the "size" of the problem
    clock_t endTime = clock();

    // validation block -- assure that process worked if applicable
    assert(timeQ.size() == n - nReps);
    timeQ2 = timeQ;

    while(!timeQ2.empty()){ // making sure 2nd PQ is still legit
      int temp = timeQ2.top();
      timeQ2.pop();
      assert(temp >= timeQ2.top());
    }

    // cleanup if applicable

    // compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if(cycle == 0){ 
	elapsedSecondsNorm = elapsedSeconds;
    }
    expectedSeconds = log(double(n)) / log(n / factor) * elapsedSecondsNorm;

    // reporting block
    cout << elapsedSeconds;
    if (cycle == 0) cout << " (expected O(log n))";
    else cout << " (expected: " << expectedSeconds << ')';
    cout << " for n=" << n << endl;

  }
  return 0;
}
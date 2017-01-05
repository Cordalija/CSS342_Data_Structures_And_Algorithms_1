// Jasenko..Cordalija, CS342, Program 2, 10/19/2015

#include <iostream>
#include <sys/time.h>

using namespace std; 


int main() {
	//-------------------- Program 2----------------------------

        struct timeval startTime; // start and end time for program
	struct timeval endTime;


	int n = 0; // set to default

	cout << "Enter Number n, n > 8  ";	// number to be 8 to ....
	cin >> n;

	gettimeofday(&startTime, NULL); // where it starts the timing

	int maxJ = 0 ; // biggest GCD (X,....)
	int maxK = 0; // biggest GCD (....,Y)
	int maxCost = 0; // how many times % aka cost

	for (int i = 8; i <= n; i++) { // 8 through n

		for (int j = 1; j < i; j++) { // x goes from 1- what i is (1 through 7)
			
			for (int k = j + 1; k <= i; k++) { // y goes from 1 above what x is and upto what i is (2 through 8)
				
				int aj = j;
				int bk = k;
				int r;

				int tempCost = 0; // set default value of temporary Cost to 0

				while (bk > 1) {	// counts down until bk which is the yVariable in GCD reaches 1 or 0
					r = aj % bk;
					aj = bk;
					bk = r;
					tempCost++;   // each time it need to mod, cost increments to keep track of # of mods required
				}

					if (tempCost > maxCost) { // once it find another GCD with more times # of modules
						maxJ = j; // gives original (8,13) instead of the reduced (3,2) which is right before whileLoop cuts out
						maxK = k;
						maxCost = tempCost; // changes max cost to what is currently higher =  req more %s
					}

					
			} 
		}
		// gives answer! returns at what 2 integers the & has highest amount of times done and what the two integers are
		cout << "At i=" << i << "; gcd (" << maxJ << "," << maxK << ") = 1 took " << maxCost << " modulus operations" << endl; // << "time" << end_time.tv_sec - start_time.tv_sec << endl;
		
	        gettimeofday(&endTime, NULL); // Timing of program ends here
		// gives out the duration it took to run
}
	cout << "Time duration in microseconds: " << ((endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec)) << endl;

	return 0;
}

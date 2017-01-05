//Jasenko Cordalija

#include <vector>
#include <math.h> // may need to use pow( )
using namespace std;


// merge function, merging <Comparable> arrays
template <class Comparable>
void merge(vector<Comparable> &a, vector <Comparable> &b, int first, int mid, int last) {

	// initilizes first > mid & mid+1 > last for merging arrays
	int first1 = first;
	int first2 = mid + 1;
	int last1 = mid;
	int last2 = last;

	// index set to first for help with arrays
	int index = first1;
	// checks first with mid and mid+1 with last
	for (; (first1 <= last1) && (first2 <= last2); ++index) {
		if (a[first1] < a[first2]) { // if first is smaller then mid+1 do this
			b[index] = a[first1];
			++first1;
		}
		else { // if first is bigger then mid+1 do this
			b[index] = a[first2];
			++first2;
		}
	}

	// first is smaller or equal to mid, throw first # into array b(temp) and increment
	for (; first1 <= last1; ++first1, ++index) {
		b[index] = a[first1];
	}
	// mid +1 is smaller or equal to last , throw  mid+1 # into array b(temp) and increment
	for (; first2 <= last2; ++first2, ++index) {
		b[index] = a[first2];
	}
}


// function mergesort improved, non-rec mergesort function
template <class Comparable>
void mergesortImproved(vector<Comparable> &a) { // original array is a

	int size = a.size();	// size of array a is b's as well
	vector<Comparable> b(size);  // this is only one temporary array. 

	// goes through array each time by 2. ex: 2-4-8 etc
	// while i at 1 is < a's size do this, increment is at bottom
		int i=1;
		while(i < a.size()){

		// for array takes i *2 and increments j by that
		// while j at 0 is < a's size do this, increment for this at bottom
		int j=0;
		while(j <a.size()){

			// first is beginning of j
			int first = j;
			// mid of j is j + what i is at -1
			int mid = j + (i - 1);
			// *last of j is j + what i is *2 then subtracted by 1
			int last = j +((2*i)-1);

			// changes mids size if > a to a-1 becuase array start at 0
			if (mid > a.size()-1) {
				mid = a.size() - 1;
			}
			// changes lasts size if > a to a-1 because array start at 0
			if (last > a.size()-1) {
				last = a.size() - 1;
			}

			// merge function for merging arrays
			merge(a, b, first, mid, last);

			// j's increment
			j += 2*i;
		}
		// copies all of temp array into original
		for (int i = 0; i <= a.size() - 1; i++) {
			a[i] = b[i];
		}
		// i's increment
		i*=2;
	}
}




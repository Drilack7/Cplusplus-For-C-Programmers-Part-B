//sorting algorithms: Prototypes

template<class RandAcc>
void sort(RandAcc b, RandAcc e);
//Quicksort algorithm over elements b to e

template<class RandAcc>
void stable_sort(RandAcc b, RandAcc e);
//Stable sorting algorithm over elements b to e
//Elements remain in their relative same position(2,1,1 gets the 2nd "1" 1st)

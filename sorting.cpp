
/*
  Program discussing various sorting algorithms like Insertion Sort, Binary Insertion Sort, Selection Sort,
  Quick Sort, Merge Sort, Heap Sort, Counting Sort, and Radix Sort. Both Counting sort and Radix sort supports
  only int data type, but rest of them support all data types.
  
  You also have the ability to sort a portion of an array using low and high variables. You can also sort the
  array in non-decreasing or non-increasing order. The default behavior is non-decreasing order.
*/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

template <class T> void display(T *arr, int high, int low = 0) ;
template <class T> void swap(T *a, T *b) ;
int getMax(int *arr, int high, int low = 0) ;

/*
    Insertion Sort Procedure
    @param arr   - input array
    @param high  - last index of input array
    @param low   - first index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
void insertionSort(T *arr, int high, int low = 0, bool order = 0) {
    for (int i = low + 1; i <= high; i++) {
        int j    = i ;
        T key    = arr[i] ,
          cmp    = order ? key : arr[j - 1] ,
          cmpKey = order ? arr[j - 1] : key ;
        while (j > low && cmp > cmpKey) {
            arr[j] = arr[j - 1] ;
            j-- ;
            cmp    = order ? key : arr[j - 1] ;
            cmpKey = order ? arr[j - 1] : key ;
        }
        arr[j] = key ;
    }
}


/*
    Binary Insertion Sort Procedure
        In this method, instead of traditional linear search to find the correct position of an element,
        we apply binary search to find the correct position of that element
    @param arr   - input array
    @param high  - last index of input array
    @param low   - first index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
void binaryInsertionSort(T *arr, int high, int low = 0, bool order = 0) {
    for (int i = low + 1; i <= high; i++) {
        T key   = arr[i] ;
        int l   = low ,
            h   = i ,
            mid = -1 ;
        while (l < h) {
            mid = l + (h - l) / 2 ;
            T cmp     = order ? arr[mid] : key ,
              cmpKey  = order ? key : arr[mid] ;
            if (cmp >= cmpKey) {
                l = mid + 1 ;
            } else {
                h = mid ;
            }
        }
        for (int j = i; j > l; j--) {
            swap<T>(&arr[j - 1], &arr[j]) ;
        }
    }
}


/*
    Selection Sort Procedure
    @param arr   - input array
    @param high  - last index of input array
    @param low   - first index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
void selectionSort(T *arr, int high, int low = 0, bool order = 0) {
    for (int i = low; i < high; i++) {
        int key   = i ;
        T cmp     = order ? arr[key]: arr[i + 1],
          cmpKey  = order ? arr[i + 1] : arr[key] ;
        for (int j = i + 1; j <= high; j++) {
            if (cmp < cmpKey) {
                key = j ;
            }
            cmp     = order ? arr[key]: arr[j + 1] ;
            cmpKey  = order ? arr[j + 1] : arr[key] ;
        }
        if (i != key) {
            swap<T>(&arr[i], &arr[key]) ;
        }
    }
}


/*
    Merge Sort Procedure
        merge       - Function to merge two subarrays
        mergeSort   - Function to split an array into two subarrays, and recursively call itself on those two subarrays
                      and merge them using merge helper function
                      If the size of the two sub arrays is less than 100, instead of calling merge sort recursively on
                      both of them, insertion sort is applied on both, and then merged
    @param arr   - input array
    @param low   - first index of input array
    @param mid   - middle index of input array
    @param high  - last index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
void merge(T *arr, int high, int mid, int low, bool order) {
    int i = low, j = mid + 1, k = 0 ;
    T B[high - low + 1] ;
    while (i <= mid && j <= high) {
        if ((order ? arr[i] > arr[j] : arr[i] < arr[j])) {
            B[k++] = arr[i++] ;
        } else {
            B[k++] = arr[j++] ;
        }
    }
    while (i <= mid) {
        B[k++] = arr[i++] ;
    }
    while (j <= high) {
        B[k++] = arr[j++] ;
    }
    while (--k >= 0) {
        arr[low + k] = B[k] ;
    }
}

template <class T>
void mergeSort(T *arr, int high, int low = 0, bool order = 0) {
    if (low < high) {
        int mid = low + (high - low) / 2 ;
        if (mid - low < 100) {
            insertionSort<T>(arr, mid, low, order) ;
            insertionSort<T>(arr, high, mid + 1, order) ;
        } else {
            mergeSort<T>(arr, mid, low, order) ;
            mergeSort<T>(arr, high, mid + 1, order) ;
        }
        merge<T>(arr, high, mid, low, order) ;
    }
}



/*
    Heap Sort Procedure
        maxHeapify  - Function to make sure that max heap property is not violated for a single node
        minHeapify  - Function to make sure that min heap property is not violated for a single node
        buildHeap   - Function to build either min heap or max heap in O(n) time
        heapSort    - Function to sort an array by building min heap or max heap, and then deleting
                      root node, and then calling heapify function in O(nlogn) time
    @param arr      - input array
    @param pos      - node position on which we check whether heap property is violated
    @param high     - last index of the input array
    @param low      - first index of the input array
    @param order    - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
void maxHeapify(T *arr, int high, int low, int pos) {
    int lChild  = 2 * (pos - low) + low + 1 ,
        rChild  = 2 * (pos - low) + low + 2 ,
        largest = pos ;

    if (lChild <= high && arr[lChild] > arr[pos]) {
        largest = lChild ;
    }
    if (rChild <= high && arr[rChild] > arr[largest]) {
        largest = rChild ;
    }
    
    if (largest != pos) {
        swap<T>(&arr[pos], &arr[largest]) ;
        maxHeapify<T>(arr, high, low, largest) ;
    }
}

template <class T>
void minHeapify(T *arr, int high, int low, int pos) {
    int lChild   = 2 * (pos - low) + low + 1 ,
        rChild   = 2 * (pos - low) + low + 2 ,
        smallest = pos ;

    if (lChild <= high && arr[lChild] < arr[pos]) {
        smallest = lChild ;
    }
    if (rChild <= high && arr[rChild] < arr[smallest]) {
        smallest = rChild ;
    }

    if (smallest != pos) {
        swap<T>(&arr[pos], &arr[smallest]) ;
        minHeapify<T>(arr, high, low, smallest) ;
    }
}

template <class T>
void buildHeap(T *arr, int high, int low, int order) {
    if (order) {
        for (int i = high - low - !(high % 2); i >= low; i--) {
            minHeapify<T>(arr, high, low, i) ;
        }
    } else {
        for (int i = high - low - !(high % 2); i >= low; i--) {
            maxHeapify<T>(arr, high, low, i) ;
        }
    }
}

template <class T>
void heapSort(T *arr, int high, int low = 0, bool order = 0) {
    buildHeap<T>(arr, high, low, order) ;
    for (int i = high; i > low; i--) {
        swap<T>(&arr[low], &arr[i]) ;
        high-- ;
        if (order) {
            minHeapify<T>(arr, high, low, low) ;
        } else {
            maxHeapify<T>(arr, high, low, low) ;
        }
    }
}


/*
    Quick Sort Procedure
        partition   - Function to partition an array, with all elements less than pivot on the left, and all elements
                      greater than pivot on the right
        quickSort   - Function to split an array into two subarrays, and recursively call itself on those two subarrays
    @param arr   - input array
    @param low   - first index of input array
    @param high  - last index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
template <class T>
int partition(T *arr, int high, int low, bool order) {
    int pivotIndex = low + rand() % (low - high) ;
    T pivot = arr[pivotIndex] ;

    swap<T>(&arr[pivotIndex], &arr[high]) ;
    int j = low ;
    for (int i = low; i < high; i++) {
        T cmp     = order ? pivot : arr[i] ,
          cmpKey  = order ? arr[i] : pivot ;
        if (cmp < cmpKey) {
            swap<T>(&arr[i], &arr[j++]) ;
        }
    }
    swap<T>(&arr[high], &arr[j]) ;
    return j ;
}

template <class T>
void quickSort(T *arr, int high, int low = 0, bool order = 0) {
    if (low < high) {
        int pivot = partition<T>(arr, high, low, order) ;
        quickSort<T>(arr, pivot - 1, low, order) ;
        quickSort<T>(arr, high, pivot + 1, order) ;
    }
}


/*
    Counting Sort Procedure
    @param arr   - input array
    @param low   - first index of input array
    @param high  - last index of input array
    @param exp   - to be used as exponent in radix sort
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
void countingSort(int *arr, int high, int low = 0, int exp = 0, bool order = 0) {
    int size       = getMax(arr, high, low) ,
        temp[size + 1] ,
        output[high - low + 1] ;
    memset(temp, 0, (size + 1) * sizeof(int)) ;
    for (int i = low; i <= high; i++) {
        (exp ? temp[(arr[i] / exp) % 10] : temp[arr[i]]) += 1 ;
    }
    if (order) {
        for (int i = size - 1; i >= 0; i--) {
            temp[i] += temp[i + 1] ;
        }
    } else {
        for (int i = 1; i <= size; i++) {
            temp[i] += temp[i - 1] ;
        }
    }
    for (int i = high; i >= low; i--) {
        (exp ? output[temp[(arr[i] / exp) % 10] - 1] : output[temp[arr[i]] - 1]) = arr[i] ;
        (exp ? temp[(arr[i] / exp) % 10] : temp[arr[i]]) -= 1 ;
    }
    for (int i = low, j = 0; i <= high; j++, i++) {
        arr[i] = output[j] ;
    }
}


/*
    Radix Sort Procedure
    @param arr   - input array
    @param low   - first index of input array
    @param high  - last index of input array
    @param order - sorting in increasing (order = 0) or decreasing (order = 1) order
*/
void radixSort(int *arr, int high, int low = 0, bool order = 0) {
    int max = getMax(arr, high, low) ;
    for(int i = 1; max / i > 0; i *= 10) {
        countingSort(arr, high, low, i, order) ;
    }
}


/*
    Helper Functions
*/

int getMax(int *arr, int high, int low) {
    int max = arr[low] ;
    for (int i = low + 1; i <= high; i++) {
        if (arr[i] > max) {
            max = arr[i] ;
        }
    }
    return max ;
}

template <class T>
void swap(T *a, T *b) {
    T temp = *a ;
    *a = *b ;
    *b = temp ;
}

template <class T>
void display(T *arr, int high, int low) {
    for(int i = low; i <= high; i++) {
        std::cout << arr[i] << " " ;
    }
    std::cout << std::endl ;
}

int main() {
    char arr[] = {'2', '4', '6', '8', '1', '0', '2', '3', '4', '7', '6', '5', '9'} ;
    int high = 12, low = 4 , order = 1 ;
    mergeSort(arr, high, low, order) ;
    display(arr, high) ;
    return 0 ;
}

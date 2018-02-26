/**
 * Title:  Algorithm Efficiency and Sorting
 * Author: Seda Gulkesen
 * ID: 21302403
 * Section: 01
 * Assignment: 1
 * Description: In this assignment, insertion sort, merge sort
 * and quick sort algorithms are implemented. Our aim is to show
 * how different algorithms have different time complexities which
 * affect their efficiency. In addition, how the size of taken array
 * and array type (ascending, descending, random) affect the time
 * complexities are examined.
 */

#include <iostream>
#include "ctime"
#include <stdlib.h>
#include "sorting.h"
using namespace std;


//helper functions
void helperMergeSort(int *arr, int first, int last,int &compCount, int &moveCount);
void merge (int *arr,int first,int mid,int last,int &compCount, int &moveCount);
void helperQuickSort(int *arr,int first, int last, int &compCount, int &moveCount);
void partition( int *arr, int first, int last, int &pIndex, int &compCount, int &moveCount);
void performanceAnalysis();

void insertionSort(int *arr, int size, int &compCount, int &moveCount)
{
    for(int unsorted=1;unsorted<size;++unsorted)
    {
        int nextItem=arr[unsorted];
        int loc=unsorted;
        bool cond=true;
        moveCount++;
        while(cond && (loc>0))
        {
            compCount++;

            if((arr[loc-1] > nextItem))
            {
                arr[loc]=arr[loc-1];
                loc--;
                moveCount++;
            }
            else
            {
                cond=false;
                arr[loc]=nextItem;
            }
        }
        moveCount++;
    }
}
//Merge Sort
void mergeSort(int *arr, int size, int &compCount, int &moveCount)
{

    helperMergeSort(arr, 0, size-1, compCount,moveCount);

}

void helperMergeSort(int *arr, int first, int last,int &compCount, int &moveCount)
{
    if(first<last)
    {
        int mid=first+(last-first)/2;

        helperMergeSort(arr,first,mid,compCount,moveCount);
        helperMergeSort(arr,mid+1,last,compCount,moveCount);
        merge(arr,first,mid,last,compCount,moveCount);
    }
}

void merge( int *arr, int first, int mid, int last, int &compCount, int &moveCount)
{
    //creating temporary arrays
    int size=last-first+1;
    int* temp= new int[size];
    //divide into halves
    int first1 = first;
    int last1 = mid;
    int first2 = mid+1;
    int last2 = last;

    int index = 0;
    while((first1 <= last1)&&(first2 <= last2))
    {
        if(arr[first1] < arr[first2])
        {
            temp[index] = arr[first1];
            first1++;
        }
        else
        {
            temp[index] = arr[first2];
            first2++;
        }
        moveCount++;
        compCount++;
        index++;
    }

    //when it's done, first array it placed
    while(first1<=last1)
    {
        temp[index] = arr[first1];
        moveCount++;
        index++;
        first1++;
    }

    //if not, same procedure for second array
    while(first2<=last2)
    {
        temp[index] = arr[first2];
        moveCount++;
        first2++;
        index++;
    }
    for(int i = 0; i <= last-first; i++)
    {

        arr[first+i] = temp[i]; //back to original array
        moveCount++;
    }
    delete [] temp;
}

//QUICKSORT FUNCTIONS
void quickSort( int *arr, int size, int &compCount, int &moveCount)
{
    helperQuickSort(arr, 0, size-1, compCount, moveCount);
}

void helperQuickSort(int *arr, int first, int last, int &compCount, int &moveCount)
{

    int pIndex;

    if(first < last)
    {
        partition(arr, first, last, pIndex, compCount, moveCount);
        helperQuickSort(arr,first, pIndex-1, compCount, moveCount);
        helperQuickSort(arr, pIndex+1, last, compCount, moveCount);
    }
}

void partition( int *arr, int first, int last, int &pIndex, int &compCount, int &moveCount)
{

    int pivot = arr[last];
    arr[last]=arr[first];
    arr[first]=pivot;
    moveCount+=3;

    int lastS1 = first;
    int firstUnknown = first + 1;

    for (  ; firstUnknown <= last; ++firstUnknown)
    {
        if (arr[firstUnknown] < pivot)
        {
            ++lastS1;
            swap(arr[firstUnknown], arr[lastS1]);
            moveCount+=3;
        }
        compCount++;
    }
    swap(arr[first], arr[lastS1]);
    pIndex = lastS1;
    moveCount+=3;
}

void performanceAnalysis()
{

    const int arrSize=1000;
    int index=0;
    int arrInsertion[arrSize];
    int arrMerge[arrSize];
    int arrQuick[arrSize];


    cout<<"Part b1 - Performance analysis of random integers array"<<endl;
    cout<<"\n-----------------------------------------------------------"<<endl;
    srand(time(NULL));

    for(int i=0;i<arrSize;i++)
    {

        arrInsertion[i]=rand()%100;
        arrMerge[i]=arrInsertion[i];
        arrQuick[i]=arrMerge[i];

    }


//    //ascending order
//    cout<<"Part b1 - Performance analysis of ascending ordered array"<<endl;
//    cout<<"\n-----------------------------------------------------------"<<endl;
//    while(index<arrSize)
//    {
//        arrInsertion[index]=index;
//        arrMerge[index]=index;
//        arrQuick[index]=index;
//        index++;
//    }


//    //descending order
//   cout<<"Part b1 - Performance analysis of descending ordered array"<<endl;
//    cout<<"\n-----------------------------------------------------------"<<endl;
//    while (index<arrSize)
//    {
//        for(int j=arrSize-1;j>=0;j--)
//        {
//            arrInsertion[index] = j;
//            arrMerge[index] = j;
//            arrQuick[index] = j;
//            index++;
//        }
//    }

    //display for 1000
    int moveCount1=0,compCount1=0,moveCount2=0,compCount2=0,moveCount3=0,compCount3=0;
    double duration1,duration2,duration3;


    clock_t startTime = clock();
    //call for insertion sort
    insertionSort(arrInsertion,arrSize,compCount1,moveCount1);
    duration1 = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    startTime = clock();
    //call for merge sort
    mergeSort(arrMerge,arrSize,compCount2,moveCount2);
    duration2 = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;


    startTime = clock();
    //call for quick sort
    quickSort(arrQuick,arrSize,compCount3,moveCount3);
    duration3 = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;


    //output wil be diplayed

    cout<<"\t\t\t\t\tElapsed Time\tcompCount\tmoveCount"<<endl;
    cout<<"Array Size: "<<arrSize<<endl;
    cout<<"Insertion Sort\t\t"<<duration1<<"\t\t\t "<<compCount1<<" \t\t\t"<<moveCount1;
    cout<<"\nMerge Sort\t\t\t"<<duration2<<"\t\t\t "<<compCount2<<" \t\t\t"<<moveCount2;
    cout<<"\nQuick Sort\t\t\t"<<duration3<<"\t\t\t "<<compCount3<<" \t\t"<<moveCount3;
    cout<<"\n-----------------------------------------------------------"<<endl;


}


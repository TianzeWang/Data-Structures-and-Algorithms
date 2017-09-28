//
//  main.cpp
//  runtime_study
//
//  Created by 季星佑 on 2017/9/23.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cassert>

using namespace std;

void bubble_sort(int arr[],int lines);

void insertion_sort(int arr[],int lines);

void selection_sort(int arr[],int lines);

void merge(int *C,int *A,int len_A,int *B,int len_B,int lines);

void merge_sort(int arr[],int lines);

int quick_sort_partition_extra(int arr[],int left,int right,int lines);

void quick_sort_extra(int arr[],int left,int right,int size);

int quick_sort_partition_in_place(int arr[],int left,int right,int lines,int pivotat);

void quick_sort_in_place(int arr[],int left,int right,int size);
//////////////////////////////
//////////////////////////////
int main(int argc, const char * argv[])
{
    int lines=50000;
    long temp0=0;
    long temp1=0;
    long temp2=0;
    long temp3=0;
    long temp4=0;
    long temp5=0;
    clock_t start,finish;
    cout<<"lines = "<<lines<<endl;
    int arr[lines];
    for(int i=0;i<lines;++i)
    {
        arr[i]=mrand48();
    }
    int brr[lines];
    for(int j=0;j<lines;++j)
    {
        brr[j]=arr[j];
    }
    int k=0;
    while(k<10)
    {
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        bubble_sort(arr,lines);
        finish=clock();
        long t0=finish-start;
        temp0+=t0;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        insertion_sort(arr,lines);
        finish=clock();
        long t1=finish-start;
        temp1+=t1;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        selection_sort(arr,lines);
        finish=clock();
        long t2=finish-start;
        temp2+=t2;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        merge_sort(arr,lines);
        finish=clock();
        long t3=finish-start;
        temp3+=t3;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        quick_sort_extra(arr,0,lines-1,lines);
        finish=clock();
        long t4=finish-start;
        temp4+=t4;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        quick_sort_in_place(arr,0,lines-1,lines);
        finish=clock();
        long t5=finish-start;
        temp5+=t5;
        //////////////////////////////
        k++;
    }
    long time0=temp0/10;
    long time1=temp1/10;
    long time2=temp2/10;
    long time3=temp3/10;
    long time4=temp4/10;
    long time5=temp5/10;
    cout<<time0<<endl;
    cout<<time1<<endl;
    cout<<time2<<endl;
    cout<<time3<<endl;
    cout<<time4<<endl;
    cout<<time5<<endl;
    return 0;
}
//////////////////////////////
//////////////////////////////
void bubble_sort(int *arr,int lines)
{
    for(int i=lines-1;i>0;--i)
    {
        for(int j=0;j<i;++j)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
//////////////////////////////
//////////////////////////////
void insertion_sort(int *arr,int lines)
{
    for(int i=0;i<=lines-1;++i)
    {
        int temp=arr[i];
        int j=i;
        while(j>=1)
        {
            if(arr[j-1]>temp)
            {
                arr[j]=arr[j-1];
                --j;
            }
            else
            {
                break;
            }
        }
        arr[j]=temp;
    }
}
//////////////////////////////
//////////////////////////////
void selection_sort(int *arr,int lines)
{
    for(int i=0;i<lines-1;++i)
    {
        int index=i;
        for(int j=i+1;j<lines;++j)
        {
            if(arr[j]<arr[index])
            {
                index=j;
            }
        }
        if(index!=i)
        {
            int tmp=arr[index];
            arr[index]=arr[i];
            arr[i]=tmp;
        }
    }
}
//////////////////////////////
//////////////////////////////
void merge(int *C,int *A,int len_A,int *B,int len_B,int lines)
{
    int i=0,j=0,k=0;
    while(i<len_A&&j<len_B)
    {
        if(A[i]<B[j])
        {
            C[k++]=A[i++];
        }
        else
        {
            C[k++]=B[j++];
        }
    }
    while(i<len_A)
    {
        C[k++]=A[i++];
    }
    while(j<len_B)
    {
        C[k++]=B[j++];
    }
}

void merge_sort(int *arr,int lines)
{
    if(lines<=1)
    {
        return;
    }
    int mid=lines/2;
    int *A=new int[mid];
    int *B=new int[lines-mid];
    for(int i=0;i<mid;++i)
    {
        A[i]=arr[i];
    }
    for(int i=mid;i<lines;++i)
    {
        B[i-mid]=arr[i];
    }
    merge_sort(A,mid);
    merge_sort(B,lines-mid);
    merge(arr,A,mid,B,lines-mid,lines);
    delete [] A;
    delete [] B;
}
//////////////////////////////
//////////////////////////////
int quick_sort_partition_extra(int *arr,int left,int right,int lines)
{
    int *temp=new int[lines];
    int l=0;
    int r=lines-1;
    for(int k=1;k<lines;++k)
    {
        if(arr[k]<arr[0])
        {
            temp[l]=arr[k];
            l++;
        }
        else
        {
            temp[r]=arr[k];
            r--;
        }
    }
    temp[l]=arr[0];
    for(int t=0;t<lines;++t)
    {
        arr[t]=temp[t];
    }
    delete [] temp;
    return l;
}

void quick_sort_extra(int *arr,int left,int right,int size)
{
    int pivotat;
    if(left>=right)
    {
        return;
    }
    pivotat=quick_sort_partition_extra(arr,left,right,size);
    quick_sort_extra(arr,left,pivotat-1,pivotat-left);
    quick_sort_extra(arr+pivotat+1,0,right-pivotat-1,right-pivotat);
}
//////////////////////////////
//////////////////////////////
int quick_sort_partition_in_place(int *arr,int left,int right,int lines,int pivotat)
{
    swap(arr[0],arr[pivotat]);
    int i=1;
    int j=lines-1;
    while(true)
    {
        while(i<lines-1&&arr[i]<arr[0])
        {
            ++i;
        }
        while(j>0&&arr[j]>=arr[0])
        {
            --j;
        }
        if(i<j)
        {
            swap(arr[i],arr[j]);
        }
        else
        {
            break;
        }
    }
    swap(arr[0],arr[j]);
    return j;
}

void quick_sort_in_place(int *arr,int left,int right,int size)
{
    if(size==0)
    {
        return;
    }
    int pivotat=rand()%size;
    if(left>=right)
    {
        return;
    }
    pivotat=quick_sort_partition_in_place(arr,left,right,size,pivotat);
    quick_sort_in_place(arr,left,pivotat-1,pivotat-left);
    quick_sort_in_place(arr+pivotat+1,0,right-pivotat-1,right-pivotat);
}

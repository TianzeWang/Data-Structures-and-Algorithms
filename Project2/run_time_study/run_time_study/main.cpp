//
//  main.cpp
//  run_time_study
//
//  Created by 季星佑 on 2017/10/9.
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

int Rselect(int *arr,int n,int i);

int Dselect(int *arr,int n,int i);

int partition(int *arr,int left,int right,int size,int pivotat);

void selection_sort(int *arr,int n);

void quick_sort_in_place(int *arr,int left,int right,int size);
//////////////////////////////
//////////////////////////////
int main(int argc, const char * argv[])
{
    int lines=1000000;
    srand(time(0));
    int t=10;
    long temp0=0;
    long temp1=0;
    long temp2=0;
    long time0=0;
    long time1=0;
    long time2=0;
    clock_t start,finish;
    int arr[lines];
    for(int i=0;i<lines;++i)
    {
        arr[i]=rand();
    }
    int brr[lines];
    for(int j=0;j<lines;++j)
    {
        brr[j]=arr[j];
    }
    //////////////////////////////
    while(t--)
    {
        int index=rand()%lines;
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        quick_sort_in_place(arr,0,lines-1,lines);
        int p=arr[index];
        finish=clock();
        long t0=finish-start;
        temp0+=t0;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        Rselect(arr,lines,index);
        finish=clock();
        long t1=finish-start;
        temp1+=t1;
        //////////////////////////////
        start=clock();
        for(int a=0;a<lines;++a)
        {
            arr[a]=brr[a];
        }
        Dselect(arr,lines,index);
        finish=clock();
        long t2=finish-start;
        temp2+=t2;
        //////////////////////////////
        time0+=temp0/1;
        time1+=temp1/1;
        time2+=temp2/1;
    }
    cout<<time0/10<<endl;
    cout<<time1/10<<endl;
    cout<<time2/10<<endl;
    return 0;
}
//////////////////////////////
//////////////////////////////
int Rselect(int *arr,int n,int i)
{
    if(n==1)
    {
        return *arr;
    }
    int pivotat=rand()%n;
    pivotat=partition(arr,0,n-1,n,pivotat);
    if(pivotat==i)
    {
        return arr[pivotat];
    }
    else if(pivotat>i)
    {
        return Rselect(arr,pivotat,i);
    }
    else
    {
        return Rselect(arr+pivotat+1,n-pivotat-1,i-pivotat-1);
    }
}
//////////////////////////////
//////////////////////////////
int Dselect(int *arr,int n,int i)
{
    if(n<=1)
    {
        return *arr;
    }
    int group_num=n/5;
    int last=n%5;
    if(last==0)
    {
        last=5;
    }
    else
    {
        group_num++;
    }
    int *C=new int[group_num];
    int *temp=new int[5];
    int size=0;
    for(int p=0;p<group_num;++p)
    {
        if(p==group_num-1)
        {
            size=last;
        }
        else
        {
            size=5;
        }
        for(int q=0;q<size;++q)
        {
            temp[q]=arr[q+5*p];
        }
        selection_sort(temp,size);
        C[p]=temp[size/2];
    }
    int pivot=Dselect(C,n/5,n/10);
    delete [] C;
    delete [] temp;
    int pivotat=0;
    for(int p=0;p<n;++p)
    {
        if(arr[p]==pivot)
        {
            pivotat=p;
        }
    }
    pivotat=partition(arr,0,n-1,n,pivotat);
    if(pivotat==i)
    {
        return arr[pivotat];
    }
    else if(pivotat>i)
    {
        return Dselect(arr,pivotat,i);
    }
    else
    {
        return Dselect(arr+pivotat+1,n-pivotat-1,i-pivotat-1);
    }
}
//////////////////////////////
//////////////////////////////
int partition(int *arr,int left,int right,int size,int pivotat)
{
    swap(arr[0],arr[pivotat]);
    int i=1;
    int j=size-1;
    while(true)
    {
        while(i<size-1&&arr[i]<arr[0])
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
//////////////////////////////
//////////////////////////////
void selection_sort(int *arr,int n)
{
    for(int i=0;i<n-1;++i)
    {
        int index=i;
        for(int j=i+1;j<n;++j)
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
    pivotat=partition(arr,left,right,size,pivotat);
    quick_sort_in_place(arr,left,pivotat-1,pivotat-left);
    quick_sort_in_place(arr+pivotat+1,0,right-pivotat-1,right-pivotat);
}

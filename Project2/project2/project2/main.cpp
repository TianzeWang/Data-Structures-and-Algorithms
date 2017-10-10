//
//  main.cpp
//  project2
//
//  Created by 季星佑 on 2017/9/27.
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
//////////////////////////////
//////////////////////////////
int main(int argc, const char * argv[])
{
    int choice;
    cin>>choice;
    int n;
    cin>>n;
    if(n==0)
    {
        return 0;
    }
    int i;
    cin>>i;
    if(i>=n||i<0)
    {
        return 0;
    }
    int a[n];
    for(int t=0;t<n;++t)
    {
        cin>>a[t];
    }
    int *arr=a;
    int result=0;
    switch(choice)
    {
        case 0:
            result=Rselect(arr,n,i);
            break;
        case 1:
            result=Dselect(arr,n,i);
        default:
            break;
    }
    cout<<"The order-"<<i<<" item is "<<result<<endl;
//    srand(time(0));
//    int times=100;
//    while(times--)
//    {
//        int size=100;
//        int index=rand()%size;
//        int *arr=new int [size];
//        int brr[size];
//        for(int i=0;i<size;++i)
//        {
//            arr[i]=rand()%size;
//        }
//        for(int i=0;i<size;++i)
//        {
//            brr[i]=arr[i];
//        }
//        sort(arr,arr+size);
//        int p=arr[index];
//        int q=Rselect(brr,size,index);
//        cout<<p-q<<endl;
//        delete [] arr;
//    }
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

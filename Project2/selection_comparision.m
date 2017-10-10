clear all;clc;
t0=[1 17 154 923 2053 9853 19602 206184];
t1=[1 4 24 158 355 1243 2004 25104];
t2=[2 16 152 749 1498 6046 11323 100056];
size=[10 100 1000 5000 10000 50000 100000 1000000];
plot(size,t0,'o-',size,t1,'v-',size,t2,'*-');
xlabel('array size');
ylabel('speed^{-1}');
legend('quick\_sort\_in\_place','rselection\_sort','dselection\_sort');
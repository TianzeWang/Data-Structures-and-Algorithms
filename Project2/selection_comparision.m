clear all;clc;
t0=[7 57 983 4701 12018 54800 106287 1180554];
t1=[3 15 191 832 1944 6622 12056 113349];
t2=[9 69 1089 3921 8860 32207 61333 550122];
size=[10 100 1000 5000 10000 50000 100000 1000000];
plot(size,t0,'o-',size,t1,'v-',size,t2,'*-');
xlabel('array size');
ylabel('speed^{-1}');
legend('quick\_sort\_in\_place','rselection\_sort','dselection\_sort');
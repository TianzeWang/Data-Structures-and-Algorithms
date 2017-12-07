#/bin/bash
testNum=21
acNum=0
for i in `seq 0 $(($testNum-1))`; do
    ./main <$i.in >$i.test
    diff $i.test $i.out
    if [ $? = 0 ]; then
        echo "testcase $i: Accepted"
        acNum=$((acNum+1))
    else
        echo "testcase $i: Wrong Answer"
    fi
done

echo "Accepted $acNum/$testNum"
if [ "$acNum" = "$testNum" ]; then
    echo "All test cases accepted"
else
    echo "Some test cases failed, work hard and try again!"
fi 

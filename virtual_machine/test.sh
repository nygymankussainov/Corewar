for (( i=1; i <= 1; i++ ))
do
    ./corewar "-dumps `expr $1 + $i`" $2 $3 $4 $5 > my 
    ./corewar_orig -d `expr $1 + $i` $2 $3 $4 $5 > orig
    diff my orig
done
CHAMPS=$(find ./ch -name '*.cor' | cut -c 3-)
for CHAMP in $CHAMPS
do
	./corewar_original -d $1 $CHAMP > output_original
	./corewar -dump $1 $CHAMP > output
	DIFF=$(diff -a output output_original)
	# if [ "$CHAMP" = "ch/doge.cor" ]
	# then
	# 	exit;
	# fi;
	if [ "$DIFF" ]
	then
		printf "\e[1;31mKO\e[0m "
		cat "$DIFF" >> diff
	else
		printf "\e[1;32mOK\e[0m "
	fi
	echo $CHAMP
done

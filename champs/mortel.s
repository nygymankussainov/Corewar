.comment "asdasdasdasdasdasdasdasd"


.name "asjkndlaksjndsakjldnsalkjdnakajsndaskjndasjkndlaksjndsakjldnsalkjdnakajsndaskjndasjkndlaksjndsakjldnsalkjdnakajsndaskjndasdasdsd"

boost: ld %-12, r2      #asdasd

	sti r1,%:live1,%1
live1:	live %66
	sti r1,%:fork0,%1

	sti r1,%:live,%-4
	ldi %:live,%-2,r6
fork2:	live %66
#	fork %:fork0

master:	live %66
	ld %16777216,r6
#	ldi %:master,%0,r6
	zjmp %:ready

numero1: live %66
	ld %3,r3
#	ldi %:live,%-2,r6
	ld %0,r5

numero2:

tampon:	sti r1,r3,r5
live:	sti r1,r5,r5

ready:	sti r6,r3,%:ecriture

wait:	live %66
	zjmp %:ecriture

ecriture: zjmp %:wait

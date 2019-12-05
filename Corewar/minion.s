.name "Kevin"
.comment "Banana! Ha-ha-ha!"

	xor r9, r9, r9
live:
	st r1, 6
	live %0
ld %66, r2
	zjmp %:live
ld %97, r3
	zjmp %:live
ld %110, r4
	zjmp %:live
ld %97, r5
	zjmp %:live
ld %110, r6
	zjmp %:live
ld %97, r7
	zjmp %:live
ld %33, r8
banana:
	aff r2
	aff r3
	aff r4
	aff r5
	aff r6
	aff r7
	aff r8
	zjmp %:live

all :
	clang -mabi=lp64d -fpass-plugin=`echo build/skeleton/SkeletonPass.*` -O0 tests/$(in) 2> outputs/$(out)
	rm a.out

check :
	FileCheck tests/$(chk) --input-file=outputs/$(out)

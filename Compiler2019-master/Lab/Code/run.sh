make clean
make
for((i=1;i<=4;i++)){
	./parser ../Test/test$i.cmm test$i.s
}

make clean
make
for((i=2;i<=2;i++)){
	./parser ../Test/test$i.cmm test$i.s
}

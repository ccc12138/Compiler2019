make clean
make
for((i=1;i<=13;i++)){
	./parser ../Test/test$i.cmm test$i.s
}

make clean
make
for((i=0;i<=9;i++)){
	./parser ../Test/Advanced/10Lab3Simple.1$i.cmm out$i.ir
}
python ./irsim/irsim.pyc

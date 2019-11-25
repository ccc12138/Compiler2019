make clean
make
for((i=0;i<=7;i++)){
	./parser ../Test/Advanced/8Lab3Hard.$i.cmm out$i.ir
}
python ./irsim/irsim.pyc

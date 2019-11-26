make clean
make
for((i=1;i<=2;i++)){
	./parser ../Test/Normal/C_$i.cmm out$i.ir
}
python ./irsim/irsim.pyc

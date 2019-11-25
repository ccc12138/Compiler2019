make clean
make
for((i=2;i<=2;i++)){
	./parser ../Test/Normal/A_$i.cmm out$i.ir
}
python ./irsim/irsim.pyc

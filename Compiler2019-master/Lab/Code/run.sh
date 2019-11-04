make clean
make
for((i=1;i<=20;i=i+1)){
	echo "---------------TestA $i---------------"
	./parser ../Test/Normal/A_$i.cmm
}
for((i=1;i<=2;i=i+1)){
	echo "---------------TestB $i---------------"
	./parser ../Test/Normal/B_$i.cmm
}
for((i=1;i<=2;i=i+1)){
	echo "---------------TestC $i---------------"
	./parser ../Test/Normal/C_$i.cmm
}
for((i=1;i<=3;i=i+1)){
	echo "---------------TestD $i---------------"
	./parser ../Test/Normal/D_$i.cmm
}
for((i=1;i<=3;i=i+1)){
	echo "---------------TestE $i---------------"
	./parser ../Test/Normal/E_$i.cmm
}
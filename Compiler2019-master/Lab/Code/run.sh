make clean
make

# Book tests
for((i=11;i<=12;i=i+1)){
	echo "---------------Book Tests $i---------------"
	./parser ../Test/BookTest/$i.txt
}

# Normal tests
# for((i=7;i<=7;i=i+1)){
# 	echo "---------------TestA $i---------------"
# 	./parser ../Test/Normal/A_$i.cmm
# }
# for((i=1;i<=2;i=i+1)){
# 	echo "---------------TestB $i---------------"
# 	./parser ../Test/Normal/B_$i.cmm
# }
# for((i=1;i<=2;i=i+1)){
# 	echo "---------------TestC $i---------------"
# 	./parser ../Test/Normal/C_$i.cmm
# }
# for((i=1;i<=3;i=i+1)){
# 	echo "---------------TestD $i---------------"
# 	./parser ../Test/Normal/D_$i.cmm
# }
# for((i=1;i<=3;i=i+1)){
# 	echo "---------------TestE $i---------------"
# 	./parser ../Test/Normal/E_$i.cmm
# }

#Advanced tests
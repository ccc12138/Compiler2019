bison -d syntax.y
flex lexical.l
gcc main.c syntax.tab.c syntaxTree.c syntaxTree.h -lfl -ly -o parser
# g++ main.c syntax.tab.c syntaxTree.cpp syntaxTree.h -lfl -ly -o parser
mv parser ../
cd ../
for((i=1;i<=25;i++)){
	echo "------------Test $i------------"
	./parser ./Test/test$i.cmm
}

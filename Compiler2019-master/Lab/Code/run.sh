bison -d syntax.y
flex lexical.l
gcc main.c syntax.tab.c syntaxTree.c syntaxTree.h -lfl -ly -o parser
# g++ main.c syntax.tab.c syntaxTree.cpp syntaxTree.h -lfl -ly -o parser
mv parser ../
cd ../
echo "------------Test1------------"
./parser ./Test/test1.cmm
echo "------------Test2------------"
./parser ./Test/test2.cmm

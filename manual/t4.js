testobj.a=1;
testobj.a=12;
print("a="+testobj.a);
var a=testobj.a;
delete testobj.a;
testobj.b=2;
testobj.c=3;
for(var i in testobj){
	print(i);
}

// Person.prototype.__defineGetter__("age", function () {
//     return this.getAge();
// });
// 
// Person.prototype.__defineSetter__("age", function (val) {
//     this.setAge(val);
// });

// Person.prototype.__defineGetter__("name", function () {
//     return this.getName();
// });
// 
// Person.prototype.__defineSetter__("name", function (val) {
//     this.setName(val);
// });

var c = new Person();
// c.setName("Franky");
c.age=2;
c.name="test";
print(c.name,c.age);
// var reduction = c.computeReduction();
// print(reduction,c.age,c.name);
// 
// var c1 = new Person();
// 
// var c2 = new Person();
// 
// var c3 = new Person();
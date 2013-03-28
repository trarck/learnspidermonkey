#ifndef PERSON_H_
#define PERSON_H_

#include "jsapi.h"
#include <string>

class Person
{

public:
	
	Person();
	~Person();
	
	int getAge(){return m_age;}
	void setAge(int newAge){m_age=newAge;}
	std::string getName(){return m_name;}
	void setName(std::string newName){m_name=newName;}

private:
	int m_age;
	std::string m_name;
	
};

void wrap_register_Person(JSContext *cx,JSObject *obj);
	
#endif //PERSON_H_
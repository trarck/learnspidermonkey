#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "jsapi.h"
#include <string>

class Customer
{

public:
	int getAge(){return m_age;}
	void setAge(int newAge){m_age=newAge;}
	std::string getName(){return m_name;}
	void setName(std::string newName){m_name=newName;}

private:
	int m_age;
	std::string m_name;
	
};


class JSCustomer
{

public:
	
	JSCustomer():m_pCustomer(NULL)
	{
		
	}
	
	~JSCustomer()
	{
		delete m_pCustomer;
		m_pCustomer=NULL;
	}
	
	static JSClass customerClass;
	
public:
	
	static JSBool JSGetProperty(JSContext *cx, JSHandleObject obj, JSHandleId id, JSMutableHandleValue vp);
	
	static JSBool JSSetProperty(JSContext *cx, JSHandleObject obj, JSHandleId id,JSBool strict, JSMutableHandleValue vp);
	
	static JSBool JSConstructor(JSContext *cx, uint32_t argc,jsval *vp);
	
	static void JSDestructor(JSFreeOp *fop, JSObject *obj);
	
	static JSObject *JSInit(JSContext *cx, JSObject *obj, JSObject *proto);
	
	static JSBool computeReduction(JSContext *cx, uint32_t argc, jsval *vp);
								   
	
protected:
	
	void setCustomer(Customer *customer)
	{
		m_pCustomer=customer;
	}
	
	Customer* getCustomer()
	{
		return m_pCustomer;
	}
	
	static JSPropertySpec customer_properties[];

	enum
	{
		name_prop,
		age_prop
	};
	
	static JSFunctionSpec customer_methods[];
	
private:
	
	Customer *m_pCustomer;
};


#endif //CUSTOMER_H_
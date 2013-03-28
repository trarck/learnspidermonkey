#include "Person.h"

Person::Person()
{
	printf("Person create\n");
	
}

Person::~Person()
{
	printf("Person destroy\n");
	
}

void
wrap_Person_finalize(JSFreeOp *fop,JSObject *obj)
{
	printf("in JSDestructor  \n");
	Person *p=(Person *)JS_GetPrivate(obj);
	delete p;
	p=NULL;
}

JSBool person_getter(JSContext *cx, JSHandleObject obj, JSHandleId id,JSMutableHandleValue vp)
{
	
	printf("get isint:%d %s\n",JSID_IS_INT(id),JS_EncodeString(cx,JSID_TO_STRING(id.get())));
	// jsval rval;
	// JS_IdToValue(cx,id.get(),&rval);
	// printf("get %s\n",JS_EncodeString(cx,JSVAL_TO_STRING(rval)));
	//       
	// JSPropertyDescriptor desc;
	// 
	// JS_GetPropertyDescriptorById(cx,obj,id,JSPROP_ENUMERATE,&desc);
	// 
	// printf("get shortid %d %s\n",desc.shortid,JS_EncodeString(cx,JS_ValueToString(cx,desc.value)));
		
    return JS_TRUE;
}

JSBool person_setter(JSContext *cx, JSHandleObject obj, JSHandleId id, JSBool strict,JSMutableHandleValue vp)
{
	printf("set isint:%d %s\n",JSID_IS_INT(id),JS_EncodeString(cx,JSID_TO_STRING(id.get())));
	// 
	// JSPropertyDescriptor desc;
	// 
	// JS_GetPropertyDescriptorById(cx,obj,id,JSPROP_ENUMERATE,&desc);
	// 
	// 
	// printf("set shortid %d %s\n",desc.shortid,JS_EncodeString(cx,JS_ValueToString(cx,desc.value)));
	
	return JS_TRUE;
}

JSClass personClass={
	"Person",JSCLASS_HAS_PRIVATE ,//|JSCLASS_HAS_RESERVED_SLOTS(3),
	JS_PropertyStub,JS_PropertyStub,person_getter,person_setter,//JS_PropertyStub, JS_StrictPropertyStub,//person_getter,person_setter,
	JS_EnumerateStub,JS_ResolveStub,
	JS_ConvertStub,wrap_Person_finalize
};

JSBool
wrap_Person_constructor(JSContext *cx,uint32_t argc,jsval *vp)
{
    JSObject *obj = JS_NewObjectForConstructor(cx, &personClass, vp);
    if (!obj)
        return JS_FALSE;
	
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	
	Person *p=new Person();
	JS_SetPrivate(obj,p);
	return JS_TRUE;
}

JSBool 
wrap_Person_setAge(JSContext *cx,uint32_t argc,jsval *vp)
{
    if(argc==1){
		jsval *argv = JS_ARGV(cx, vp);
		int arg0;
		
		if(!JS_ValueToInt32(cx, argv[0], &arg0)){
			return JS_FALSE;
		}
		
		JSObject *obj = JS_THIS_OBJECT(cx, vp);
		Person* p=(Person *)JS_GetPrivate(obj);
		p->setAge(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool 
wrap_Person_getAge(JSContext *cx,uint32_t argc,jsval *vp)
{
    if(argc==0){
		
		JSObject *obj = JS_THIS_OBJECT(cx, vp);
		Person* p=(Person *)JS_GetPrivate(obj);
		int ret=p->getAge();
		jsval jsret=INT_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool 
wrap_Person_setName(JSContext *cx,uint32_t argc,jsval *vp)
{
    if(argc==1){
		jsval *argv = JS_ARGV(cx, vp);
		
		std::string arg0;
		JSString *arg0_tmp=JS_ValueToString(cx, argv[0]);
		
		arg0=JS_EncodeString(cx,arg0_tmp);
		
		JSObject *obj = JS_THIS_OBJECT(cx, vp);
		Person* p=(Person *)JS_GetPrivate(obj);
		p->setName(arg0);
		
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool 
wrap_Person_getName(JSContext *cx,uint32_t argc,jsval *vp)
{
    if(argc==0){
		
		JSObject *obj = JS_THIS_OBJECT(cx, vp);
		Person* p=(Person *)JS_GetPrivate(obj);
		std::string ret=p->getName();
		
		jsval jsret=STRING_TO_JSVAL(JS_NewStringCopyZ(cx,ret.c_str()));
		
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
    }
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool wrap_Person_computeReduction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Person *p = (Person *)JS_GetPrivate(obj);
    if ( p->getAge() < 25 )
		JS_SET_RVAL(cx, vp, INT_TO_JSVAL(10));
    else
        JS_SET_RVAL(cx, vp, INT_TO_JSVAL(5));
    return JS_TRUE;
}

JSBool wrap_Person_property_getter(JSContext *cx, JSHandleObject obj, JSHandleId id,JSMutableHandleValue vp)
{
	
	printf("pget isint:%d\n",JSID_IS_INT(id));
	// jsval rval;
	// JS_IdToValue(cx,id.get(),&rval);
	// printf("get %s\n",JS_EncodeString(cx,JSVAL_TO_STRING(rval)));
	//       
	// JSPropertyDescriptor desc;
	// 
	// JS_GetPropertyDescriptorById(cx,obj,id,JSPROP_ENUMERATE,&desc);
	// 
	// printf("get shortid %d %s\n",desc.shortid,JS_EncodeString(cx,JS_ValueToString(cx,desc.value)));
		
    return JS_TRUE;
}

JSBool wrap_Person_property_setter(JSContext *cx, JSHandleObject obj, JSHandleId id, JSBool strict,JSMutableHandleValue vp)
{
	printf("pset isint:%d\n",JSID_IS_INT(id));
	// printf("set %s\n",JS_EncodeString(cx,JSID_TO_STRING(id.get())));
	// 
	// JSPropertyDescriptor desc;
	// 
	// JS_GetPropertyDescriptorById(cx,obj,id,JSPROP_ENUMERATE,&desc);
	// 
	// 
	// printf("set shortid %d %s\n",desc.shortid,JS_EncodeString(cx,JS_ValueToString(cx,desc.value)));
	
	return JS_TRUE;
}

JSPropertySpec person_properties[]={
	// {"name",1,JSPROP_ENUMERATE},
	{"name",1,JSPROP_ENUMERATE | JSPROP_SHARED,JSOP_WRAPPER(wrap_Person_property_getter),JSOP_WRAPPER(wrap_Person_property_setter)},
	{0}
};

JSFunctionSpec person_methods[] = 
{
	JS_FS( "getAge", wrap_Person_getAge, 0, 0 ),
	JS_FS( "setAge", wrap_Person_setAge, 0, 0 ),
	JS_FS( "getName", wrap_Person_getName, 0, 0 ),
	JS_FS( "setName", wrap_Person_setName, 0, 0 ),
    JS_FS( "computeReduction", wrap_Person_computeReduction, 0, 0 ),
    JS_FS_END
};

void wrap_register_Person(JSContext *cx,JSObject *obj)
{
	JS_InitClass(cx,obj,NULL,&personClass,wrap_Person_constructor,0,person_properties,person_methods,NULL,NULL);
}











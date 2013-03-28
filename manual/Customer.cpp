#include "Customer.h"

JSClass JSCustomer::customerClass={
	
	"Customer",JSCLASS_HAS_PRIVATE,
	JS_PropertyStub,JS_PropertyStub,JSCustomer::JSGetProperty,JSCustomer::JSSetProperty,
	JS_EnumerateStub,JS_ResolveStub,
	JS_ConvertStub,JSCustomer::JSDestructor
};

JSObject* JSCustomer::JSInit(JSContext *cx,JSObject *obj,JSObject *proto)
{
	JSObject* newObj=JS_InitClass(cx,obj,proto,&customerClass,JSCustomer::JSConstructor,0,JSCustomer::customer_properties,JSCustomer::customer_methods,NULL,NULL);
	return newObj;
}

JSBool
JSCustomer::JSConstructor(JSContext *cx,uint32_t argc,jsval *vp)
{
    JSObject *obj = JS_NewObjectForConstructor(cx, &customerClass, vp);
    if (!obj)
        return JS_FALSE;
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
	
	JSCustomer *p=new JSCustomer();
	p->setCustomer(new Customer());
	JS_SetPrivate(obj,p);
	return JS_TRUE;
}

void
JSCustomer::JSDestructor(JSFreeOp *fop,JSObject *obj)
{
	printf("in JSDestructor  \n");
	JSCustomer *p=(JSCustomer *)JS_GetPrivate(obj);
	delete p;
	p=NULL;
}



JSPropertySpec JSCustomer::customer_properties[]={
	{"name",name_prop,JSPROP_ENUMERATE},
	{"age",age_prop,JSPROP_ENUMERATE},
	{0}
};

JSBool JSCustomer::JSGetProperty(JSContext *cx, JSHandleObject obj, JSHandleId id,JSMutableHandleValue vp)
{
	JSString *propName=JSID_TO_STRING(id);
	printf("get %s[%d]\n",JS_EncodeString(cx,propName),JSID_TO_INT(id));
	// if(JSVAL_IS_INT(id)){
		JSCustomer *priv=(JSCustomer*) JS_GetPrivate(obj);
		switch(id){
			case name_prop:
				vp.set(STRING_TO_JSVAL(JS_NewStringCopyZ(cx,priv->getCustomer()->getName().c_str())));
				break;
			case age_prop:
				vp.set(INT_TO_JSVAL(priv->getCustomer()->getAge()));
				break;
		}
	// }
	return JS_TRUE;
}

JSBool JSCustomer::JSSetProperty(JSContext *cx, JSHandleObject obj, JSHandleId id, JSBool strict,JSMutableHandleValue vp)
{
	jsval rval;
	JS_IdToValue(cx,id.get(),&rval);
printf("set %d,%d\n",JSID_TO_INT(id.get()),JSVAL_TO_INT(rval));
        JSCustomer *priv = (JSCustomer *) JS_GetPrivate(obj);
        switch(id)
        {
        case name_prop:
			priv->getCustomer()->setName(JS_EncodeString(cx,JSVAL_TO_STRING(vp.get())));
            break;
        case age_prop:
            priv->getCustomer()->setAge(JSVAL_TO_INT(vp.get()));
            break;
        }

    return JS_TRUE;
}

JSFunctionSpec JSCustomer::customer_methods[] = 
{
    JS_FS( "computeReduction", JSCustomer::computeReduction, 0, 0 ),
    JS_FS_END
};

JSBool JSCustomer::computeReduction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    JSCustomer *p = (JSCustomer *)JS_GetPrivate(obj);
    if ( p->getCustomer()->getAge() < 25 )
		JS_SET_RVAL(cx, vp, INT_TO_JSVAL(10));
    else
        JS_SET_RVAL(cx, vp, INT_TO_JSVAL(5));
    return JS_TRUE;
}
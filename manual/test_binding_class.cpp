/*
 * This define is for Windows only, it is a work-around for bug 661663.
 */
#ifdef _MSC_VER
# define XP_WIN
#endif

#include "jsapi.h"
#include "jsbinding.h"

/* The class of the global object. */
static JSClass global_class = { "global", JSCLASS_GLOBAL_FLAGS, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, NULL, JSCLASS_NO_OPTIONAL_MEMBERS };

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
     fprintf(stderr, "%s:%u:%s\n",
             report->filename ? report->filename : "<no filename="">",
             (unsigned int) report->lineno,
             message);
}

JSBool
addProperty(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
	JSString *propName=JSID_TO_STRING(id);
  printf("in addProperty %s[%ld]=%s\n",JS_EncodeString(cx,propName),JSID_BITS(id.get()),JS_EncodeString(cx,JS_ValueToString(cx,vp.get())));
  return true;
}

JSBool
delProperty(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
  printf("in delProperty %ld=%s\n",JSID_BITS(id.get()),JS_EncodeString(cx,JS_ValueToString(cx,vp.get())));
  return true;
}

JSBool
getProperty(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
  JSString *propName=JSID_TO_STRING(id);
  printf("in getProperty %s[%ld]=%s\n",JS_EncodeString(cx,propName),JSID_BITS(id.get()),JS_EncodeString(cx,JS_ValueToString(cx,vp.get())));
  return true;
}

JSBool
setProperty(JSContext *cx, JSHandleObject obj, JSHandleId id, JSBool strict, JSMutableHandleValue vp)
{
  printf("in setProperty %ld=%s\n",JSID_BITS(id.get()),JS_EncodeString(cx,JS_ValueToString(cx,vp.get())));
  return true;
}

JSBool
my_enumerate(JSContext *cx, JSHandleObject obj)
{
	printf("in enumerate \n");
    return JS_TRUE;
}

JSBool
my_resolve(JSContext *cx, JSHandleObject obj,JSHandleId id)
{
	printf("in resolve \n");
    return JS_TRUE;
}

void
my_finalize(JSFreeOp *fop, JSObject *obj)
{
	printf("in finalize  %d\n",obj);
}

static JSClass testobj_class = { "Test", 0, 
	addProperty, delProperty, getProperty, setProperty, 
	my_enumerate, my_resolve, JS_ConvertStub,my_finalize, JSCLASS_NO_OPTIONAL_MEMBERS 
};

static JSBool
Test(JSContext* cx, unsigned argc, jsval *vp)
{
    JSObject *obj = JS_NewObjectForConstructor(cx, &testobj_class, vp);
    if (!obj)
        return JS_FALSE;
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    return JS_TRUE;
}

static JSBool test_fn(JSContext *cx, unsigned argc, jsval *vp)
{
	printf("test_fun:\n");
    return JS_TRUE;
}

static JSFunctionSpec ptestFunctions[] = {
    JS_FS( "test_fn", test_fn, 0, 0 ),
    JS_FS_END
};

JSBool beforeTest(JSContext *cx)
{
	JSObject *global=JS_GetGlobalObject(cx);

	JS_InitClass(cx,global,NULL,&testobj_class,Test,JSPROP_ENUMERATE|JSFUN_CONSTRUCTOR,NULL,ptestFunctions,NULL,NULL);
	
}



JSBool test(JSContext *cx)
{
	
	jsval propVal;
	
	JSObject *global=JS_GetGlobalObject(cx);
	
	return JS_TRUE;
}

int main(int argc, const char *argv[]) {
    /* JS variables. */
    JSRuntime *rt;
    JSContext *cx;
    JSObject *global;

    /* Create a JS runtime. */
    rt = JS_NewRuntime(8L * 1024L * 1024L,JS_NO_HELPER_THREADS);
    if (rt == NULL)
       return 1;

    /* Create a context. */
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL)
       return 1;
    JS_SetOptions(cx, JSOPTION_VAROBJFIX | JSOPTION_METHODJIT);
    JS_SetVersion(cx, JSVERSION_LATEST);
    JS_SetErrorReporter(cx, reportError);

    /* Create the global object in a new compartment. */
    global = JS_NewGlobalObject(cx, &global_class, NULL);
    if (global == NULL)
       return 1;

    /* Populate the global object with the standard globals, like Object and Array. */
    if (!JS_InitStandardClasses(cx, global))
       return 1;

 
    /* Your application code here. This may include JSAPI calls
     * to create your own custom JavaScript objects and to run scripts.
     *
     * The following example code creates a literal JavaScript script,
     * evaluates it, and prints the result to stdout.
     *
     * Errors are conventionally saved in a JSBool variable named ok.
     */
	
	JS_DefineFunction(cx,global,"print",&js_print,0,0);
	
	// execJsFile(cx,"t.js");
	
	// testObj(cx);
	
	beforeTest(cx);
	execJsFile(cx,"t5.js");
	test(cx);
    
 
    /* End of your application code */
 
    /* Clean things up and shut down SpiderMonkey. */
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    return 0;
}
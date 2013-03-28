/*
 * This define is for Windows only, it is a work-around for bug 661663.
 */
#ifdef _MSC_VER
# define XP_WIN
#endif

#include "jsapi.h"
#include "jsbinding.h"
#include <string>
/* The class of the global object. */
static JSClass global_class = { "global", JSCLASS_GLOBAL_FLAGS, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, NULL, JSCLASS_NO_OPTIONAL_MEMBERS };

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
     fprintf(stderr, "%s:%u:%s\n",
             report->filename ? report->filename : "<no filename="">",
             (unsigned int) report->lineno,
             message);
}

static JSClass testobj_class = { "test", 0, 
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub, 
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, NULL, JSCLASS_NO_OPTIONAL_MEMBERS 
};

JSBool beforeTest(JSContext *cx)
{
	JSObject *x=JS_NewObject(cx,NULL,NULL,NULL);
	if(x==NULL)
		return JS_FALSE;
	
	jsval y;


	if (!JS_GetProperty(cx, x, "myprop", &y)){
		printf("no myprop\n");
		return JS_FALSE;
	}
	printf("myprop=%s\n",JS_EncodeString(cx,JS_ValueToString(cx,y)));
	
	if(!JS_SetProperty(cx,x,"myprop",&INT_TO_JSVAL(24))){
		return JS_FALSE;
	}
	
	if (!JS_GetProperty(cx, x, "myprop", &y)){
		printf("no myprop\n");
		return JS_FALSE;
	}
	printf("myprop=%s\n",JS_EncodeString(cx,JS_ValueToString(cx,y)));
	
	if (!JS_DefineProperty(cx, x, "prop", INT_TO_JSVAL(123),
	                       JS_PropertyStub, JS_StrictPropertyStub,
	                       JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT)) {
	   return JS_FALSE;
	}
	
	if (!JS_GetProperty(cx, x, "prop", &y)){
		printf("no prop\n");
		return JS_FALSE;
	}
	printf("prop=%s\n",JS_EncodeString(cx,JS_ValueToString(cx,y)));
	
	return JS_TRUE;
	
}

JSBool test(JSContext *cx)
{
	
	jsval propVal;
	
	JSObject *global=JS_GetGlobalObject(cx);
	
	if (!JS_GetProperty(cx, global, "myprop", &propVal)){
		printf("no myprop\n");
		return JS_FALSE;
	}
	printf("myprop=%s\n",JS_EncodeString(cx,JS_ValueToString(cx,propVal)));
	
	JSObject *obj;
	
	jsval rval;
	
	if(!JS_GetProperty(cx,global,"obj",&rval)){
		return JS_FALSE;
	}
	obj=JSVAL_TO_OBJECT(rval);
	printf("obj:%s\n",JS_EncodeString(cx,JS_ValueToString(cx,rval)));
	
	// jsval xVal;
	if(!JS_GetProperty(cx,obj,"x",&rval)){
		return JS_FALSE;
	}
	int x=JSVAL_TO_INT(rval);
	printf("x=%d\n",x);
	
	// jsval yVal;
	if(!JS_GetProperty(cx,obj,"y",&rval)){
		return JS_FALSE;
	}
	int y=JSVAL_TO_INT(rval);
	printf("y=%d\n",y);
	
	int yy;
	if(!JS_ValueToInt32(cx,rval,&yy)){
		return JS_FALSE;
	}
	
	printf("yy=%d\n",yy);
	
	
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
	
	std::string file="t2.js";
	
	if(argc>1){
		file=argv[1];
	}
	printf("exec:%s\n",file.c_str());
	
	beforeTest(cx);
	execJsFile(cx,file.c_str());
	test(cx);

  
    /* End of your application code */
 
    /* Clean things up and shut down SpiderMonkey. */
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    return 0;
}
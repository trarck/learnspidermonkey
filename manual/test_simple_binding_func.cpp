/*
 * This define is for Windows only, it is a work-around for bug 661663.
 */
#ifdef _MSC_VER
# define XP_WIN
#endif
 
#include <stdlib.h>
#include <time.h>
/* Include the JSAPI header file to get access to SpiderMonkey. */
#include <jsapi.h>
 
/* The class of the global object. */
static JSClass global_class = { "global", JSCLASS_GLOBAL_FLAGS, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, NULL, JSCLASS_NO_OPTIONAL_MEMBERS };

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
     fprintf(stderr, "%s:%u:%s\n",
             report->filename ? report->filename : "<no filename="">",
             (unsigned int) report->lineno,
             message);
}


JSBool myjs_rand(JSContext *cx,uint32_t argc,jsval *vp)
{
	JS_SET_RVAL(cx,vp,DOUBLE_TO_JSVAL(rand()));
	return JS_TRUE;
}

JSBool myjs_srand(JSContext *cx,uint32_t argc,jsval *vp)
{
	uint32_t seed;
	if(!JS_ConvertArguments(cx,argc,JS_ARGV(cx,vp),"/u",&seed));
		return JS_FALSE;
	if(argc==0) 
		seed=time(NULL);
	srand(seed);
	JS_SET_RVAL(cx,vp,JSVAL_VOID);
	return JS_TRUE;	
}

JSBool myjs_system(JSContext *cx,uint32_t argc,jsval* vp)
{
	JSString* str;
	char* cmd;
	int rc;
	if (!JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &str))
	        return JS_FALSE;
	cmd=JS_EncodeString(cx,str);
	rc=system(cmd);
	JS_free(cx,cmd);
	if(rc!=0){
		JS_ReportError(cx,"Command failed with exit code %d",rc);
		return JS_FALSE;
	}
	JS_SET_RVAL(cx,vp,JSVAL_VOID);
	return JS_TRUE;
} 


int main(int argc, const char *argv[])
{
	static JSFunctionSpec myjs_global_functions[]={
		JS_FS("rand",myjs_rand,0,0),
		JS_FS("srand",myjs_srand,0,0),
		JS_FS("system",myjs_system,0,0),
		JS_FS_END
	};
	
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
    
	
	if(!JS_DefineFunctions(cx,global,myjs_global_functions))
		return JS_FALSE;
 
    /* Your application code here. This may include JSAPI calls
     * to create your own custom JavaScript objects and to run scripts.
     *
     * The following example code creates a literal JavaScript script,
     * evaluates it, and prints the result to stdout.
     *
     * Errors are conventionally saved in a JSBool variable named ok.
     */
    char *script = "var a=ss;";
    jsval rval;
    JSString *str;
    JSBool ok;
    const char *filename = "noname";
    uint32_t lineno = 0;
 
    ok = JS_EvaluateScript(cx, global, script, strlen(script),
                           filename, lineno, &rval);
    if (!ok)
        return 1;
 
    str = JS_ValueToString(cx, rval);
    printf("%s\n", JS_EncodeString(cx, str));
 
    /* End of your application code */
 
    /* Clean things up and shut down SpiderMonkey. */
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    return 0;
}
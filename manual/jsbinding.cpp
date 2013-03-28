#include "jsbinding.h"

JSBool js_print(JSContext *cx,uint32_t argc,jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	
    JSString *jss; 
    for(int i = 0; i < argc; ++i){ 
       jss = JS_ValueToString(cx, argv[i]); 
       printf("js: %s\n",JS_EncodeString(cx,jss)); 
    }
    return JS_TRUE; 
}

JSBool execJsFile(JSContext* cx,const char* path)
{
	JSObject* global=JS_GetGlobalObject(cx);
	
    js::RootedObject obj(cx, global);
	JS::CompileOptions options(cx);
	options.setUTF8(true).setFileAndLine(path, 1);
	JSScript *script = JS::Compile(cx, obj, options, path);

    JSBool evaluatedOK = false;
    if (script) {
        jsval rval;
        JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (JS_FALSE == evaluatedOK) {
            JS_ReportPendingException(cx);
        }
    }
    return evaluatedOK;
}
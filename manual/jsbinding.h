#ifndef JSBINDING_BASE_H_
#define JSBINDING_BASE_H_

#include "jsapi.h"

JSBool js_print(JSContext *cx,uint32_t argc,jsval *argv);

JSBool execJsFile(JSContext* cx,const char* file);

#endif //JSBINDING_BASE_H_
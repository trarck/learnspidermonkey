1.关于js的binding方式。
  一种是面向对象式的：建立一个Binding对象，需要传送给JS_InitClass的参数使用类的静态变量，对应的方法使用类的静态方法。FireFox,nodejs(虽然使用V8，但原理差不多)
  一种是面向过程式的:直接定义传送给JS_InitClass的参数和处理方法。cocos2dx目前的做法。
  由此可见，c++中嵌入spidermonkey,使用面向对象式比较通常。
ROSS_COMPILE_PREFIX =
CROSS_COMPILE_PATH   =
CFLAGS  = -I/usr/local/include/js/
LDFLAGS = -L/usr/local/lib
# LIBS = -lmozjs185-1.0
LIBS = -ljs_static -lz
DFLAGS  =
CC =  $(CROSS_COMPILE_PREFIX)g++ 
#$(DFLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS)
# CLINK  = -c -o
RM  = rm -f

TARGET=
DEPENDENCY=
DIST=dist


# CFILES = test.cpp
# OBJ  = $(patsubst %.c,%.o, $(CFILES))
# EXECUTABLE = $(patsubst %.c,%, $(CFILES))
# DEPENDENCY = $(patsubst %.c,%.d, $(CFILES))
# all: $(DEPENDENCY) $(EXECUTABLE)
# %: %.o
#         $(CC) $< $(LIBS) -o $@ $(LDFLAGS)
# %.o: %.c
#         $(CC) -c $< -o$@ $(CFLAGS)
# %.d: %.c
#         $(CC) -MM $(CFLAGS) $< >$@.$$$$;\
#         sed 's,\($*\)\.o:,\1.o $@:,g' < $@.$$$$ > $@;\
#         $(RM) $@.$$$$;
# clean:
# 	$(RM) $(EXECUTABLE) *.o *.bak *.c~ *.h~ *.d

mkdist:
	mkdir $(DIST)

clean:
	rm -r $(DIST)/*

$(DIST)/%.o :%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c  $< -o $@

build:$(DEPENDENCY) $(TARGET).o
	$(CC) $(LIBS) $(LDFLAGS) $(TARGET).o $(DEPENDENCY) -o $(TARGET) 

run:build
	./$(TARGET)

test_hello:
	$(MAKE) run TARGET=$(DIST)/hello

test_simple_binding_func:
	$(MAKE) run TARGET=$(DIST)/simple_binding_func

test_execfile:
	$(MAKE) run TARGET=$(DIST)/execfile DEPENDENCY=$(DIST)/jsbinding.o

test_native:
	$(MAKE) run TARGET=$(DIST)/test_native DEPENDENCY=$(DIST)/jsbinding.o
	
test_binding_object:
	$(MAKE) run TARGET=$(DIST)/test_binding_object DEPENDENCY=$(DIST)/jsbinding.o

test_binding_class:
	$(MAKE) run TARGET=$(DIST)/test_binding_class DEPENDENCY=$(DIST)/jsbinding.o

test_binding_class_oo_wrap:
	$(MAKE) run TARGET=$(DIST)/test_binding_class_oo_wrap DEPENDENCY="$(DIST)/jsbinding.o $(DIST)/Customer.o"
	
test_binding_class_po_wrap:
	$(MAKE) run TARGET=$(DIST)/test_binding_class_po_wrap DEPENDENCY="$(DIST)/jsbinding.o $(DIST)/Person.o"

.PHONY: test_hello test_simple_binding_func test_execfile test_native test_binding_object
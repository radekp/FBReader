include $(ROOTDIR)/makefiles/config.mk

INCLUDE = $(ZINCLUDE) $(EXTERNALINCLUDE) $(GTKINCLUDE)

HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

DEPFILE = .depend

.dep:
	@echo -n "Calculating dependencies ..."
	@if [ "$(SOURCES)" != "" ]; then \
		$(DEPGEN) $(INCLUDE) $(SOURCES) >> $(DEPFILE); \
	fi;
	@echo " OK"

.SUFFIXES: .cpp .o .h

.cpp.o:
	@echo -n "Compiling $@ ..."
	@$(CC) -c $(CFLAGS) $(INCLUDE) $<
	@echo " OK"

all: .dep $(OBJECTS)

clean:
	@$(RM) $(DEPFILE) *.o

ifneq "$(wildcard $(DEPFILE))" ""
  include $(DEPFILE)
endif

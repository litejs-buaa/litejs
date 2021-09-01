#
# QuickJS Javascript Engine
# 
# Copyright (c) 2017-2021 Fabrice Bellard
# Copyright (c) 2017-2021 Charlie Gordon
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

CONFIG_LTO=y
CFLAGS_CUSTOM=-O2 #-Werror
prefix=/mnt/e/WSL_Ubuntu/qjsreplica/output
CONFIG_BIGNUM=y
#BUILD_EXAMPLES=y
#BUILD_TESTS=y

OBJDIR=.obj

CFLAGS=-g -Wall -Wno-array-bounds -Wno-format-truncation -MMD -MF $(OBJDIR)/$(@F).d
CFLAGS+=$(CFLAGS_CUSTOM)
ifdef CONFIG_LTO
    AR=gcc-ar
else
    AR=ar
endif
DEFINES:=-D_GNU_SOURCE -DCONFIG_VERSION=\"$(shell cat VERSION)\"
ifdef CONFIG_BIGNUM
DEFINES+=-DCONFIG_BIGNUM
endif
CFLAGS+=$(DEFINES)
CFLAGS_NOLTO:=$(CFLAGS)
LDFLAGS=-g
ifdef CONFIG_LTO
CFLAGS+=-flto
LDFLAGS+=-flto
endif

PROGS=qjsc qjscalc libquickjs.a
ifdef CONFIG_LTO
PROGS+=libquickjs.lto.a
endif
PROGS+=qjs
endif

NEWDIR=$(OBJDIR)
ifdef BUILD_TESTS
NEWDIR+=$(OBJDIR)/tests
PROGS+=test
endif
ifdef BUILD_EXAMPLES
NEWDIR+=$(OBJDIR)/examples
PROGS+=examples/hello examples/hello_module examples/test_fib examples/fib.so examples/point.so
endif

QJS_LIB_OBJS=$(OBJDIR)/quickjs.o $(OBJDIR)/libregexp.o $(OBJDIR)/libunicode.o $(OBJDIR)/cutils.o $(OBJDIR)/quickjs-libc.o
QJS_OBJS=$(OBJDIR)/qjs.o $(OBJDIR)/repl.o $(QJS_LIB_OBJS)
ifdef CONFIG_BIGNUM
QJS_LIB_OBJS+=$(OBJDIR)/libbf.o 
QJS_OBJS+=$(OBJDIR)/qjscalc.o
endif

all: $(OBJDIR) $(OBJDIR)/quickjs.check.o $(OBJDIR)/qjs.check.o $(PROGS)

$(OBJDIR):
	mkdir -p $(NEWDIR)

qjs: $(QJS_OBJS)
	gcc $(LDFLAGS) -rdynamic -o $@ $^ -lm -ldl -lpthread

qjsc: $(OBJDIR)/qjsc.o $(QJS_LIB_OBJS)
	gcc $(LDFLAGS) -o $@ $^ -lm -ldl -lpthread

QJSC_DEFINES:=-DCONFIG_CC=\"gcc\" -DCONFIG_PREFIX=\"$(prefix)\"
ifdef CONFIG_LTO
QJSC_DEFINES+=-DCONFIG_LTO
endif
QJSC_HOST_DEFINES:=-DCONFIG_CC=\"gcc\" -DCONFIG_PREFIX=\"$(prefix)\"

$(OBJDIR)/qjsc.o: CFLAGS+=$(QJSC_DEFINES)
$(OBJDIR)/qjsc.host.o: CFLAGS+=$(QJSC_HOST_DEFINES)

qjscalc: qjs
	ln -sf $< $@

ifdef CONFIG_LTO
LTOEXT=.lto
else
LTOEXT=
endif

libquickjs$(LTOEXT).a: $(QJS_LIB_OBJS)
	$(AR) rcs $@ $^

ifdef CONFIG_LTO
libquickjs.a: $(patsubst %.o, %.nolto.o, $(QJS_LIB_OBJS))
	$(AR) rcs $@ $^
endif # CONFIG_LTO

repl.c: ./qjsc repl.js
	./qjsc -c -o $@ -m repl.js

qjscalc.c: ./qjsc qjscalc.js
	./qjsc -fbignum -c -o $@ qjscalc.js

ifneq ($(wildcard unicode/UnicodeData.txt),)
$(OBJDIR)/libunicode.o $(OBJDIR)/libunicode.m32.o $(OBJDIR)/libunicode.m32s.o \
    $(OBJDIR)/libunicode.nolto.o: libunicode-table.h

libunicode-table.h: unicode_gen
	./unicode_gen unicode $@
endif

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	gcc $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.host.o: %.c | $(OBJDIR)
	gcc $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.pic.o: %.c | $(OBJDIR)
	gcc $(CFLAGS) -fPIC -DJS_SHARED_LIBRARY -c -o $@ $<

$(OBJDIR)/%.nolto.o: %.c | $(OBJDIR)
	gcc $(CFLAGS_NOLTO) -c -o $@ $<

$(OBJDIR)/%.check.o: %.c | $(OBJDIR)
	gcc $(CFLAGS) -DCONFIG_CHECK_JSVALUE -c -o $@ $<

regexp_test: libregexp.c libunicode.c cutils.c
	gcc $(LDFLAGS) $(CFLAGS) -DTEST -o $@ libregexp.c libunicode.c cutils.c -lm -ldl -lpthread

unicode_gen: $(OBJDIR)/unicode_gen.host.o $(OBJDIR)/cutils.host.o libunicode.c unicode_gen_def.h
	gcc $(LDFLAGS) $(CFLAGS) -o $@ $(OBJDIR)/unicode_gen.host.o $(OBJDIR)/cutils.host.o

run-test262: $(OBJDIR)/run-test262.o $(QJS_LIB_OBJS)
	gcc $(LDFLAGS) -o $@ $^ -lm -ldl -lpthread

clean:
	-rm -f repl.c qjscalc.c out.c
	-rm -f *.a *.o *.d *~ unicode_gen regexp_test $(PROGS)
	-rm -f hello.c test_fib.c
	-rm -f examples/*.so tests/*.so
	-rm -rf $(OBJDIR)/ *.dSYM/

install: all
	mkdir -p "$(DESTDIR)$(prefix)/bin"
	strip qjs qjsc
	install -m755 qjs qjsc "$(DESTDIR)$(prefix)/bin"
	ln -sf qjs "$(DESTDIR)$(prefix)/bin/qjscalc"
	mkdir -p "$(DESTDIR)$(prefix)/lib/quickjs"
	install -m644 libquickjs.a "$(DESTDIR)$(prefix)/lib/quickjs"
ifdef CONFIG_LTO
	install -m644 libquickjs.lto.a "$(DESTDIR)$(prefix)/lib/quickjs"
endif
	mkdir -p "$(DESTDIR)$(prefix)/include/quickjs"
	install -m644 quickjs.h quickjs-libc.h "$(DESTDIR)$(prefix)/include/quickjs"

###############################################################################
# examples

# example of static JS compilation
HELLO_SRCS=examples/hello.js
HELLO_OPTS=-fno-string-normalize -fno-map -fno-promise -fno-typedarray \
           -fno-typedarray -fno-regexp -fno-json -fno-eval -fno-proxy \
           -fno-date -fno-module-loader
ifdef CONFIG_BIGNUM
HELLO_OPTS+=-fno-bigint
endif

hello.c: ./qjsc $(HELLO_SRCS)
	./qjsc -e $(HELLO_OPTS) -o $@ $(HELLO_SRCS)

examples/hello: $(OBJDIR)/hello.o $(QJS_LIB_OBJS)
	gcc $(LDFLAGS) -o $@ $^ -lm -ldl -lpthread

# example of static JS compilation with modules
HELLO_MODULE_SRCS=examples/hello_module.js
HELLO_MODULE_OPTS=-fno-string-normalize -fno-map -fno-promise -fno-typedarray \
           -fno-typedarray -fno-regexp -fno-json -fno-eval -fno-proxy \
           -fno-date -m
examples/hello_module: ./qjsc libquickjs$(LTOEXT).a $(HELLO_MODULE_SRCS)
	./qjsc $(HELLO_MODULE_OPTS) -o $@ $(HELLO_MODULE_SRCS)

# use of an external C module (static compilation)

test_fib.c: ./qjsc examples/test_fib.js
	./qjsc -e -M examples/fib.so,fib -m -o $@ examples/test_fib.js

examples/test_fib: $(OBJDIR)/test_fib.o $(OBJDIR)/examples/fib.o libquickjs$(LTOEXT).a
	gcc $(LDFLAGS) -o $@ $^ -lm -ldl -lpthread

examples/fib.so: $(OBJDIR)/examples/fib.pic.o
	gcc $(LDFLAGS) -shared -o $@ $^

examples/point.so: $(OBJDIR)/examples/point.pic.o
	gcc $(LDFLAGS) -shared -o $@ $^

###############################################################################
# tests

test: qjs
	./qjs tests/test_closure.js
	./qjs tests/test_language.js
	./qjs tests/test_builtin.js
	./qjs tests/test_loop.js
	./qjs tests/test_std.js
	./qjs tests/test_worker.js
ifndef CONFIG_DARWIN
ifdef CONFIG_BIGNUM
	./qjs --bignum tests/test_bjson.js
else
	./qjs tests/test_bjson.js
endif
	./qjs examples/test_point.js
endif
ifdef CONFIG_BIGNUM
	./qjs --bignum tests/test_op_overloading.js
	./qjs --bignum tests/test_bignum.js
	./qjs --qjscalc tests/test_qjscalc.js
endif

microbench: qjs
	./qjs tests/microbench.js

# ES5 tests (obsolete)
test2o: run-test262
	time ./run-test262 -m -c test262o.conf

test2o-update: run-test262
	./run-test262 -u -c test262o.conf

# Test262 tests
test2-default: run-test262
	time ./run-test262 -m -c test262.conf

test2: run-test262
	time ./run-test262 -m -c test262.conf -a

test2-update: run-test262
	./run-test262 -u -c test262.conf -a

test2-check: run-test262
	time ./run-test262 -m -c test262.conf -E -a

testall: all test microbench test2o test2

tests/bjson.so: $(OBJDIR)/tests/bjson.pic.o
	gcc $(LDFLAGS) -shared -o $@ $^ -lm -ldl -lpthread

-include $(wildcard $(OBJDIR)/*.d)

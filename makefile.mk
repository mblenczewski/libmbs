.PHONY: libmbs libmbs-build libmbs-test

LIBMBS_MAJOR		:= 0
LIBMBS_MINOR		:= 1
LIBMBS_PATCH		:= 0
LIBMBS_VERSION		:= $(LIBMBS_MAJOR).$(LIBMBS_MINOR).$(LIBMBS_PATCH)

LIBMBS_CFLAGS		:= \
			   $(CFLAGS) \
			   $(CPPFLAGS) \
			   -DLIBMBS_VERSION_MAJOR="\"$(LIBMBS_MAJOR)"\" \
			   -DLIBMBS_VERSION_MINOR="\"$(LIBMBS_MINOR)"\" \
			   -DLIBMBS_VERSION_PATCH="\"$(LIBMBS_PATCH)"\" \
			   -DLIBMBS_VERSION="\"$(LIBMBS_VERSION)"\" \
			   -Ilibmbs/include

LIBMBS_FLAGS		:= \
			   $(LIBMBS_CFLAGS) \
			   $(LDFLAGS)

LIBMBS_SOURCES		:= libmbs/src/libmbs.c

LIBMBS_OBJECTS		:= $(LIBMBS_SOURCES:%.c=$(OBJ)/%.c.o)
LIBMBS_OBJDEPS		:= $(LIBMBS_OBJECTS:%.o=%.d)

-include $(LIBMBS_OBJDEPS)

LIBMBS_TEST_SOURCES	:= libmbs/tests/test_libmbs.c

LIBMBS_TEST_OBJECTS	:= $(LIBMBS_TEST_SOURCES:%.c=$(TST)/%.x)

$(LIBMBS_OBJECTS): $(OBJ)/%.c.o: %.c | $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) -MMD -o $@ -c $< $(LIBMBS_CFLAGS)

$(LIBMBS_TEST_OBJECTS): $(TST)/%.x: libmbs-test-deps %.c $(LIBMBS_OBJECTS) | $(TST)
	@mkdir -p $(dir $@)
	$(CC) -static -o $@ $(wordlist 2,$(words $^),$^) $(LIBMBS_FLAGS)

$(LIB)/libmbs.$(LIBMBS_VERSION).a: libmbs-deps $(LIBMBS_OBJECTS) | $(LIB)
	@mkdir -p $(dir $@)
	$(AR) -rcs $@ $(wordlist 2,$(words $^),$^)

$(LIB)/libmbs.$(LIBMBS_MAJOR).a: $(LIB)/libmbs.$(LIBMBS_VERSION).a
	ln -sf $(notdir $<) $@

$(LIB)/libmbs.a: $(LIB)/libmbs.$(LIBMBS_MAJOR).a
	ln -sf $(notdir $<) $@

libmbs-deps:

libmbs-build: $(LIB)/libmbs.a

libmbs-test-deps:

libmbs-test: $(LIBMBS_TEST_OBJECTS)
	@for f in $(LIBMBS_TEST_OBJECTS); do ./$$f ; done

libmbs: libmbs-build libmbs-test

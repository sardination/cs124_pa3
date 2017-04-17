CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -O3
LDFLAGS=-g -O3

SRCS=kk.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: kk

kk: $(OBJS)
	$(CXX) $(LDFLAGS) -o kk $(OBJS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include: .depend

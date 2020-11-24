CCFLAGS   := -std=c99 -Wall -pedantic

TARGETS   := SequenceDemo ForwardListDemo
TARGETS   := $(addprefix bin/,$(TARGETS))

all: $(TARGETS)

$(TARGETS): bin utils/Utilities.h

bin: 
	mkdir -p bin

bin/SequenceDemo: SequenceDemo.c Sequence.h Sequence.c
	$(CC)  SequenceDemo.c Sequence.c  -o $@  $(CCFLAGS)

bin/ForwardListDemo: ForwardListDemo.c ForwardList.h ForwardList.c
	$(CC)  ForwardListDemo.c ForwardList.c  -o $@  $(CCFLAGS)

.PHONY:
clean:
	rm -rfv ./bin

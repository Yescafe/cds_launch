cc        := clang
ccflags   := -std=c99 -Wall -pedantic

targets   := SequenceDemo ForwardListDemo
targets   := $(addprefix bin/,$(targets))

all: $(targets)

$(targets): bin utils/Utilities.h

bin: 
	mkdir -p bin

bin/SequenceDemo: SequenceDemo.c Sequence.h Sequence.c
	$(cc)  SequenceDemo.c Sequence.c  -o $@  $(ccflags)

bin/ForwardListDemo: ForwardListDemo.c ForwardList.h ForwardList.c
	$(cc)  ForwardListDemo.c ForwardList.c  -o $@  $(ccflags)

.PHONY:
clean:
	rm -rfv ./bin

cc        := clang
ccflags   := -std=c99 -Wall -pedantic

targets   := SequenceDemo
targets   := $(addprefix bin/,$(targets))

all: $(targets)

$(targets): bin utils/Utilities.h

bin: 
	mkdir -p bin

bin/SequenceDemo: SequenceDemo.c Sequence.h Sequence.c
	$(cc)  SequenceDemo.c Sequence.c  -o $@  $(ccflags)

.PHONY:
clean:
	rm -rfv ./bin
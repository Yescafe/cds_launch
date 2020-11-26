CCFLAGS      := -std=c99 -g -Wall -pedantic

TARGETS      := SequenceDemo ForwardListDemo ListDemo StackQueueDemo BinaryTreeDemo \
                BSTDemo
TARGETS      := $(addprefix bin/,$(TARGETS))
DEPENDENCIES := utils/Utilities.c

all: $(TARGETS)

$(TARGETS): bin utils/Utilities.h

bin: 
	mkdir -p bin

bin/SequenceDemo: SequenceDemo.c Sequence.h Sequence.c
	$(CC)  SequenceDemo.c Sequence.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

bin/ForwardListDemo: ForwardListDemo.c ForwardList.h ForwardList.c
	$(CC)  ForwardListDemo.c ForwardList.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

bin/ListDemo: ListDemo.c List.h List.c
	$(CC)  ListDemo.c List.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

bin/StackQueueDemo: StackQueueDemo.c Stack.h Stack.c Queue.h Queue.c List.h List.c
	$(CC)  StackQueueDemo.c Stack.c Queue.c List.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

bin/BinaryTreeDemo: BinaryTreeDemo.c BinaryTree.h BinaryTree.c
	$(CC)  BinaryTreeDemo.c BinaryTree.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

bin/BSTDemo: BSTDemo.c BST.h BST.c BinaryTree.h BinaryTree.c
	$(CC)  BSTDemo.c BST.c BinaryTree.c  $(DEPENDENCIES)  -o $@  $(CCFLAGS)

.PHONY:
clean:
	rm -rfv ./bin

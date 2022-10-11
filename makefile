# MAKEFILE FOR DISTRIBUTED SYSTEMS PROJECT 1
# WRITTEN BY NUNO DIAS, FC56330
# IF YOU DO NOT INTEGRATE STUDENT NUMBERS FC56330, FC56328 OR FC56369,
# YOU HAVE OBTAINED THIS FILE THROUGH UNAUTHORIZED MEANS AND ARE
# COMMITTING PLAGIARISM

CC=gcc
INC_dir=include
CFLAGS=-g -Wall -I $(INC_dir)
OBJ_dir=object
data.o=
serialization.o=
entry.o=data.h
tree.o=data.h entry.h tree-private.h

testDataDEPS=data.o test_data.o
testEntryDEPS=data.o entry.o test_entry.o
testTreeDEPS=data.o entry.o tree.o test_tree.o

all: out

out: test_data test_entry test_tree clean_obj
%.o: source/%.c $($@)
	$(CC) $(CFLAGS) $(INC_DIR) -o $(OBJ_dir)/$@ -c $<
clean: clean_obj clean_bin
clean_obj:
	rm -f object/*.o
clean_bin:
	rm -f binary/*
test_data: $(testDataDEPS)
	$(CC) $(addprefix $(OBJ_dir)/,$(testDataDEPS)) -o binary/test_data
test_entry: $(testEntryDEPS)
	$(CC) $(addprefix $(OBJ_dir)/,$(testEntryDEPS)) -o binary/test_entry
test_tree: $(testTreeDEPS)
	$(CC) $(addprefix $(OBJ_dir)/,$(testTreeDEPS)) -o binary/test_tree

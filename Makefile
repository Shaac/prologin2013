# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = prologin.c $(wildcard src/*.c)
champion-dists = 
champion-cflags = -ggdb3 -Wall -Wextra -Werror -std=c11 -Iinclude/ -I./

# Evite de toucher a ce qui suit
champion-dists += prologin.h interface.hh
champion-srcs += interface.cc
include ../includes/rules.mk

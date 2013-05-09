# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = prologin.c
champion-dists =
champion-cflags = -ggdb3 -Wall -Wextra -std=c11

# Evite de toucher a ce qui suit
champion-dists += prologin.h interface.hh
champion-srcs += interface.cc
include ../includes/rules.mk

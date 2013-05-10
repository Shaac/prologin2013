# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = $(wildcard *.c)
champion-dists = $(wildcard *.h)
champion-cflags = -ggdb3 -Wall -Wextra -Werror -std=c11 -O2

# Evite de toucher a ce qui suit
champion-dists += prologin.h interface.hh
champion-srcs += interface.cc
include ../includes/rules.mk

stechec: config.yml $(lib_TARGETS).so
	stechec2-run.py $<

.PHONY: stechec

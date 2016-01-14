#! /bin/bash
############################################
#
# Author: liushu1231
# Create time: 2016 1ÔÂ 12 19Ê±07·Ö50Ãë
# E-Mail:liushu.fly@gmail.com
# version 1.0
#
############################################

g++ AhoCorasick.cpp aho_corasick.cpp aho_corasick_test.cpp  -o test -lgtest -lpthread --std=gnu++11 -g

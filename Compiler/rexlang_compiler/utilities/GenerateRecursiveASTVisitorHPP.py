#coding: utf-8

import os, sys, re

with open('../NodeDecl.h') as fp:
    re.search('typedef enum class NodeType')
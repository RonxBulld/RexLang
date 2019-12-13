
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

PROJECT(OECompilerParse)

ADD_LIBRARY(OECompilerParse SHARED
        openeLexer.cpp
        openeLexer.h
        openeParser.cpp
        openeParser.h
        openeParserBaseListener.cpp
        openeParserBaseListener.h
        openeParserBaseVisitor.cpp
        openeParserBaseVisitor.h
        openeParserListener.cpp
        openeParserListener.h
        openeParserVisitor.cpp
        openeParserVisitor.h
        AstGenerate.cpp
        AstGenerate.h
        )

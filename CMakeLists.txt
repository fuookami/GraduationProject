cmake_minimum_required(VERSION 3.9)
project(SSDConfigurator)

set(CMAKE_CXX_STANDARD 11)

add_executable(SSDConfigurator
        PublicModule/ChineseNumberUtils.cpp
        PublicModule/ChineseNumberUtils.h
        PublicModule/DataUtils.cpp
        PublicModule/DataUtils.h
        PublicModule/DateTimeUtils.cpp
        PublicModule/DateTimeUtils.h
        PublicModule/EndianUtils.cpp
        PublicModule/EndianUtils.h
        PublicModule/FileUtils.cpp
        PublicModule/FileUtils.h
        PublicModule/MailUtils.cpp
        PublicModule/MailUtils.h
        PublicModule/NumberVariant.cpp
        PublicModule/NumberVariant.h
        PublicModule/StringConvertUtils.cpp
        PublicModule/StringConvertUtils.h
        PublicModule/StringUtils.cpp
        PublicModule/StringUtils.h
        PublicModule/UuidUtils.cpp
        PublicModule/UuidUtils.h
        XSDAnalyzer/BaseTypeAnalyzer/DataType.cpp
        XSDAnalyzer/BaseTypeAnalyzer/DataType.h
        XSDAnalyzer/BaseTypeAnalyzer/DateTimeType.cpp
        XSDAnalyzer/BaseTypeAnalyzer/DateTimeType.h
        XSDAnalyzer/BaseTypeAnalyzer/ListType.h
        XSDAnalyzer/BaseTypeAnalyzer/main.cpp
        XSDAnalyzer/BaseTypeAnalyzer/NumberType.cpp
        XSDAnalyzer/BaseTypeAnalyzer/NumberType.h
        XSDAnalyzer/BaseTypeAnalyzer/SimpleTypeAnalyzer.cpp
        XSDAnalyzer/BaseTypeAnalyzer/SimpleTypeAnalyzer.h
        XSDAnalyzer/BaseTypeAnalyzer/SimpleTypeInterface.cpp
        XSDAnalyzer/BaseTypeAnalyzer/SimpleTypeInterface.h
        XSDAnalyzer/BaseTypeAnalyzer/SimpleTypes.h
        XSDAnalyzer/BaseTypeAnalyzer/StringType.cpp
        XSDAnalyzer/BaseTypeAnalyzer/StringType.h
        XSDAnalyzer/BaseTypeAnalyzer/test.cpp
        XSDAnalyzer/BaseTypeAnalyzer/test.h
        XSDAnalyzer/BaseTypeAnalyzer/UnionType.h
        XSDAnalyzer/BaseTypeAnalyzer/XSDToken.h)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = XT.bin

INCLUDEPATH += ./ctp/v6.3.6_20160606_api_tradeapi_linux64
LIBS += -lthostmduserapi -lthosttraderapi -lpthread

QMAKE_CXXFLAGS += -Wno-unused-parameter

SOURCES += main.cpp \
    util/XTLog.cpp \
    ctp/XTCtpMd.cpp \
    XTThread.cpp \
    XTCore.cpp \
    XTTimer.cpp \
    util/XTLock.cpp

HEADERS += \
    XTDef.h \
    util/XTLog.h \
    ctp/v6.3.6_20160606_api_tradeapi_linux64/ThostFtdcMdApi.h \
    ctp/v6.3.6_20160606_api_tradeapi_linux64/ThostFtdcTraderApi.h \
    ctp/v6.3.6_20160606_api_tradeapi_linux64/ThostFtdcUserApiDataType.h \
    ctp/v6.3.6_20160606_api_tradeapi_linux64/ThostFtdcUserApiStruct.h \
    ctp/XTCtpMd.h \
    XTThread.h \
    ctp/XTCTPDef.h \
    XTCore.h \
    XTTimer.h \
    util/XTHeap.h \
    util/XTLock.h

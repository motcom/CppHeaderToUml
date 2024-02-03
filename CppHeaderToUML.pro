QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        argholder.cpp \
        filelistmanager.cpp \
        main.cpp \
        main_dest.cpp \
        rawwordtransrator.cpp \
        umlclassextract.cpp \
        umlclassrelation.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
   argholder.h \
   filelistmanager.h \
   rawwordtransrator.h \
   umlclassextract.h \
   umlclassrelation.h

CONFIG(release,debug|release) {
    DEFINES += TEST_MODE
}else{
    DEFINES += APP_MODE
}

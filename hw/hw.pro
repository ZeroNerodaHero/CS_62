QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../Downloads/CS_62/HW1Complete/DirectMessage.cpp \
    ../../../Downloads/CS_62/HW1Complete/Network.cpp \
    ../../../Downloads/CS_62/HW1Complete/Post.cpp \
    ../../../Downloads/CS_62/HW1Complete/User.cpp \
    loggedform.cpp \
    loginpage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../../Downloads/CS_62/HW1Complete/DirectMessage.h \
    ../../../Downloads/CS_62/HW1Complete/Network.h \
    ../../../Downloads/CS_62/HW1Complete/Post.h \
    ../../../Downloads/CS_62/HW1Complete/User.h \
    loggedform.h \
    loginpage.h \
    mainwindow.h

FORMS += \
    loggedform.ui \
    loginpage.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../Downloads/CS_62/HW1Complete/largeTest \
    ../../../Downloads/CS_62/HW1Complete/posts \
    networkInfo

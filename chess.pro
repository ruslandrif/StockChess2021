QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core/src/board.cpp \
    core/src/game.cpp \
    core/src/main.cpp \
    elpp/easylogging++.cc \
    figures/src/bishop.cpp \
    figures/src/figure.cpp \
    figures/src/king.cpp \
    figures/src/knight.cpp \
    figures/src/piece.cpp \
    figures/src/queen.cpp \
    figures/src/rook.cpp
HEADERS += \
    core/headers/board.h \
    core/headers/common_used.h \
    core/headers/game.h \
    elpp/easylogging++.h \
    figures/headers/bishop.h \
    figures/headers/figure.h \
    figures/headers/king.h \
    figures/headers/knight.h \
    figures/headers/piece.h \
    figures/headers/queen.h \
    figures/headers/rook.h

INCLUDEPATH += \
    figures/headers \
    core/headers \
    elpp

RESOURCES += \
    $$files(pics/figures/*.png) \
    $$files(pics/*.jpg) \
    $$files(pics/*.png) \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    board.cpp \
    figure.cpp \
    game.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    piece.cpp \
    queen.cpp \
    rook.cpp

HEADERS += \
    bishop.h \
    board.h \
    common_used.h \
    figure.h \
    game.h \
    king.h \
    knight.h \
    piece.h \
    queen.h \
    rook.h

RESOURCES += \
    $$files(pics/figures/*.png) \
    $$files(pics/*.jpg) \
    $$files(pics/*.png) \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

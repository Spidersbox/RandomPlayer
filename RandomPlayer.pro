TARGET = randomplayer
QT += core gui \
      multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

SOURCES += \
    src/editform.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/editform.h \
    src/mainwindow.h

FORMS += \
    src/forms/editform.ui \
    src/forms/mainwindow.ui \

RC_FILE = src/RandomPlayer.rc

RESOURCES += \
    src/RandomPlayer.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/RandomPlayer.rc \
    src/images/RandomPlayer.ico \
    src/images/blue-next-64.png \
    src/images/blue-next-hover-64.png \
    src/images/blue-pause-64.png \
    src/images/blue-pause-hover-64.png \
    src/images/blue-play-64.png \
    src/images/blue-play-hover-64.png \
    src/images/blue-previous-64.png \
    src/images/blue-previous-hover-64.png \
    src/images/blue-repeat-64.png \
    src/images/blue-shuffle-64.png \
    src/images/blue-stop-64.png \
    src/images/blue-stop-hover-64.png \
    src/images/close.png \
    src/images/edit.png \
    src/images/next.png \
    src/images/next16.png \
    src/images/next_hover.png \
    src/images/open.png \
    src/images/pause.png \
    src/images/pause16.png \
    src/images/pause_hover.png \
    src/images/play.png \
    src/images/play16.png \
    src/images/play_hover.png \
    src/images/playlist.png \
    src/images/previous.png \
    src/images/previous16.png \
    src/images/previous_hover.png \
    src/images/repeat.png \
    src/images/repeat16.png \
    src/images/save.png \
    src/images/shuffle.png \
    src/images/shuffle16.png \
    src/images/stop.png \
    src/images/stop16.png \
    src/images/stop_hover.png

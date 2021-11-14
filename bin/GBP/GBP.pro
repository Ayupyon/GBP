QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Aya.cpp \
    BoostBullet.cpp \
    Boost_Marinai.cpp \
    Cart_Marinai.cpp \
    Control.cpp \
    FlyMarinai.cpp \
    HelmetMarinai.cpp \
    Himari.cpp \
    Kaoru.cpp \
    Kokoro.cpp \
    Land.cpp \
    Michelle_Statue.cpp \
    Moca.cpp \
    NormalMarinai.cpp \
    Normal_Flymarinai.cpp \
    Obstacle.cpp \
    Obstacle_Flymarinai.cpp \
    Otae.cpp \
    Pin_Bullet.cpp \
    Pin_Marinai.cpp \
    Ran.cpp \
    Saya.cpp \
    SmileStarBullet.cpp \
    StartScene.cpp \
    Tomoe.cpp \
    Tsugu.cpp \
    WheelMarinai.cpp \
    arisa.cpp \
    basegirls.cpp \
    basemarinai.cpp \
    baseobject.cpp \
    battlescene.cpp \
    card.cpp \
    choosescene.cpp \
    kasumi.cpp \
    main.cpp \
    mybtn.cpp \
    rimi.cpp \
    starboard.cpp \
    starbullet.cpp \
    starstone.cpp

HEADERS += \
    Aya.h \
    BoostBullet.h \
    Boost_Marinai.h \
    Cart_Marinai.h \
    Control.h \
    FlyMarinai.h \
    HelmetMarinai.h \
    Himari.h \
    Kaoru.h \
    Kokoro.h \
    Land.h \
    Michelle_Statue.h \
    Moca.h \
    NormalMarinai.h \
    Normal_Flymarinai.h \
    Obstacle.h \
    Obstacle_Flymarinai.h \
    Otae.h \
    Pin_Bullet.h \
    Pin_Marinai.h \
    Ran.h \
    Saya.h \
    SmileStarBullet.h \
    StartScene.h \
    Tomoe.h \
    Tsugu.h \
    WheelMarinai.h \
    arisa.h \
    basegirls.h \
    basemarinai.h \
    baseobject.h \
    battlescene.h \
    card.h \
    choosescene.h \
    kasumi.h \
    mybtn.h \
    objects.h \
    rimi.h \
    starboard.h \
    starbullet.h \
    starstone.h

FORMS += \
    StartScene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/res.qrc

DISTFILES +=

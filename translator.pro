QT       -= gui

# Output file
TARGET = ../translator
TARGET_EXT = .asi

# Configs
TEMPLATE = lib
CONFIG += dll c++14
CONFIG -= UNICODE
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++ -Wl,--strip-all -Os -ffast-math
# Generate .map file
#QMAKE_LFLAGS = -Wl,-Map=translator.map


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	translator.cpp \
	loader.cpp \
	llmo/ccallhook.cpp \
	llmo/memsafe.cpp \
	llmo/cshortasm.cpp \
	sys/mman.c \
	sys/SRKeys.cpp \
	d3d9/proxydirectx.cpp \
	d3d9/directx.cpp \
	d3d9/color.cpp \
	d3d9/d3drender.cpp \
	d3d9/texture.cpp \
	d3d9/MenuManager/ContextMenu.cpp \
	d3d9/MenuManager/Listing.cpp \
	d3d9/MenuManager/Menu.cpp \
	d3d9/MenuManager/Node.cpp \
	d3d9/MenuManager/WidgetBase.cpp \
	d3d9/MenuManager/Text.cpp \
	d3d9/MenuManager/VerticalLayout.cpp \
	d3d9/MenuManager/Slider.cpp \
	CGame/CPed.cpp \
	CGame/CEntity.cpp \
	CGame/CPhysical.cpp \
	CGame/CObject.cpp \
	CGame/Types.cpp \
	CGame/CPlaceable.cpp \
	CGame/methods.cpp \
	CGame/CCam.cpp \
	CGame/CCamera.cpp \
	CGame/CVehicle.cpp \
	CGame/CAutomobile.cpp \
	CGame/CBike.cpp \
	CGame/samp.cpp \
	CGame/sampfuncs.cpp \
	RakNet/BitStream.cpp \
	translate.cpp

HEADERS +=\
	translator.h \
	loader.h \
	llmo/ccallhook.h \
	llmo/memsafe.h \
	llmo/cshortasm.h \
	sys/mman.h \
	sys/SRKeys.h \
	d3d9/proxydirectx.h \
	d3d9/GirlCursor.hpp \
	d3d9/directx.h \
	d3d9/color.h \
	d3d9/d3drender.h \
	d3d9/texture.h \
	d3d9/MenuManager/ContextMenu.h \
	d3d9/MenuManager/Listing.h \
	d3d9/MenuManager/Menu.h \
	d3d9/MenuManager/Node.h \
	d3d9/MenuManager/WidgetBase.h \
	d3d9/MenuManager/Text.h \
	d3d9/MenuManager/VerticalLayout.h \
	d3d9/MenuManager/Slider.h \
	CGame/Types.h \
	CGame/CPlaceable.h \
	CGame/CEntity.h \
	CGame/CPhysical.h \
	CGame/CObject.h \
	CGame/CHAnimIFrame.h \
	CGame/CBone.h \
	CGame/CPedIK.h \
	CGame/CParticleData.h \
	CGame/CWeaponSlot.h \
	CGame/CPed.h \
	CGame/CVehicle.h \
	CGame/CAutomobile.h \
	CGame/CMosterTruck.h \
	CGame/CBike.h \
	CGame/CQuad.h \
	CGame/CBmx.h \
	CGame/CHeli.h \
	CGame/CPlane.h \
	CGame/CBoat.h \
	CGame/CTrailer.h \
	CGame/methods.h \
	CGame/CCam.h \
	CGame/CCamera.h \
	CGame/samp.h \
	CGame/sampfuncs.h \
	RakNet/BitStream.h \
	RakNet/RakClient.h \
	IniFiles.hpp \
	translate.h

LIBS += -ld3d9 \
		-ld3dx9 \
		-lgdi32 \
		-luser32 \
		-lkernel32


#OS = LINUX
OS = MACOSX
#OS = WINDOWS

PROG=florian

OBJS =	main.o dictionary.o speakjet_lookup.o utility.o hid_$(OS).o

LIBS = -lusb

ifeq ($(OS), MACOSX)
	CXX = g++
	CC = gcc
	SDK = /Developer/SDKs/MacOSX10.5.sdk
	ARCH = -mmacosx-version-min=10.5 -arch i386
	STRIP = strip
	CFLAGS =  -Wall -O2 -g -arch i386 -fmessage-length=0 #-DOS_$(OS) -isysroot $(SDK) $(ARCH)
	CXXFLAGS = -Wall -O2 -g -arch i386 -fmessage-length=0 #-DOS_$(OS) -isysroot $(SDK) $(ARCH)
	LIBS = $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation
	TARGET = $(PROG)
else ifeq ($(OS), WINDOWS)
	CXX = i586-mingw32msvc-gpp
	CC = i586-mingw32msvc-gcc
	STRIP = i586-mingw32msvc-strip
	CFLAGS = -Wall -O2 -DOS_$(OS)
	CxxFLAGS = -Wall -O2 -DOS_$(OS)
	LIBS = -lhid -lsetupapi
	TARGET = $(PROG).exe
endif

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

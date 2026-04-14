CXX = g++
CXXFLAGS = -Wall -Wno-unknown-pragmas
LDLIBS = -leasyx -lwinmm

TARGET = guess

OBJDIR = obj

SRCS = main.cpp show.cpp guess.cpp sound.cpp globals.cpp

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDLIBS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	-mkdir $(OBJDIR) 2>nul

clean:
	-rmdir /S /Q $(OBJDIR) 2>nul
	-del /Q $(TARGET).exe 2>nul
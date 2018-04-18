CXX	= clang++
CXXFLAGS= -std=c++1z -g
LDFLAGS	=

TARGET	= nbody
OBJS	= main.o

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

default:
	make $(TARGET)

run: $(TARGET)
	./$<

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)

$(TARGET):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

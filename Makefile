CXX=g++
CXXFLAGS = -std=c++17 -g

SOURCES = $(wildcard *.cpp)
OBJFILES = $(notdir $(SOURCES:.cpp=.o))
LIBS = 

all: image_app

# Applicaiton Targets:
image_app: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) ${LIBS} -o $@

%.o: %.cpp %.h
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generate dependencies
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $(INCLUDES) $1
-include $(addprefix $(OBJDIR)/,$(OBJFILES:.o=.d))

clean:
	rm -f *.o *.d image_editor
# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================

include ../../build/bakefiles.gen/config.gnu

# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###

OBJDIR = gnu$(OPTION_SELECTLIB)$(SUFFIX_LIBRARY)

### Conditionally set variables: ###

ifeq ($(OPTION_DEBUG),0)
SUFFIX_STATIC = _s
endif
ifeq ($(OPTION_DEBUG),1)
SUFFIX_STATIC = _sd
endif
ifeq ($(OPTION_DEBUG),0)
SUFFIX_DYNAMIC = 
endif
ifeq ($(OPTION_DEBUG),1)
SUFFIX_DYNAMIC = _d
endif
ifeq ($(OPTION_SHARED),0)
SUFFIX_LIBRARY = $(SUFFIX_STATIC)
endif
ifeq ($(OPTION_SHARED),1)
SUFFIX_LIBRARY = $(SUFFIX_DYNAMIC)
endif


all: ../../lib/$(OBJDIR)/examples/Win32Integration
../../lib/$(OBJDIR)/examples/Win32Integration:
	@mkdir -p ../../lib/$(OBJDIR)/examples/Win32Integration

### Targets: ###

all: 

install: 

uninstall: 

clean: 
	rm -f ../../lib/$(OBJDIR)/examples/Win32Integration/*.o
	rm -f ../../lib/$(OBJDIR)/examples/Win32Integration/*.d

.PHONY: all install uninstall clean


# Dependencies tracking:
-include ../../lib/$(OBJDIR)/examples/Win32Integration/*.d

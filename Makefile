NAME = tik
# ICON = icon.png
DESCRIPTION  = "ti k"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz -std=gnu++2b

# ----------------------------

include $(shell cedev-config --makefile)

run: all
	CEmu

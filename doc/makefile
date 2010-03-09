# 
# makefile
# 
# Author
#     Andrew Brown
#
GANDER = ..

# Images
IMAGES = gander.png

# Directives
.PHONY: all html
all: html
html: 
	@echo "  Generating HTML documentation."
	@$(RM) ${addprefix html/,$(IMAGES)}
	@doxygen Doxyfile

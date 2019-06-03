COREPATH  = core
CLIENTPATH = client
SERVERPATH = server
TOOLSPATH = tools/packer

CORETAGS = $(shell find $(COREPATH) -type f -iname 'tags')
CLIENTTAGS = $(shell find $(CLIENTPATH) -type f -iname 'tags')
SERVERTAGS = $(shell find $(SERVERPATH) -type f -iname 'tags')
TOOLSTAGS = $(shell find $(TOOLSPATH) -type f -iname 'tags')

TAGMAKE = ctags --fields=+l --c-kinds=+p --c++-kinds=+p -R
TAGINCLUDES = -R /mnt/data/code/c++/libs/glm/glm

all: client server tags

client: nix win emcc tags

tags: cleantags maketags

packer: core tools

nix:
	+$(MAKE) -C $(COREPATH) -f Makefile
	+$(MAKE) -C $(CLIENTPATH) -f Makefile

win:
	+$(MAKE) -C $(COREPATH) -f Makefile.WIN32
	+$(MAKE) -C $(CLIENTPATH) -f Makefile.WIN32

emcc:
	+$(MAKE) -C $(CLIENTPATH) -f Makefile.EMCC

server:
	+$(MAKE) -C $(COREPATH) -f Makefile
	+$(MAKE) -C $(SERVERPATH) -f Makefile

core:
	+$(MAKE) -C $(COREPATH) -f Makefile
	+$(MAKE) -C $(COREPATH) -f Makefile.WIN32

tools:
	+$(MAKE) -C $(TOOLSPATH) -f Makefile

maketags:
	@$(TAGMAKE) $(COREPATH)/src $(TAGINCLUDES) 
	@mv tags $(COREPATH)
	@$(TAGMAKE) $(CLIENTPATH)/src $(TAGINCLUDES) -R 
	@mv tags $(CLIENTPATH)
	@$(TAGMAKE) $(SERVERPATH) $(TAGINCLUDES) 
	@mv tags $(SERVERPATH)
	@$(TAGMAKE) $(TOOLSPATH) $(TAGINCLUDES) 
	@mv tags $(TOOLSPATH)

clean: cleanobjs cleantags

cleanobjs:
	+$(MAKE) clean -C $(COREPATH) -f Makefile
	+$(MAKE) clean -C $(COREPATH) -f Makefile.WIN32
	+$(MAKE) clean -C $(CLIENTPATH) -f Makefile
	+$(MAKE) clean -C $(CLIENTPATH) -f Makefile.WIN32
	+$(MAKE) clean -C $(SERVERPATH) -f Makefile
	+$(MAKE) clean -C $(TOOLSPATH) -f Makefile

cleantags:
	@rm -rf $(CORETAGS)
	@rm -rf $(CLIENTTAGS)
	@rm -rf $(SERVERTAGS)
	@rm -rf $(TOOLSTAGS)


.PHONY: core tools 

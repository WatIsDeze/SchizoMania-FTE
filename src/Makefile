all:
	make menu
	make games
	make mods
	make plugins

menu:
	cd menu-fn && $(MAKE)

games:
	cd client/valve && $(MAKE)
	cd server/valve && $(MAKE)

mods:
	cd client/cstrike && $(MAKE)
	cd server/cstrike && $(MAKE)
	cd client/schizomania && $(MAKE)
	cd server/schizomania && $(MAKE)

plugins:
	cd plugins && $(MAKE)

BIN_PATH = /usr/bin/
RU_PATH = /usr/share/locale
LOCALE  = /ru/LC_MESSAGES/

ifdef DESTDIR
	BIN_PATH = $(DESTDIR)
	RU_PATH = $(DESTDIR)
endif

all: guess $(RU_PATH)$(LOCALE)guess.mo

$(RU_PATH)$(LOCALE)guess.mo: guess.po
	mkdir -p `dirname $@`
	msgfmt $< -o $(RU_PATH)$@

guess: guess.c
	gcc $< -o $(BIN_PATH)$@ 

guess.po: guess.pot
	msgmerge -U $@ $<

guess.pot: guess.c 
	xgettext -k_ -c guess.c -o update.pot
	msgmerge -U $@ update.pot

clean:
	rm -rf $(RU_PATH)ru     
	rm $(RU_PATH)update.pot 
	rm $(BIN_PATH)guess
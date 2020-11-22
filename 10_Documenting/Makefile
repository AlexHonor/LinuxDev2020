all: guess po/ru/LC_MESSAGES/guess.mo html

guess: guess.c
	gcc $< -o $@

po/%/LC_MESSAGES/guess.mo: po/%/LC_MESSAGES/guess.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

po/%/LC_MESSAGES/guess.po: po/guess.pot
	msgmerge -U $@ $<

po/guess.pot: guess.c
	xgettext -k_ -c guess.c -o changes.pot
	msgmerge -U $@ changes.pot

html: Doxyfile guess.c
	doxygen Doxyfile
	rm -rf latex

clean:
	rm -rf html
	rm -rf latex
	rm -f guess
	rm -f po/*.pot~ po/*.po~ changes.pot
	rm -rf po/*/LC_MESSAGES/*.mo
	rm -rf po/ru/*.mo
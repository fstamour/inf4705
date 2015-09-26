
sort: main.cpp quicksort.h
	g++ --std=c++14 -g -o $@ $^

fetch-data: FORCE
	xdg-open https://moodle.polymtl.ca/pluginfile.php/160082/mod_resource/content/5/htmlsc/tp1-tri-donnees.tar.gz 

extract-data: tp1-tri-donnees.tar.gz
	tar -zxvvf $^
	[ -d data ] && rmdir data
	mv tp1-H10-donnees data

.PHONY: FORCE



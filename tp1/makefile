


sort: main.cpp quicksort.h
	g++ --std=c++14 -o $@ $^

fetch-data: FORCE
	xdg-open https://moodle.polymtl.ca/pluginfile.php/160082/mod_resource/content/5/htmlsc/tp1-tri-donnees.tar.gz 

extract-data: tp1-tri-donnees.tar.gz
	tar -zxvvf $^
	mv tp1-tri-donnees data

.PHONY: FORCE



TEMPLATE = subdirs

SUBDIRS += src tests

CONFIG += c++11
CONFIG += no_lflags_merge

unix: LIBS += -L"/usr/lib64/" -lgmp -lgmpxx -lmpfr

#unix: CONFIG += link_pkgconfig
#unix: PKGCONFIG += gmpxx

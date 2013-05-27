DESCRIPTION = "CLooG is a software which generates loops for scanning Z-polyhedra."
HOMEPAGE = "http://www.cloog.org/"
LICENSE = "LGPLv2.1"
SECTION = "libs"

FILESPATH = "${@base_set_filespath([ '${FILE_DIRNAME}/cloog-ppl' ], d)}"

inherit autotools

BBCLASSEXTEND = "native nativesdk "
EXTRA_OECONF = " --with-bits=gmp --with-isl=no"
EXTRA_OECONF_class-native = " --with-bits=gmp --with-isl=no"
EXTRA_OECONF_class-nativesdk = " --with-bits=gmp --with-isl=no"

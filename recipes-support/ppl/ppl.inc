DESCRIPTION = "Parma Polyhedra Library: C++ library for (not necessarily closed) convex polyhedra and other numerical abstractions."
HOMEPAGE = "http://bugseng.com/products/ppl"
LICENSE = "GPLv3"
SECTION = "libs"

BBCLASSEXTEND = "native nativesdk "
FILESPATH = "${@base_set_filespath([ '${FILE_DIRNAME}/ppl' ], d)}"

inherit autotools

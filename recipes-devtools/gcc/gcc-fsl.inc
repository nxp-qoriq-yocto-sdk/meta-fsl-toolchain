#LIC_FILES_CHKSUM = "file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552 \
#                   file://COPYING3;md5=d32239bcb673463ab874e80d47fae504 \
#                   file://COPYING3.LIB;md5=6a6a8e020838b23406c81b19c1d46df6 \
#                   file://COPYING.LIB;md5=2d5025d4aa3495befef8f17206a5b0a1 \
#                   file://COPYING.RUNTIME;md5=fe60d87048567d4fe8c8a0ed2448bcc8"

PV_fsl = "fsl-git"

BINV_fsl = "4.7.2"

SRCREV_fsl = "${AUTOREV}"

SRC_URI_fsl = "git://git.am.freescale.net/gitolite/sdk/gcc.git;destsuffix=gcc-${PV} \
		file://optional_libstdc.patch \
		file://use-defaults.h-and-t-oe-in-B.patch \
		file://GLIBC_DYNAMIC_LINKER.patch \
		"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"


PV = "4.7.2+fsl"

BINV = "4.7.2"

SRCREV = "c88a2f851197a103296175e0a7a1cb94ab91bcc3"

SRC_URI = "git://git.am.freescale.net/gitolite/sdk/gcc.git;destsuffix=gcc-${PV} \
        file://optional_libstdc.patch \
        file://use-defaults.h-and-t-oe-in-B.patch \
        file://GLIBC_DYNAMIC_LINKER.patch \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

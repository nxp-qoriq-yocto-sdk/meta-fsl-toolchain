PV = "4.7.2+fsl"

BINV = "4.7.2"

SRCREV = "660a3488ee161884d5e2dae2ca60e6435df037bb"

SRC_URI = "git://git.am.freescale.net/gitolite/sdk/gcc.git;destsuffix=gcc-${PV} \
        file://optional_libstdc.patch \
        file://use-defaults.h-and-t-oe-in-B.patch \
        file://GLIBC_DYNAMIC_LINKER.patch \
        file://64bithack.patch \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

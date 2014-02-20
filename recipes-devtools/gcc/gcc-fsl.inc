PV = "4.8.1+fsl"

BINV = "4.8.1"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRCBRANCH = "gcc-${BINV}"
SRCREV = "d08552bd37bddd6b0eac05e5e8e8cc0cfc2a9bbe"
SRC_URI = "git://git.am.freescale.net/gitolite/sdk/gcc.git;branch=${SRCBRANCH};destsuffix=gcc-${PV} \
           file://0019-64-bit-multilib-hack-backport.patch \
           file://0020-optional-libstdc.patch \
           file://0023-Use-the-defaults.h-in-B-instead-of-S-and-t-oe-in-B.patch \
           file://0038-gcc-4.8-build-args.patch \
"

NATIVEDEPS =+ "cloog-native"

EXTRA_OECONF_BASE = "--enable-lto \
                     --enable-libssp \
                     --disable-bootstrap \
                     --disable-libmudflap \
                     --with-system-zlib \
                     --with-linker-hash-style=${LINKER_HASH_STYLE} \
                     --enable-linker-build-id \
                     --enable-checking=release \
                     --enable-cheaders=c_global "

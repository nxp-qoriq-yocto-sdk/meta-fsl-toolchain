PV = "4.8.1+fsl"

BINV = "4.8.1"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRCBRANCH = "gcc-${BINV}"
SRCREV = "26137172147f224e7fd0ce2a80dcfbde19d672d9"
SRC_URI = "git://git.am.freescale.net/gitolite/sdk/gcc.git;branch=${SRCBRANCH};destsuffix=gcc-${PV} \
           file://0019-64-bit-multilib-hack-backport.patch \
           file://0020-optional-libstdc.patch \
           file://0023-Use-the-defaults.h-in-B-instead-of-S-and-t-oe-in-B.patch \
           file://0029-Define-GLIBC_DYNAMIC_LINKER-and-UCLIBC_DYNAMIC_LINKE.patch \
           file://0038-gcc-4.8-build-args.patch \
           file://0049-Enable-SPE-AltiVec-generation-on-powepc-linux-target-gcc-4.8.1.patch \
           file://0034-Use-the-multilib-config-files-from-B-instead-of-usin.patch \
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

do_configure_prepend() {
        lineno=$(grep -n "m4_define(\[_GCC_AUTOCONF_VERSION\], \[2." ${S}/config/override.m4 | cut -f1 -d:)
        ver=$(autoconf -V | head -1 | cut -d' ' -f 4)
        sed -i "${lineno}s/2\.[0-9][0-9]/${ver}/" ${S}/config/override.m4
}

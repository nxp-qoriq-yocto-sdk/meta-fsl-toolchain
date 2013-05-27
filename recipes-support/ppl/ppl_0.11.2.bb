require ppl.inc

DEPENDS = "gmp"

LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"

SRC_URI = "http://bugseng.com/products/ppl/download/ftp/releases/${PV}/ppl-${PV}.tar.gz \
        file://GMP_version_5_1_0_defines_std__numeric_limits.patch \
        file://remove_obsolete_dist-lzma_from_configure_ac.patch \
        file://remove_obsolete_dist-lzma_from_watchdog_configure_ac.patch \
        file://pkglib_DATA-is-not-valid-since-automake-1.11.1.patch "

SRC_URI[md5sum] = "ce014f153a28006009db207ca953a984"
SRC_URI[sha256sum] = "666542b853beeb5793cd327fff8f231a8317e162654e817f441427fe1f85b835"

S = "${WORKDIR}/ppl-${PV}"

EXTRA_OECONF = " --enable-interfaces=c,c++"
EXTRA_OECONF_class-native = " --enable-interfaces=c,c++"
EXTRA_OECONF_class-nativesdk = " --enable-interfaces=c,c++"

acpaths="$acpaths -I m4"

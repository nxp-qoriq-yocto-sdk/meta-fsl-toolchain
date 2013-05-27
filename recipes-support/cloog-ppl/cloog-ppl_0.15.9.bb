require cloog-ppl.inc

DEPENDS = "gmp ppl"

LIC_FILES_CHKSUM = "file://LICENSE;md5=2c0c8c39efe4b616cc7187df2883ef4a"

SRC_URI = "ftp://gcc.gnu.org/pub/gcc/infrastructure/cloog-ppl-${PV}.tar.gz \
        file://fix_ppl_version_checking.patch "

SRC_URI[md5sum] = "806e001d1b1a6b130069ff6274900af5"
SRC_URI[sha256sum] = "8c54d4bca186cb66671e07540aec276d5f8ad013ae8867294576b431cbb142a5"

S = "${WORKDIR}/cloog-ppl-${PV}"

EXTRA_OECONF_class-native += " --with-ppl=${STAGING_DIR_NATIVE}${prefix_native}"
EXTRA_OECONF_class-nativesdk += " --with-ppl=${STAGING_DIR_HOST}${layout_exec_prefix}"

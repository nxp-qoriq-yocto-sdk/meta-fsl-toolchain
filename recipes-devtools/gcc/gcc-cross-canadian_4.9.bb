require recipes-devtools/gcc/gcc-${PV}.inc
require gcc-cross-canadian.inc

DEPENDS += "nativesdk-isl nativesdk-cloog"
RDEPENDS_${PN} += "nativesdk-isl nativesdk-cloog"

EXTRA_OECONF += "--with-isl=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} \
                 --with-cloog=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} \
"

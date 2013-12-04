require gcc-fsl.inc

DEPENDS += "nativesdk-isl nativesdk-cloog"
RDEPENDS_${PN} += "nativesdk-isl nativesdk-cloog"

EXTRA_OECONF += "--with-isl=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} \
                 --with-cloog=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} "

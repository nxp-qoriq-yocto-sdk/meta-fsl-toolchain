require gcc-fsl.inc

DEPENDS += " nativesdk-ppl nativesdk-cloog-ppl"
RDEPENDS_${PN} += " nativesdk-ppl nativesdk-cloog-ppl"

EXTRA_OECONF += " --with-ppl=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} \
                --with-cloog=${STAGING_DIR_HOST}${SDKPATHNATIVE}${prefix_nativesdk} "

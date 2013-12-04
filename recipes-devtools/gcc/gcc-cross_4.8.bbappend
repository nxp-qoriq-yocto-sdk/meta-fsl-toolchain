require gcc-fsl.inc

EXTRA_OECONF_PATHS += "--with-isl=${STAGING_DIR_NATIVE}${prefix_native} \
                       --with-cloog=${STAGING_DIR_NATIVE}${prefix_native} "

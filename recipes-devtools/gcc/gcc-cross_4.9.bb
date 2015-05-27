require recipes-devtools/gcc/gcc-${PV}.inc
require gcc-cross.inc

EXTRA_OECONF_PATHS += "--with-isl=${STAGING_DIR_NATIVE}${prefix_native} \
                       --with-cloog=${STAGING_DIR_NATIVE}${prefix_native} \
"

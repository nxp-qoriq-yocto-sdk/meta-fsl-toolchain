FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
SRC_URI_append = " file://fix-compile-error.patch"

DEPENDS_append = " libtirpc"
CPPFLAGS_append = " -I${STAGING_INCDIR}/tirpc"

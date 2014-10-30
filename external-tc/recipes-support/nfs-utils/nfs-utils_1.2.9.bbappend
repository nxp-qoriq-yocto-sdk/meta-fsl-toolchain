FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://remove-compile-failed-subdirs.patch"

DEPENDS_append = " libtirpc"

EXTRA_OEMAKE_append = " LIBTIRPC=-ltirpc"

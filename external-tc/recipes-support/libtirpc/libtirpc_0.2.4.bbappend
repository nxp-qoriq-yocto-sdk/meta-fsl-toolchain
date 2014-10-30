FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://disable-des-functions.patch"

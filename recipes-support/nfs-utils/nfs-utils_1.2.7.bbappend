FILESEXTRAPATHS_prepend := "${@base_conditional('TCMODE', 'external-fsl', '${THISDIR}/files:', '', d)}"

SRC_URI_append = "${@base_conditional('TCMODE', 'external-fsl', ' file://remove-compile-failed-subdirs.patch', '', d)}"

DEPENDS_append = "${@base_conditional('TCMODE', 'external-fsl', ' libtirpc', '', d)}"

EXTRA_OEMAKE_append = "${@base_conditional('TCMODE', 'external-fsl', ' LIBTIRPC=-ltirpc', '', d)}"

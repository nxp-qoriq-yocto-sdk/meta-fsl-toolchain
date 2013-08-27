FILESEXTRAPATHS_prepend := "${@base_conditional('TCMODE', 'external-fsl', '${THISDIR}/files:', '', d)}"

SRC_URI_append = "${@base_conditional('TCMODE', 'external-fsl', ' file://fix-compile-error.patch', '', d)}"

DEPENDS_append = "${@base_conditional('TCMODE', 'external-fsl', ' libtirpc', '', d)}"

CPPFLAGS_append = "${@base_conditional('TCMODE', 'external-fsl', ' -I${STAGING_INCDIR}/tirpc', '', d)}"

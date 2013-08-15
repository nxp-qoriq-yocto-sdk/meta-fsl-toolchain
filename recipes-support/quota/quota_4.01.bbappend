FILESEXTRAPATHS_prepend := "${@base_conditional('TCMODE', 'external-fsl', '${THISDIR}/files:', '', d)}"

SRC_URI_append = "${@base_conditional('TCMODE', 'external-fsl', ' file://remove-the-compile-failed-objects.patch', '', d)}"

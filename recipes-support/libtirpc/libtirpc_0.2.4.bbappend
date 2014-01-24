FILESEXTRAPATHS_prepend := "${@base_conditional('TCMODE', 'external-fsl', '${THISDIR}/files:', '', d)}"

SRC_URI_append = "${@base_conditional('TCMODE', 'external-fsl', ' file://disable-des-functions.patch', '', d)}"

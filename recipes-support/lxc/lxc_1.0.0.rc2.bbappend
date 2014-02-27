FILESEXTRAPATHS_prepend := "${@base_conditional('TCMODE', 'external-fsl', '${THISDIR}/files:', '', d)}"

SRC_URI_append = "${@base_conditional('TCMODE', 'external-fsl', ' file://0001-fix-the-definition-conflict-issue-of-setns.patch', '', d)}"

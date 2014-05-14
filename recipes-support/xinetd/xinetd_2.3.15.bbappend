DEPENDS_append = "${@base_conditional('TCMODE', 'external-fsl', ' libtirpc', '', d)}"

LDFLAGS_append = "${@base_conditional('TCMODE', 'external-fsl', ' -ltirpc', '', d)}"

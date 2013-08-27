LDFLAGS_append = "${@base_conditional('TCMODE', 'external-fsl', ' -ltirpc', '', d)}"

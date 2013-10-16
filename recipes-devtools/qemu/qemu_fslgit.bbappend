EXTRA_OEMAKE_append_e5500-64b = "${@base_contains('TCMODE', 'external-fsl', 'AS="${AS} -a64"', '', d)}"
EXTRA_OEMAKE_append_e6500-64b = "${@base_contains('TCMODE', 'external-fsl', 'AS="${AS} -a64"', '', d)}"

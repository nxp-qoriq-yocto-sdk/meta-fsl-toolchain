do_install_append() {
   ${@base_conditional('TCMODE', 'external-fsl', 'rm -fr ${D}${bindir}/powerpc-fsl_*', '', d)}
}

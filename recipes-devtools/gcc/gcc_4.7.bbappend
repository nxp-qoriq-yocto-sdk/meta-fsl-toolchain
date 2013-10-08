require gcc-fsl.inc

python () {
   tcmode = d.getVar("TCMODE", True)
   arch = d.getVar("OVERRIDES", True)

   if "external-fsl" in tcmode and "e5500-64b:" in arch:
      d.setVar('ALLOW_EMPTY_g++', '1')
}

EXTRA_OECONF_append_e5500-64b = "${@base_contains('TCMODE', 'external-fsl', ' --disable-libgomp --disable-libssp --disable-libquadmath --enable-languages=c', '', d)}"

do_install_append() {
   ${@base_conditional('TCMODE', 'external-fsl', 'rm -fr ${D}${bindir}/*-fsl_*', '', d)}
}

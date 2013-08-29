require gdb-fsl.inc

SRC_URI += "file://sim-install-6.6.patch"

DEPENDS += "python-native flex-native bison-native"
RDEPENDS_${PN} += "python-core-native"

EXTRA_OECONF = "--disable-gdbtk --disable-tui --disable-x --disable-werror \
                --with-curses --disable-multilib --with-system-readline --disable-sim \
                ${GDBPROPREFIX} ${EXPAT} \
                ${@base_contains('DISTRO_FEATURES', 'multiarch', '--enable-64-bit-bfd', '', d)} \
                --with-python=${WORKDIR}/python \
               "

inherit python-dir

do_configure_prepend() {
cat > ${WORKDIR}/python << EOF
#! /bin/sh
case "\$2" in
        --includes) echo "-I${STAGING_INCDIR_NATIVE}/${PYTHON_DIR}/" ;;
        --ldflags) echo "-Wl,-rpath-link,${STAGING_LIBDIR_NATIVE}/.. -Wl,-rpath,${libdir}/.. -lpthread -ldl -lutil -lm -lpython${PYTHON_BASEVERSION}" ;;
        --exec-prefix) echo "${exec_prefix}/bin" ;;
        *) exit 1 ;;
esac
exit 0
EOF
        chmod +x ${WORKDIR}/python
}

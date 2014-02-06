require gdb-fsl.inc
require gdb-python.inc

DEPENDS += "flex-native bison-native"

EXTRA_OECONF = "--disable-gdbtk --disable-tui --disable-x --disable-werror \
                --with-curses --disable-multilib --with-system-readline --disable-sim \
                --without-lzma \
                ${GDBPROPREFIX} ${EXPAT} \
                ${@base_contains('DISTRO_FEATURES', 'multiarch', '--enable-64-bit-bfd', '', d)} \
                --disable-rpath "

require recipes-core/eglibc/eglibc-package.inc

INHIBIT_DEFAULT_DEPS = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

# License applies to this recipe code, not the toolchain itself
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

DEPENDS += "${@base_conditional('PREFERRED_PROVIDER_linux-libc-headers', PN, '', 'linux-libc-headers', d)}"
PROVIDES += "\
	virtual/${TARGET_PREFIX}gcc \
	virtual/${TARGET_PREFIX}g++ \
	virtual/${TARGET_PREFIX}gcc-initial \
	virtual/${TARGET_PREFIX}binutils \
	virtual/${TARGET_PREFIX}compilerlibs \
	virtual/${TARGET_PREFIX}libc-initial \
	libgcc \
	${@base_conditional('PREFERRED_PROVIDER_linux-libc-headers', PN, 'linux-libc-headers', '', d)} \
	virtual/libc virtual/libiconv virtual/libintl virtual/${TARGET_PREFIX}libc-for-gcc ${TCLIBC} \
"
S = "${EXTERNAL_TOOLCHAIN_SYSROOT}"
PV = "${FSL_VER_MAIN}"
PR = "r0"

#http://gforge.freescale.net/frs/download.php/1416/gcc-4.7.2-XMe500mc-linux-i686-linux-r817.tar.bz2
SRC_URI = "file://SUPPORTED"

do_install() {
	install -d ${D}${base_libdir}
	cp -a ${S}${base_libdir}/* ${D}${base_libdir}

	for usr_element in ${libdir} ${datadir} ${includedir}; do
		if [ -e ${S}${usr_element} ]; then
			install -d ${D}${usr_element}
			cp -a ${S}${usr_element}/* ${D}${usr_element}
		fi
	done

	if [ -e ${S}/../include ]; then
		cp -a ${S}/../include/* ${D}${includedir}
	fi

	if [ "${PREFERRED_PROVIDER_linux-libc-headers}" != "${PN}" ]; then
		for dir in linux asm asm-generic sound video rdma drm mtd; do
			rm -rf ${D}${includedir}/${dir}
		done
	fi

	install -d ${D}${bindir}
	mv ${D}${libdir}/bin/ldd ${D}${bindir}/
	rm -fr ${D}${libdir}/bin
	rm -rf ${D}${datadir}/zoneinfo
	rm -rf ${D}${libdir}/libgcc_s.so*
	rm -rf ${D}${includedir}/tirpc
	rm -rf ${D}${libdir}/libtirpc*
	rm -rf ${D}${libdir}/pkgconfig

	#fix the symlinks
	ln -sf libitm.so.1.0.0 ${D}${libdir}/libitm.so
	ln -sf libitm.so.1.0.0 ${D}${libdir}/libitm.so.1
	ln -sf libgomp.so.1.0.0 ${D}${libdir}/libgomp.so
	ln -sf libgomp.so.1.0.0 ${D}${libdir}/libgomp.so.1
	ln -sf libstdc++.so.6.0.17 ${D}${libdir}/libstdc++.so
	ln -sf libstdc++.so.6.0.17 ${D}${libdir}/libstdc++.so.6
	ln -sf libgfortran.so.3.0.0 ${D}${libdir}/libgfortran.so
	ln -sf libgfortran.so.3.0.0 ${D}${libdir}/libgfortran.so.3
	ln -sf ../..${base_libdir}/libm.so.6 ${D}${libdir}/libm.so
	ln -sf ../..${base_libdir}/librt.so.1 ${D}${libdir}/librt.so
	ln -sf ../..${base_libdir}/libdl.so.2 ${D}${libdir}/libdl.so
	ln -sf ../..${base_libdir}/libanl.so.1 ${D}${libdir}/libanl.so
	ln -sf ../..${base_libdir}/libnsl.so.1 ${D}${libdir}/libnsl.so
	ln -sf ../..${base_libdir}/libcidn.so.1 ${D}${libdir}/libcidn.so
	ln -sf ../..${base_libdir}/libutil.so.1 ${D}${libdir}/libutil.so
	ln -sf ../..${base_libdir}/libcrypt.so.1 ${D}${libdir}/libcrypt.so
	ln -sf ../..${base_libdir}/libresolv.so.2 ${D}${libdir}/libresolv.so
	ln -sf ../..${base_libdir}/libnss_db.so.2 ${D}${libdir}/libnss_db.so
	ln -sf ../..${base_libdir}/libnss_nis.so.2 ${D}${libdir}/libnss_nis.so
	ln -sf ../..${base_libdir}/libnss_dns.so.2 ${D}${libdir}/libnss_dns.so
	ln -sf ../..${base_libdir}/libnss_files.so.2 ${D}${libdir}/libnss_files.so
	ln -sf ../..${base_libdir}/libthread_db.so.1 ${D}${libdir}/libthread_db.so
	ln -sf ../..${base_libdir}/libnss_hesiod.so.2 ${D}${libdir}/libnss_hesiod.so
	ln -sf ../..${base_libdir}/libnss_compat.so.2 ${D}${libdir}/libnss_compat.so
	ln -sf ../..${base_libdir}/libnss_nisplus.so.2 ${D}${libdir}/libnss_nisplus.so
	ln -sf ../..${base_libdir}/libBrokenLocale.so.1 ${D}${libdir}/libBrokenLocale.so

	sed -i -e "s# ${base_libdir}# ../..${base_libdir}#g" -e "s# ${libdir}# .#g" ${D}${libdir}/libc.so
	sed -i -e "s# ${base_libdir}# ../..${base_libdir}#g" -e "s# ${libdir}# .#g" ${D}${libdir}/libpthread.so
}

# These files are picked up out of the sysroot by eglibc-locale, so we don't
# need to keep them around ourselves.
do_install_locale_append() {
	rm -fr ${D}${libdir}/locale
}

#fix can not find libstdc++ and libc error
SYSROOT_PREPROCESS_FUNCS += "external_fsl_toolchain_sysroot_preprocess"
external_fsl_toolchain_sysroot_preprocess() {
	dir_temp=`grep -E "libdir" ${D}${libdir}/libstdc++.la | sed "s#^libdir='##g" | sed "s#'##g"`

	install -d ${SYSROOT_DESTDIR}${dir_temp}/
	install -m 755 ${D}${libdir}/libstdc++.la ${SYSROOT_DESTDIR}${dir_temp}/
	install -m 755 ${D}${libdir}/libstdc++.so.6.0.17 ${SYSROOT_DESTDIR}${dir_temp}/
	ln -sf libstdc++.so.6.0.17 ${SYSROOT_DESTDIR}${dir_temp}/libstdc++.so

	if [ "${base_libdir}" = "/lib" ]; then
	   if [ -e ${S}/lib64 ];then
              cp -a ${S}/lib64 ${SYSROOT_DESTDIR}/
	      install -d ${SYSROOT_DESTDIR}/usr/
	      cp -a ${S}/usr/lib64 ${SYSROOT_DESTDIR}/usr/
	      sed -i -e "s# /lib64# ../../lib64#g" -e "s# /usr/lib64# .#g" ${SYSROOT_DESTDIR}/usr/lib64/libc.so
	      sed -i -e "s# /lib64# ../../lib64#g" -e "s# /usr/lib64# .#g" ${SYSROOT_DESTDIR}/usr/lib64/libpthread.so
	   fi
	fi

	install -d ${SYSROOT_DESTDIR}/usr/lib
}

PACKAGES =+ "\
          libgcc \
          libgcc-dev \
          libstdc++ \
          libstdc++-dev \
          libstdc++-staticdev \
          libgfortran \
          libgfortran-dev \
	  libgfortran-staticdev \
          libgomp \
          libgomp-dev \
          libgomp-staticdev \
          libitm \
          libitm-dev \
          libitm-staticdev \
          eglibc \
          eglibc-dev \
          eglibc-utils \
"
PACKAGES =+ "${@base_conditional('PREFERRED_PROVIDER_linux-libc-headers', PN, 'linux-libc-headers linux-libc-headers-dev', '', d)}"

ALLOW_EMPTY_eglibc-dev = "1"
ALLOW_EMPTY_eglibc-utils = "1"

INSANE_SKIP_${PN}-dbg = "staticdev"
INSANE_SKIP_libgcc += "ldflags"

PKG_${PN} = "eglibc"
PKG_${PN}-dev = "eglibc-dev"
PKG_${PN}-staticdev = "eglibc-staticdev"
PKG_${PN}-doc = "eglibc-doc"
PKG_${PN}-mtrace = "eglibc-mtrace"
PKG_${PN}-dbg = "eglibc-dbg"
PKG_${PN}-pic = "eglibc-pic"
PKG_${PN}-utils = "eglibc-utils"
PKG_${PN}-gconv = "eglibc-gconv"
PKG_${PN}-extra-nss = "eglibc-extra-nss"
PKG_${PN}-thread-db = "eglibc-thread-db"
PKG_${PN}-pcprofile = "eglibc-pcprofile"

RPROVIDES_${PN} += "${TCLIBC} libssp"
RPROVIDES_${PN}-dev += "${TCLIBC}-dev libssp-dev"
RPROVIDES_${PN}-doc += "${TCLIBC}-doc"
RPROVIDES_${PN}-dbg += "${TCLIBC}-dbg"
RPROVIDES_${PN}-pic += "${TCLIBC}-pic"
RPROVIDES_${PN}-utils += "${TCLIBC}-utils"
RPROVIDES_${PN}-gconv += "${TCLIBC}-gconv"
RPROVIDES_${PN}-mtrace += "${TCLIBC}-mtrace"
RPROVIDES_${PN}-extra-nss += "${TCLIBC}-extra-nss"
RPROVIDES_${PN}-staticdev += "${TCLIBC}-staticdev libssp-staticdev"
RPROVIDES_${PN}-thread-db += "${TCLIBC}-thread-db"
RPROVIDES_${PN}-pcprofile += "${TCLIBC}-pcprofile"

PKGV = "${FSL_VER_LIBC}"
PKGV_${PN}-dev = "${FSL_VER_LIBC}"
PKGV_${PN}-doc = "${FSL_VER_LIBC}"
PKGV_${PN}-dbg = "${FSL_VER_LIBC}"
PKGV_${PN}-pic = "${FSL_VER_LIBC}"
PKGV_${PN}-utils = "${FSL_VER_LIBC}"
PKGV_${PN}-pcprofile = "${FSL_VER_LIBC}"
PKGV_catchsegv = "${FSL_VER_LIBC}"
PKGV_libsegfault = "${FSL_VER_LIBC}"
PKGV_sln = "${FSL_VER_LIBC}"
PKGV_nscd = "${FSL_VER_LIBC}"
PKGV_ldd = "${FSL_VER_LIBC}"
PKGV_libgcc = "${FSL_VER_GCC}"
PKGV_libgcc-dev = "${FSL_VER_GCC}"
PKGV_libstdc++ = "${FSL_VER_GCC}"
PKGV_libstdc++-dev = "${FSL_VER_GCC}"
PKGV_libstdc++-staticdev = "${FSL_VER_GCC}"
PKGV_libgfortran = "${FSL_VER_GCC}"
PKGV_libgfortran-dev = "${FSL_VER_GCC}"
PKGV_libgomp = "${FSL_VER_GCC}"
PKGV_libgomp-dev = "${FSL_VER_GCC}"
PKGV_libgomp-staticdev = "${FSL_VER_GCC}"
PKGV_libitm = "${FSL_VER_GCC}"
PKGV_libitm-dev = "${FSL_VER_GCC}"
PKGV_libitm-staticdev = "${FSL_VER_GCC}"

FILES_libgcc = "${base_libdir}/libgcc_s.so.1"
FILES_libgcc-dev = "${base_libdir}/libgcc_s.so"
FILES_libstdc++ = "${libdir}/libstdc++.so.*"
FILES_libstdc++-dev = "${includedir}/c++/${PV} \
                       ${libdir}/libstdc++.so \
                       ${libdir}/libstdc++.la \
                       ${libdir}/libsupc++.la"
FILES_libstdc++-staticdev = "${libdir}/libstdc++.a ${libdir}/libsupc++.a"

FILES_libgfortran = "${libdir}/libgfortran.so.*"
FILES_libgfortran-dev = "${libdir}/libgfortran.so \
                         ${libdir}/libgfortran.la \
                         ${libdir}/libgfortran.spec \
"
FILES_libgfortran-staticdev = "${libdir}/libgfortran.a"

FILES_libgomp = "${libdir}/libgomp.so.*"
FILES_libgomp-dev = "${libdir}/libgomp.la \
                     ${libdir}/libgomp.so \
                     ${libdir}/libgomp.spec \
"
FILES_libgomp-staticdev = "${libdir}/libgomp.a"

FILES_libitm = "${libdir}/libitm.so.*"
FILES_libitm-dev = "${libdir}/libitm.so \
                    ${libdir}/libitm.la \
                    ${libdir}/libitm.spec \
"
FILES_libitm-staticdev = "${libdir}/libitm.a"

FILES_${PN} += "${libdir}/audit/sotruss-lib.so"

FSL_VER_MAIN ??= ""

python () {
    if not d.getVar("FSL_VER_MAIN"):
	raise bb.parse.SkipPackage("Freescale external toolchain not configured (FSL_VER_MAIN not set).")
}

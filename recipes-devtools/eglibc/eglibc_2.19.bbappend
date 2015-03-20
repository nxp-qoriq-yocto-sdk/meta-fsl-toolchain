SRCREV = "b661ca1b87ebd903c936b689874afd9d7dfe8e7b"
SRC_URI = "git://git.am.freescale.net/gitolite/sdk/eglibc.git;branch=eglibc-2.19;destsuffix=eglibc-${PV} \
           file://etc/ld.so.conf \
	   file://generate-supported.mk \
           file://0001-eglibc-menuconfig-support.patch \
	   file://fix-tibetian-locales.patch \
          "

EXTRA_OECONF += "--disable-multi-arch"


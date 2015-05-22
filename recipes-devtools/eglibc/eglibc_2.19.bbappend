SRCREV = "13aacd96b2b45b20212d28c7602858fd9fe507f1"
SRC_URI = "git://git.am.freescale.net/gitolite/sdk/eglibc.git;branch=eglibc-2.19;destsuffix=eglibc-${PV} \
           file://etc/ld.so.conf \
	   file://generate-supported.mk \
           file://0001-eglibc-menuconfig-support.patch \
	   file://fix-tibetian-locales.patch \
          "

EXTRA_OECONF += "--disable-multi-arch"


PV = "7.6+fsl"

SRCREV = "db3778e1ee653bd759cbfd2e53f3494a978bfee4"

SRC_URI = "git://git.am.freescale.net/gitolite/sdk/gdb.git;destsuffix=gdb-${PV} \
           file://0001-bfd.texinfo-Replace-with-when-it-is-part-of-the-text.patch \
"
FILESEXTRAPATHS_prepend := "${THISDIR}/gdb:"


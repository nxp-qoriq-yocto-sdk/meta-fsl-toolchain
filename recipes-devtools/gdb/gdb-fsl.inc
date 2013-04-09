PV = "7.5.1+fsl"

PRINC := "${@int(PRINC) + 1}"

SRCREV = "6d6a056b9884964226ea0c4417da95c03ed547c1"

SRC_URI = "git://git.am.freescale.net/gitolite/users/b32721/gdb.git;protocol=git;destsuffix=gdb-${PV}"

FILESEXTRAPATHS_prepend := "${THISDIR}/gdb:"


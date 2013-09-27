#
# Configuration to use external freescale toolchain
#

python () {
        arch = d.getVar("OVERRIDES", True)

        if "e5500-64b:" in arch or "e6500-64b:" in arch:
           d.setVar('BUILD_64BIT_KERNEL', '1')
}

EXTERNAL_TOOLCHAIN ?= "UNDEFINED"

TOOLCHAIN_PATH_ADD = "${EXTERNAL_TOOLCHAIN}/bin:"
PATH =. "${TOOLCHAIN_PATH_ADD}"

FSL_TARGET_SYS_powerpc ?= "powerpc-unknown-linux-gnu powerpc-unknown-linux-gnuspe"
FSL_TARGET_SYS_powerpc64 ?= "powerpc-unknown-linux-gnu"
FSL_TARGET_SYS = "${TARGET_SYS}"

def fsl_target_sys(d):
    toolchain_path = d.getVar('EXTERNAL_TOOLCHAIN', True)

    for triplet in d.getVar('FSL_TARGET_SYS', True).split():
        gcc = os.path.join(toolchain_path, 'bin', triplet + '-gcc')
        if os.path.exists(gcc):
            return triplet + '-'
    return '${TARGET_SYS}-'

TARGET_PREFIX = "${@fsl_target_sys(d)}"

#PREFERRED_PROVIDER_linux-libc-headers = "external-fsl-toolchain"
#PREFERRED_PROVIDER_linux-libc-headers-dev = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc-initial = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}g++ = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}binutils = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-for-gcc = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-initial = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}compilerlibs = "external-fsl-toolchain"
PREFERRED_PROVIDER_libgcc = "external-fsl-toolchain"
PREFERRED_PROVIDER_eglibc ?= "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/libc = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/libintl = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/libiconv = "external-fsl-toolchain"
PREFERRED_PROVIDER_virtual/gettext = "gettext"

# No need to re-compile the locale files
GLIBC_INTERNAL_USE_BINARY_LOCALE = "precompiled"
ENABLE_BINARY_LOCALE_GENERATION = ""

TOOLCHAIN_OPTIONS = " --sysroot=${STAGING_DIR_HOST}"

def fsl_get_sysroot(d):
    import subprocess
    sysroot_cmd = "${TARGET_PREFIX}gcc ${TARGET_CC_ARCH} -print-sysroot"
    try:
        toolchain_sysroot = bb.process.run(bb.data.expand(sysroot_cmd, d),
                                           stderr=subprocess.PIPE,
                                           env={"PATH": d.getVar('PATH', True)})[0].rstrip()
    except bb.process.CmdError as exc:
        bb.fatal(str(exc))
    else:
        return toolchain_sysroot

EXTERNAL_TOOLCHAIN_SYSROOT = "${@fsl_get_sysroot(d)}"

ERROR_QA[type] ?= "list"
python toolchain_metadata_setup () {
    import subprocess
    if not isinstance(e, bb.event.ConfigParsed):
        return

    d = e.data
    l = d.createCopy()
    l.finalize()
    oe_import(l)

    external_toolchain = l.getVar('EXTERNAL_TOOLCHAIN', True)
    if not external_toolchain or external_toolchain == 'UNDEFINED':
        bb.fatal("Error: EXTERNAL_TOOLCHAIN must be set to the path to your freescale toolchain")

    if not os.path.exists(external_toolchain):
        bb.fatal("Error: EXTERNAL_TOOLCHAIN path '%s' does not exist" % external_toolchain)

    populate_toolchain_links(l)

    # The external toolchain may not have been built with the yocto preferred
    # gnu hash setting, so ensure that the corresponding sanity check is not an error.
    error_qa = oe.data.typed_value('ERROR_QA', l)
    if 'ldflags' in error_qa:
        error_qa.remove('ldflags')
        d.setVar('ERROR_QA', ' '.join(error_qa))
}
addhandler toolchain_metadata_setup

def populate_toolchain_links(d):
    import errno
    from glob import glob

    d = d.createCopy()
    d.finalize()

    pattern = d.expand('${EXTERNAL_TOOLCHAIN}/bin/${TARGET_PREFIX}*')
    files = glob(pattern)
    if not files:
        bb.fatal("Unable to populate toolchain binary symlinks in %s" % pattern)

    bindir = d.getVar('STAGING_BINDIR_TOOLCHAIN', True)
    bb.mkdirhier(bindir)
    for f in files:
        base = os.path.basename(f)
        newpath = os.path.join(bindir, base)
        try:
            os.symlink(f, newpath)
        except OSError as exc:
            if exc.errno == errno.EEXIST:
                break
            bb.fatal("Unable to populate toolchain binary symlink for %s: %s" % (newpath, exc))

require conf/distro/include/fsl-toolchain-external-version.inc

BUILDCFG_VARS += "FSL_VER_MAIN EXTERNAL_TOOLCHAIN"

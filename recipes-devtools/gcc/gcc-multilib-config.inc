# following code modifies these definitions in the gcc config
#    MULTILIB_OPTIONS
#    MULTILIB_DIRNAMES
#    MULTILIB_OSDIRNAMES
#    GLIBC_DYNAMIC_LINKER32
#    GLIBC_DYNAMIC_LINKER64
#    GLIBC_DYNAMIC_LINKERX32
#    GLIBC_DYNAMIC_LINKERN32
#  For more information on use of these variables look at these files in the gcc source code
#    gcc/config/i386/t-linux64
#    gcc/config/mips/t-linux64
#    gcc/config/rs6000/t-linux64
#    gcc/config/i386/linux64.h
#    gcc/config/mips/linux64.h
#    gcc/config/rs6000/linux64.h

python gcc_multilib_setup() {
    import re
    import shutil
    import glob

    srcdir = d.getVar('S', True)
    builddir = d.getVar('B', True)
    src_conf_dir = '%s/gcc/config' % srcdir
    build_conf_dir = '%s/gcc/config' % builddir

    bb.utils.remove(build_conf_dir, True)
    ml_globs = ('%s/*/t-linux64' % src_conf_dir,
                '%s/*/linux64.h' % src_conf_dir,
                '%s/linux.h' % src_conf_dir)

    # copy the target multilib config files to ${B}
    for ml_glob in ml_globs:
        for fn in glob.glob(ml_glob):
            rel_path = os.path.relpath(fn, src_conf_dir)
            parent_dir = os.path.dirname(rel_path)
            bb.utils.mkdirhier('%s/%s' % (build_conf_dir, parent_dir))
            bb.utils.copyfile(fn, '%s/%s' % (build_conf_dir, rel_path))

    multilibs = (d.getVar('MULTILIB_VARIANTS', True) or '').split()
    if not multilibs:
        return

    mlprefix = d.getVar('MLPREFIX', True)
    pn = d.getVar('PN', True)
    if ('%sgcc' % mlprefix) != pn and (not pn.startswith('gcc-cross-canadian')):
        return


    def write_config(root, files, options, dirnames, osdirnames):
        for ml_conf_file in files:
            with open(root + '/' + ml_conf_file, 'r') as f:
                filelines = f.readlines()
                # recreate multilib configuration variables
                substs = [
                    (r'^(\s*(MULTILIB_OPTIONS\s*=).*)$', r'\2 %s' % '/'.join(options)),
                    (r'^(\s*MULTILIB_OPTIONS\s*\+=.*)$', ''),
                    (r'^(\s*(MULTILIB_DIRNAMES\s*=).*)$', r'\2 %s' % ' '.join(dirnames)),
                    (r'^(\s*MULTILIB_DIRNAMES\s*\+=.*)$', ''),
                    (r'^(\s*(MULTILIB_OSDIRNAMES\s*=).*)$', r'\2 %s' % ' '.join(osdirnames)),
                    (r'^(\s*MULTILIB_OSDIRNAMES\s*\+=.*)$', ''),
                ]

                for (i, line) in enumerate(filelines):
                    for subst in substs:
                        line = re.sub(subst[0], subst[1], line)
                    filelines[i] = line

                with open(root + '/' + ml_conf_file, 'w') as f:
                    f.write(''.join(filelines))

    def write_headers(root, files, libdir32, libdir64, libdirx32, libdirn32):
        def wrap_libdir(libdir):
            if libdir.find('SYSTEMLIBS_DIR') != -1:
                return libdir
            else:
                return '"/%s/"' % libdir

        for ml_conf_file in files:
            with open(root + '/' + ml_conf_file, 'r') as f:
                filelines = f.readlines()

                # replace lines like
                # #define GLIBC_DYNAMIC_LINKER32 SYSTEMLIBS_DIR "ld-linux.so.2"
                # by
                # #define GLIBC_DYNAMIC_LINKER32 "/lib/" "ld-linux.so.2"
                # this is needed to put the correct dynamic loader path in the generated binaries
                substs = [
                    (r'^(#define\s*GLIBC_DYNAMIC_LINKER32\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdir32) + r'\3'),
                    (r'^(#define\s*GLIBC_DYNAMIC_LINKER64\s*)(\S+)(\s*\"\S+\")$',
                        r'\1' + wrap_libdir(libdir64) + r'\3'),
                    (r'^(#define\s*GLIBC_DYNAMIC_LINKER64\s*\"\S+\"\s*)(\S+)(\s*\"\S+\"\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdir64) + r'\3' + wrap_libdir(libdir64) + r'\5'),
                    (r'^(#define\s*GLIBC_DYNAMIC_LINKERX32\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdirx32) + r'\3'),
                    (r'^(#define\s*GLIBC_DYNAMIC_LINKERN32\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdirn32) + r'\3'),
                    (r'^(#define\s*UCLIBC_DYNAMIC_LINKER32\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdir32) + r'\3'),
                    (r'^(#define\s*UCLIBC_DYNAMIC_LINKER64\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdir64) + r'\3'),
                    (r'^(#define\s*UCLIBC_DYNAMIC_LINKERN32\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdirn32) + r'\3'),
                    (r'^(#define\s*UCLIBC_DYNAMIC_LINKER\b\s*)(\S+)(\s*\".*\")$',
                        r'\1' + wrap_libdir(libdir32) + r'\3'),
                ]

                for (i, line) in enumerate(filelines):
                    for subst in substs:
                        line = re.sub(subst[0], subst[1], line)
                    filelines[i] = line

                with open(root + '/' + ml_conf_file, 'w') as f:
                    f.write(''.join(filelines))


    gcc_target_config_files = {
        'x86_64'    : ['gcc/config/i386/t-linux64'],
        'i586'      : ['gcc/config/i386/t-linux64'],
        'mips'      : ['gcc/config/mips/t-linux64'],
        'powerpc'   : ['gcc/config/rs6000/t-linux64'],
        'powerpc64' : ['gcc/config/rs6000/t-linux64'],
    }

    gcc_header_config_files = {
        'x86_64'    : ['gcc/config/i386/linux64.h'],
        'i586'      : ['gcc/config/i386/linux64.h'],
        'mips'      : ['gcc/config/mips/linux64.h'],
        'powerpc'   : ['gcc/config/rs6000/linux64.h'],
        'powerpc64' : ['gcc/config/rs6000/linux64.h'],
    }

    target_arch = (d.getVar('TARGET_ARCH_MULTILIB_ORIGINAL', True) if mlprefix
                    else d.getVar('TARGET_ARCH', True))
    if target_arch not in gcc_target_config_files:
        bb.warn('gcc multilib setup is not supported for TARGET_ARCH=' + target_arch)
        return

    libdir32 = 'SYSTEMLIBS_DIR'
    libdir64 = 'SYSTEMLIBS_DIR'
    libdirx32 = 'SYSTEMLIBS_DIR'
    libdirn32 = 'SYSTEMLIBS_DIR'

    target_config_files = gcc_target_config_files[target_arch]
    header_config_files = gcc_header_config_files[target_arch]

    ml_list = ['DEFAULTTUNE_MULTILIB_ORIGINAL' if mlprefix else 'DEFAULTTUNE']
    mltunes = [('DEFAULTTUNE_virtclass-multilib-%s' % ml) for ml in multilibs]
    if mlprefix:
        mlindex = 0
        for ml in multilibs:
            if mlprefix.startswith(ml):
                break
            mlindex += 1

        ml_list.extend(mltunes[:mlindex] + ['DEFAULTTUNE'] + mltunes[(mlindex + 1):])
    else:
        ml_list.extend(mltunes)

    options = []
    dirnames = []
    osdirnames = []
    optsets = []

    for ml in ml_list:
        tune = d.getVar(ml, True)
        if not tune:
            bb.warn("%s doesn't have a corresponding tune. Skipping..." % ml)
            continue
        tune_parameters = get_tune_parameters(tune, d)

        tune_baselib = tune_parameters['baselib']
        if not tune_baselib:
            bb.warn("Tune %s doesn't have a baselib set. Skipping..." % tune)
            continue

        if tune_baselib == 'lib64':
            libdir64 = tune_baselib
        elif tune_baselib == 'libx32':
            libdirx32 = tune_baselib
        elif tune_baselib == 'lib32':
            libdirn32 = tune_baselib
        elif tune_baselib == 'lib':
            libdir32 = tune_baselib
        else:
            bb.error('Unknown libdir (%s) of the tune : %s' % (tune_baselib, tune))

        # take out '-' mcpu='s and march='s from parameters
        options.append(re.sub(r'mcpu=[^ ]+ *', '',
                         re.sub(r'march=[^ ]+ *', '',
                           re.sub(r' +\-+', ' ',
                             re.sub(r'^ *\-+', '', tune_parameters['ccargs'])))))
        if tune_baselib == 'lib':
            dirnames.append('32')  # /lib => 32bit lib
        else:
            dirnames.append(tune_baselib.replace('lib', ''))
        osdirnames.append('../' + tune_baselib)

    if len(options) > 1:
        for optstr in options:
            optsets.append(optstr.split())

    #get common options present in all the tune parameters
        common_opt_set = set.intersection(*map(set, optsets))

    #common options will be added at the end of the options string only once
        if (len(common_opt_set) > 0):
            rex = re.compile(''.join(['\\b(', '|'.join(common_opt_set), ')\\W']), re.I)
            options = [rex.sub("", optstr) for optstr in options]
            options = [optstr.strip() for optstr in options]
            options[len(options)-1] = ' '.join((options[len(options)-1], ' '.join(common_opt_set)))

    write_config(builddir, target_config_files, options, dirnames, osdirnames)
    write_headers(builddir, header_config_files, libdir32, libdir64, libdirx32, libdirn32)
}

gcc_multilib_setup[cleandirs] = "${B}/gcc/config"

EXTRACONFFUNCS += "gcc_multilib_setup"

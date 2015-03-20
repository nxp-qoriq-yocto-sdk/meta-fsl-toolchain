# Specify the preferred version of toolchain
EGLIBCVERSION_qoriq-ppc = "2.19"
BINUVERSION_qoriq-ppc = "2.23.2"
GCCVERSION_qoriq-ppc = "4.9.2"
 
PREFERRED_VERSION_nativesdk-eglibc-locale_qoriq-ppc ?= "${EGLIBCVERSION}"
PREFERRED_VERSION_eglibc-mtrace_qoriq-ppc ?= "${EGLIBCVERSION}"
PREFERRED_VERSION_eglibc-scripts_qoriq-ppc ?= "${EGLIBCVERSION}"

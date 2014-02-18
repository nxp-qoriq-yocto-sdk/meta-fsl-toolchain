# Specify the preferred version of toolchain
EGLIBCVERSION = "2.15"
BINUVERSION = "2.23.2"

PREFERRED_VERSION_nativesdk-eglibc-locale   ?= "${EGLIBCVERSION}"
PREFERRED_VERSION_eglibc-mtrace   ?= "${EGLIBCVERSION}"
PREFERRED_VERSION_eglibc-scripts   ?= "${EGLIBCVERSION}"


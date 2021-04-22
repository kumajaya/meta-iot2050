# Sample application
#
# This software is a part of ISAR.
# Copyright (C) 2015-2018 ilbers GmbH

DESCRIPTION = "Perle TruePort userspace package for Debian"

PV = "6.10.0-1f86281"

SRC_URI = " \
    git://github.com/kumajaya/trueport.git;protocol=https;destsuffix=${P} \
    file://trueport-debian-userspace-no-ssl-256-devices-nostrip.patch"
SRCREV = "1f86281f61d0508b9970d09cc1f2939f333634da"

inherit dpkg

dpkg_runbuild_prepend() {
	if [ ${ISAR_CROSS_COMPILE} -eq 1 ]; then
		export DEB_BUILD_OPTIONS="nostrip"
	fi
}

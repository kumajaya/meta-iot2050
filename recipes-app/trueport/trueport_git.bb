# Sample application
#
# This software is a part of ISAR.
# Copyright (C) 2015-2018 ilbers GmbH

DESCRIPTION = "Perle TruePort userspace package for Debian"

PV = "6.10.0-240d7a2"

SRC_URI = " \
    git://github.com/kumajaya/trueport.git;protocol=https;destsuffix=${P} \
    file://trueport-debian-userspace-no-ssl-256-devices-nostrip.patch"
SRCREV = "240d7a25b7fd0a54ed093a116d6183044071d341"

inherit dpkg

dpkg_runbuild_prepend() {
	if [ ${ISAR_CROSS_COMPILE} -eq 1 ]; then
		export DEB_BUILD_OPTIONS="nostrip"
	fi
}

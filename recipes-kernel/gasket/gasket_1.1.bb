#
# Copyright (c) Siemens AG, 2021
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This file is subject to the terms and conditions of the MIT License.  See
# COPYING.MIT file in the top-level directory.
#

require recipes-kernel/linux-module/module.inc

# Replicated from https://coral.googlesource.com/linux-imx/+archive/7d368db3e6cf6d55f8f552e656e5fe85898886ce/drivers/staging/gasket.tar.gz,
# just fixing up the incorrect inclusion of linux/rwlock.h to linux/spinlock.h.
#
# Unfortunately, their nice gitiles does not generate stable archives, thus
# is useless for reproducible downloads.
SRC_URI += "file://gasket"

S = "${WORKDIR}/gasket"

dpkg_runbuild_prepend() {
    export CONFIG_STAGING_GASKET_FRAMEWORK=m
    export CONFIG_STAGING_APEX_DRIVER=m
}

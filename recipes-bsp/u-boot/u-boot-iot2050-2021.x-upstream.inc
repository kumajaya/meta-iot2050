#
# Copyright (c) Siemens AG, 2020
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#  Chao Zeng <chao.zeng@siemens.com>
#
# This file is subject to the terms and conditions of the MIT License.  See
# COPYING.MIT file in the top-level directory.
#

require u-boot-iot2050.inc

SRC_URI += " \
    https://git.ti.com/cgit/ti-u-boot/ti-u-boot/snapshot/ti-u-boot-${U_BOOT_REV}.tar.xz; \
    file://upstream/0001-arm-dts-Add-IOT2050-device-tree-files.patch \
    file://upstream/0002-board-siemens-Add-support-for-SIMATIC-IOT2050-device.patch \
    file://upstream/0003-iot2050-Add-ICSSG0-Ethernet-support.patch \
    file://upstream/0004-dts-remove-the-extra-sdhci1-dts-node.patch \
    file://upstream/0005-Add-the-function-convert-string-to-upper.patch \
    file://upstream/0006-config-add-the-CONFIG_SPL_SYSCON-configuration.patch \
    file://upstream/0007-Remove-Binman-use-its-to-generate-u-boot.patch \
    file://upstream/iot2050-uboot-ti-sdk-rules \
    "

U_BOOT_REV = "654d73f8725db340ccb470d5d130df3fcf7ce482"
U_BOOT_CONFIG = "iot2050_defconfig"
U_BOOT_BIN = "flash.bin"
#SRC_URI[sha256sum] = "e8fd05d77ef93ee47aa413b225123e56153144dac7b14b6fa9452899906e62da"
S = "${WORKDIR}/ti-u-boot-${U_BOOT_REV}"

SPI_FLASH_IMG = "${U_BOOT_BIN}"
SPI_FLASH_DEPLOY_IMG = "iot2050-image-boot.bin"

DEPENDS += "trusted-firmware-a-iot2050 optee-os-iot2050"
DEBIAN_BUILD_DEPENDS =. "trusted-firmware-a-iot2050, optee-os-iot2050, \
    swig:native, python3-dev:native, python3-pkg-resources,"

#do_prepare_build_append() {
#    cd ${S}
#    if [ ${SOC_VERSION} = "sr1" ]; then
#        ln -sf ../prebuild/prufw_sr1/* ${S}
#        ln -sf ../prebuild/sysfw_sr1/* ${S}
#    elif [ ${SOC_VERSION} = "sr2" ]; then
#        ln -sf ../prebuild/prufw_sr2/* ${S}
#        ln -sf ../prebuild/sysfw_sr2/* ${S}
#    fi
#}

dpkg_runbuild_prepend() {
    export ATF=/usr/lib/trusted-firmware-a/iot2050/bl31.bin
    export TEE=/usr/lib/optee-os/iot2050/tee-pager_v2.bin
    export IOT2050_VARIANT=${IOT2050_VARIANT}
    export SPI_FLASH_IMG=${SPI_FLASH_IMG}
    export SPI_FLASH_SIZE_KB=${SPI_FLASH_SIZE_KB}
}

do_prepare_build_append() {
    cp ${WORKDIR}/upstream/iot2050-uboot-ti-sdk-rules ${S}/debian/rules
}
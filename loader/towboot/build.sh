#!/bin/bash

readonly CONST_TOWBOOT_VERSION="0.3.0"
readonly CONST_PART_SECTORS="20480"

if [[ ! -f "towboot-ia32.efi" || ! -f "towboot-x64.efi" ]]; then
  wget -O towboot-ia32.efi "https://github.com/hhuOS/towboot/releases/download/v${CONST_TOWBOOT_VERSION}/towboot-v${CONST_TOWBOOT_VERSION}-i686.efi"
  wget -O towboot-x64.efi "https://github.com/hhuOS/towboot/releases/download/v${CONST_TOWBOOT_VERSION}/towboot-v${CONST_TOWBOOT_VERSION}-x86_64.efi"
fi

mformat -i part.img -C -T ${CONST_PART_SECTORS} -h 1 -s ${CONST_PART_SECTORS}
mmd -i part.img efi
mmd -i part.img efi/boot
mcopy -i part.img towboot-ia32.efi ::efi/boot/bootia32.efi
mcopy -i part.img towboot-x64.efi ::efi/boot/bootx64.efi
mcopy -i part.img towboot.toml ::
mcopy -i part.img hhuOS.bin ::
mcopy -i part.img hhuOS.initrd ::

fallocate -l 1M fill.img
cat fill.img part.img fill.img > hhuOS.img
echo -e "g\\nn\\n1\\n2048\\n+${CONST_PART_SECTORS}\\nt\\n1\\nw\\n" | fdisk hhuOS.img

rm fill.img part.img

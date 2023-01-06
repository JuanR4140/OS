{ pkgs }: {
    deps = [
        pkgs.bchunk
        pkgs.mdf2iso
        pkgs.nasm
        pkgs.bochs
        pkgs.qemu
        pkgs.hexdump
        pkgs.gdb-multitarget
    ];
}

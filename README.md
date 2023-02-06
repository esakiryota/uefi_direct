## 使用コマンド
```
$ make
$ qemu-system-x86_64 -bios OVMF.fd -drive file=fat:rw:image,media=disk,format=raw
```

## エラーパターン
# no file or directory: objcopyの場合
binutilslへのpathが通っていない
```
$ export PATH=/opt/homebrew/sbin:/opt/homebrew/opt/binutils/bin:$PATH 
```


## MakeFile 
# 最初のMakefile
 ```
 CC = x86_64-w64-mingw32-gcc
CFLAGS = -shared -nostdlib -mno-red-zone -fno-stack-protector -Wall \
         -e EfiMain

all: main.efi

%.efi: %.dll
	objcopy --target=efi-app-x86_64 $< $@

%.dll: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu: main.efi OVMF.fd image/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -nographic -bios OVMF.fd -drive file=fat:rw:image,media=disk,format=raw

image/EFI/BOOT/BOOTX64.EFI:
	mkdir -p image/EFI/BOOT
	ln -sf ../../../main.efi image/EFI/BOOT/BOOTX64.EFI

OVMF.fd:
	wget http://downloads.sourceforge.net/project/edk2/OVMF/OVMF-X64-r15214.zip
	unzip OVMF-X64-r15214.zip OVMF.fd

clean:
	rm -f main.efi

 ```


 ## QEMU 終了方法
 ctl+opt+g

 ## メモ
 ・-nographic をはずした。->結局動いた
 ・マウス処理はqemuでは認識しない

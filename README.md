# shade-os
a bad os that does not work that well

### Building from source
This is tested on Artix/Arch Linux, therefore you will figure it out if your on another distrobution.
1) Install packages.
```
sudo pacman -S grub base-devel git nasm qemu make zip unzip wget
```
2) Clone repo.
```
git clone https://github.com/c0repwn3r/shade-os.git
cd shade-os
```
3) Download required files.
```
./download_dependencies.sh
```
4) Build.
```
make build-x86_64
```
5) Run.
```
make test
```

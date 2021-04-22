# shade-os
a bad os that does not work that well

### Building from source
This is tested on Artix/Arch Linux, therefore you will figure it out if your on another distrobution.

**Does-not-know-what-a-terminal-is experience tutorial:**
Go install linux. Learn how to use it.

**Knows-how-to-open-a-terminal experienced tutorial:**
Paste this into your favorite terminal. Modify for your linux install. Always be careful when pasting walls of text from the internet.
```
sudo pacman -S --needed grub base-devel git nasm qemu make zip unzip wget xorriso mtools;git clone https://github.com/c0repwn3r/shade-os.git;cd shade-os;./download_dependencies.sh;make build-x86_64;make test
```

**Semi-experienced tutorial:**
1) Install packages.
```
sudo pacman -S --needed grub base-devel git nasm qemu make zip unzip wget xorriso mtools
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

**Already a developer tutorial:**
Install grub, base-devel, git, nasm, qemu, make, zip, unzip, wget, and xorriso. Package names for Arch/Artix.
Clone repo, run ./download_dependencies, make build-x86_64. Test with make test.

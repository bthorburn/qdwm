
# qdwm - My personal DWM build, patched for QubesOS

qdwm is just a standard clone of dwm which has been modified with qubes os patches and others, as well as changes to the directory structure for easier future modification.

The following instructions assume you are using an up-to-date version of QubesOS.

## Installation
Identify the ditribution of dom0. This could be Fedora 38 or Fedora 39 for example.

Create a new standalone qube named 'dwmbuild' which uses the same ditro as dom0.

If you can't already see the distro in your templates, you can likley find and install it by running the following command in dom0:
```bash
qvm-template-gui
```
Install dependencies for building dwm on your selected ditro. This is not qubes specific.

Navigate to the cloned directory and execute the following command.
```bash
sudo make clean dwm
```
- You just need the dwm binary, you don't want to install dwm to this standalone.

Given a successful build, go ahead and copy the dwm binary to dom0. This can be done from within dom0 using the following command:
```bash 
qvm-run --pass-io <svm> 'cat <path to dwm binary>' > /tmp/dwm
```
An example being:
```bash
qvm-run --pass-io dwmbuild 'cat /home/user/suckless/dwm/dwm' > /tmp/dwm
```
Make sure to copy the binary dwm, not the folder also named dwm. (This should error if you try to copy an uncompressed directory anyway)

Now just run the following in dom0, these should be self explanitory:
```bash
cd /usr/local/bin &&
sudo mv /tmp/dwm ./ &&
sudo chmod 755 dwm
```

You're good to go. Almost!

Just disable lightdm and stop in dom0:

```bash 
sudo systemctl disbale lightdm && sudo systemctl stop lightdm
```
This will result in a disabled lightdm on the next boot and will exit you out of your currect desktop env. Just log back in via the terminal and run:

```bash 
startx /usr/local/bin/dwm
```


### Why not just build dwm directly in dom0?

For those still unfamiliar with Qubes please read over their docs and forums. Qubes OS may be a complex piece of software, but it's not all to difficult to learn with some time and interest!

From your research, you will hopefully see that installing software to dom0 is not considared very 'qube-ist'. 

Using a standalone VM for building dwm is a wise approch,and a standalone mitagates some issues.

- Carelessly installing and building software to dom0 is not advisiable from a security persepective. A standalone qube mitagates this issue.

- Stange versioning errors are less likely to occur due to the distributions matching.

- You could got one step further and build offline, and clone this repo over TOR if you want.





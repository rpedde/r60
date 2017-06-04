r60 keyboard firmware
======================

## Ugh

I didn't really want to carry around a fork of QMK, and I wanted the
firmware in this repo, but I did build this with QMK.

Get qmk from https://github.com/qmk/qmk_firwmare

Check out rev aaa67f, link this directory as "r60" in keyboards, and
then make from the linked directory.  A r60_default.hex should appear
in the root of the qmk directory.

### Default

To build with the default keymap, simply run `make default`.

### Other Keymaps

Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create a folder with the name of your keymap in the keymaps folder, and see keymap documentation (you can find in top readme.md) and existant keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.

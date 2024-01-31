# Software

## Symlinks

To enable symlinks on windows must:
- Enable developer mode on windows by searching for developer mode in settings (so symlinks can be made without admin rights)
- Enable symlinks in git
```bash
git config --global core.symlinks true
```

To create a new symlink:
- In sketch directory (folder with .ino file)
```bash
cmd.exe /c mklink /d src ..\common
```
- Name src/ is essential for Arduino IDE to compile source files

To remove a symlink:
```bash
cmd.exe /c rmdir src
```

- Any questions please ask Jon 'the Goat' Tindal

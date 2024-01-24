# Software

## Symlinks

To enable symlinks on windows must:
- Enable developer mode on windows (search for developer mode in settings) (so symlinks can be made without admin rights)
- Enable symlinks in git (git config --global core.symlinks true)

To create a new symlink:
- In sketch directory (folder with .ino file)
- mklink /d src ..\common
- Name src/ is essential for Arduino IDE to compile source files
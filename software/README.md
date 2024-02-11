# Software

## Arduino Libraries

Required Arduino libraries:
- Servo by Michael Margolis, Arduino Version 1.2.1
- Adafruit Motor Shield V2 Library by Adafruit Version 1.1.3
- Ticker by Stefan Staub Version 4.4.0

Install libraries using the Arduino IDE, under Tools -> Manage Libraries...

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

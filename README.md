Metapipe
========
It's about the things you don't say!

Metapipe measures the time between your keystrokes and translates them into
bytes which are piped out to `STDERR` while your input goes to `STDOUT`. So
you can compose two inputs at once.

Usage
-----
```
$ metapipe [-abmhlv] [-n MSECS]
```

Options
-------
* `-n` Set keystroke threshold (milliseconds)
* `-a` Set 7-bit ASCII output mode (default)
* `-b` Set 8-bit byte output mode
* `-m` Set morse code output mode
* `-h` Show usage information
* `-l` Show license
* `-v` Show version

License
-------
Licensed under the terms of the [MIT License](LICENSE).
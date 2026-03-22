
Terminal to experiment with some devices using some ports, like serial port.

[[_TOC_]]

# Introduction

For some cases, we have to interact with a device.

Some uses [RS-232 serial ports](https://en.wikipedia.org/wiki/RS-232),
other [USBTMC](https://www.usb.org/document-library/test-measurement-class-specification),
and many more.

Before we can write our application,
it's handy to use a terminal to get familiar with the device command interface.

There are a lot of terminal application that can communicate via RS232 serial port.
Maybe not so much for USB-TMC.
Also, some old devices are very slow,
and don't work if we send bytes at the normal predefined rate
(they must be sent one by one with some ms interval).

# Getting started

There are currently no prebuilt packages available.

To build the project from source, see the [BUILD](BUILD.md) documentation.

On some systems, like Linux Ubuntu, accessing serial ports is probably not allowed by default.
To access serial ports, you probably have to be in the `dialout` group.
To check what groups are currently affected to your login user:
```shell
groups
```

To add you to the `dialout` group:
```shell
sudo adduser <user> dialout
```

# Status

Currently, I only work on RS-232 serial port.

# Existing projects

- https://github.com/Duolabs/SerialTool
- https://realterm.sourceforge.io/

# UUM

## Compiling

### Build dependencies

#### A `c` compiler

This project is designed to use use standard library functions, not gnu extentions. This project can be compiled with gcc or clang. Glibc or MUSL can be used.

#### meson && ninja

The `meson` and `ninja` packages are used to build this program. Any required libraries are resolved by meson.

### Runtime dependencies

#### Curses

This program is built around the curses libraries. Compatablility is only gaurenteed when using `PDCurses` or `ncurses`, but any proper library should work fine.

### Compiling instructions

This project can be cloned with git, or a compressed archive may be downloaded with `curl` or `wget`

```bash
# git
git clone https://github.com/el-wumbus/UsageMonitor.git 

# curl
curl -Lo UsageMonitor.zip https://github.com/el-wumbus/UsageMonitor/archive/refs/heads/master.zip

# wget
wget -o UsageMonitor.zip https://github.com/el-wumbus/UsageMonitor/archive/refs/heads/master.zip
```

Compressed `zip` archives can be decompressed with `unzip`.

```bash
unzip -x UsageMonitor.zip
# output should be in `./UsageMonitor-master`
```

## Features

* [ ] Cpu Usage calculation
    * [ ] Calculate cpu usage on another thread
    * [x] Calculate cpu usage function

* [x] Cpu model
* [ ] Core and thread count
    * [x] Core count
    * [ ] Thread count
* [x] Memory Utilization info
    * [x] Used
    * [x] Availiable
    * [x] Total
* [x] Uptime info
    * [x] uptime
    * [x] idletime



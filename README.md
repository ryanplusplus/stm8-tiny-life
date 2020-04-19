# stm8-tiny-life
Conway's game of life using an LED matrix and an STM8S103F3P6.

## Setup
- Copy `tools/Linux/udev/70-st-link.rules` to `/etc/udev/` and run `udevadm control --reload-rules`.

## Use
### Compile
```shell
make -f <target>.mk
```

### Clean
```shell
make -f <target>.mk clean
```

### Erase via SWIM
```shell
make -f <target>.mk erase
```

### Flash via SWIM
```shell
make -f <target>.mk upload
```


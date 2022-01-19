# rpi-dbus-test
Raspberry Pi Dbus Test
- Target: Raspberry PI 4 Model B
- OS: Raspberry Pi OS (32-bit)

Note that I included dbus include and *.so in this repository which is not a good practice typically.
In practice, I would add external dependencies to a conan package and store in Artifactory.

## dbus-test
Simple example from https://github.com/makercrew/dbus-sample/blob/master/dbus.cpp

`conan install . --install-folder build-raspberry-armv7 -pr=raspberrypi-arm7`

`conan build . --build-folder build-raspberry-armv7`

## dbus-test2
Simple example from http://www.matthew.ath.cx/projects.git/dbus-example.c.

### Build
`conan install . --install-folder build-raspberry-armv7 -pr=raspberrypi-arm7`

`conan build . --build-folder build-raspberry-armv7`

### Install
- copy `com.echozulucode.conf` to /etc/dbus-1/system.d/
- copy <application> to /<install-path>
- `chmod +x /<install-path>/<application>`

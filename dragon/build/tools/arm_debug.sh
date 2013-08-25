#!/bin/sh
#

# start debug

#adb push $ANDROID_NDK_ROOT/prebuilt/android-arm/gdbserver/gdbserver /data

#adb shell gdbserver :12345 /data/data/myapp

#adb forward tcp:12345 tcp:12345

#$ANDROID_NDK_ROOT/toolchains/arm-linux-androideabi-4.4.3/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gdb --eval-command="set solib-search-path ./debugging/lib" --eval-command="file ./dragon3d-examples" --eval-command="target remote :12345"
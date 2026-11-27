# Microphone stream sample

This sample opens the system-selected microphone for a signed-in user, reads
signed 16-bit mono PCM, and prints signal levels, silence state, and dropped
frame counts. Toggle the DualSense MUTE button during capture to observe the
system's silence state. The selected input may be a headset or USB microphone
instead of the DualSense built-in microphone.

Build the SDK and install it, then build the sample:

```sh
make
sudo make install DESTDIR=/opt/ps5-payload-sdk
make -C samples/microphone_stream PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
```

Link homebrew title consumers with `-lps5microphone -lSceAudioIn -lSceUserService
-lpthread`. The AudioIn capture API requires a user id from UserService and an
application title context. Sending this ELF directly through `ps5-payload-elfldr`
does not provide an application identity and can make `sceAudioInOpen` fail
with `0x809b0081`; that payload-only failure does not imply capture is
unavailable to a homebrew title. Package this code in a title and launch it
through the console's homebrew title loader to test live audio.

The silence bitmask is firmware-dependent diagnostic data rather than a public
Sony API contract. Record the console model, firmware, selected input device,
controller connection mode, and mute transitions when reporting results.

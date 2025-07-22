- [x] CMake
- [ ] Integrate forked pxtone library (for bugfixes and big-endian, needs updating and cmake adaptation; https://github.com/ewancg/pxtone)
- [ ] Cross-platform windowing (SDL)
- [ ] Cross-platform audio (TBD: probably miniaudio)

Pixel's desired changes (translated):
```
"In fact, there are many things that should be done, but are not.

-Insufficient copy/paste functionality (not even file-to-file copy...)
-Multiple simultaneous startups (easy to implement, but more functions are needed at once)
-Color coding of tracks
-“Tone preset” function
-Volume changes need to be smooth ( noise will occur if not careful )

Current(?) I used to manage lists and priorities like this back in the day... 🙃."
```
A tone preset can be understood as a group of instruments that you can load at the same time

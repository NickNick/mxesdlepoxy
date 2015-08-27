# mxesdlepoxy
This reproduces the issue I raised with SDL + Epoxy + MXE static build at https://github.com/anholt/libepoxy/issues/67

It works fine natively under linux, but when I compile with mxe (static stuff) I get a segfault because wglGetProcAddress can't find glGenTextures

```
nick@fusrodah:~/code/sdl-epoxy(master % u=)/build-mxe%$ WINEDEBUG=warn+wgl wine sdl_epoxy.exe 
wine: cannot find L"C:\\windows\\system32\\winemenubuilder.exe"
err:wineboot:ProcessRunKeys Error running cmd L"C:\\windows\\system32\\winemenubuilder.exe -a -r" (2)
Wine cannot find the ncurses library (libncursesw.so.5).
err:module:load_builtin_dll failed to load .so lib for builtin L"winemp3.acm": libmpg123.so.0: cannot open shared object file: No such file or directory
fixme:ole:RemUnknown_QueryInterface No interface for iid {00000019-0000-0000-c000-000000000046}
fixme:win:EnumDisplayDevicesW ((null),0,0x155f880,0x00000000), stub!
fixme:win:EnumDisplayDevicesW (L"\\\\.\\DISPLAY1",0,0x155f880,0x00000000), stub!
fixme:win:EnumDisplayDevicesW (L"\\\\.\\DISPLAY1",0,0x155f3e8,0x00000000), stub!
fixme:win:EnumDisplayDevicesW (L"\\\\.\\DISPLAY1",1,0x155f880,0x00000000), stub!
fixme:win:EnumDisplayDevicesW ((null),1,0x155f880,0x00000000), stub!
fixme:win:EnumDisplayDevicesW ((null),0,0x155f880,0x00000000), stub!
fixme:win:EnumDisplayDevicesW ((null),1,0x155f880,0x00000000), stub!
fixme:win:RegisterDeviceNotificationW (hwnd=0x1004c, filter=0x1c6e93c,flags=0x00000000) returns a fake device notification handle!
../sdl_epoxy.cpp:  44(           main): Creating window sized 200 x 200
fixme:win:RegisterTouchWindow (0x1004e 00000003): stub
fixme:wgl:X11DRV_wglChoosePixelFormatARB unused pfAttribFList
fixme:imm:ImmReleaseContext (0x1004e, 0x143a40): stub
fixme:ole:CoCreateInstance no instance created for interface {3e90ade3-7594-4cb0-bb58-69628f5f458c} of class {529a9e6b-6587-4f23-ab9e-9c7d683e3c50}, hres is 0x80004002
fixme:imm:NotifyIME NI_CLOSECANDIDATE
../sdl_epoxy.cpp:  56(           main): Succesfully created window
../sdl_epoxy.cpp:  70(           main): 33
../sdl_epoxy.cpp:  71(           main): 1
warn:wgl:wglGetProcAddress Function glGenTextures unknown
wine: Unhandled page fault on read access to 0x00000000 at address (nil) (thread 0009), starting debugger...
^CCtrl-C: stopping debuggee
fixme:console:CONSOLE_DefaultHandler Terminating process 29 on event 0
✗ - status code 84 
```



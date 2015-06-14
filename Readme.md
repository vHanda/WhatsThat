WhatsThat
---------

WhatsThat is a C++ library to communicate with web.whatsapp.com. It operates by
running a chromium webbrowser in the background, running the website, and
interacting through the website via websockets and jquery. This is then translated
into a C++ API providing higer level interaciton.

This library relies on QtWebEngine 5.5

How to Build
------------
$ mkdir build
$ cd build
$ cmake ../ -DCMAKE_INSTALL_PREFIX=prefix
$ make && make install

Testing it out
--------------

WhatsThat ships with a CLI tool called `whatsthat`.



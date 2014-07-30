About kgocode
=============

Description
-----------
    
[kgocode][1] is a plugin for KTextEditor (Kate, KDevelop, among others) that provides basic code completion for
the Go programming language. Uses [gocode][2] as completion provider.

Dependencies
------------

KTextEditor libraries and [gocode][2].
Uses CMake as build tool.

Install
-------

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr ..
    $ make
    # make install

License
-------

GPLv3+.

Contact
-----------

Lucas Hermann Negri - lucashnegri@gmail.com

[1]: https://bitbucket.org/lucashnegri/kgocode
[2]: https://github.com/nsf/gocode

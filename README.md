CustomView
============

Customize your Sylpheed user interface.

This plugin supports to customize Sylpheed user interface
such as two pane view.

Supported Features
------------------

* Two column layout
  It shows summaryview and messageview only.
  This layout is suitable for wide display such as HD (1366 x 768)

Requirement
-----------

* Ubuntu 12.04 or later
* Sylpheed 3.4.0 or later.

Install
-------

```
% git clone git://github.com/kenhys/sylpheed-customview.git
% cd sylpheed-customview
% ./autogen.sh
% ./configure --sylpheed-build-dir=/path/to/sylpheed_source_dir
% make
% make install
```

Usage
-----

Configure customviewrc placed at $HOME/.sylpheed-2.0/.

```
[customview]
hide-folderview=true
```

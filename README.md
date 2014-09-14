QtWaitingSpinner
================

QtWaitingSpinner is a configurable custom Qt widget for showing a "waiting" or "loading" spinner icon.

Configuration
================

Some spinners with different configurations: 

![waiting spinner](https://github.com/goblincoding/QtWaitingSpinner/blob/gh-pages/waiting-spinners.gif)

The following configuration options are available:

* Colour
* "Roundness"
* Speed (rotations per second)
* The number of radial lines to be drawn
* The length of the radial lines
* The width of the widget
* The radius of the widget
* The length of the "trail" or "fade"
* Opacity

Usage
==========

Despite being highly configurable, QtWaitingSpinner is extremely easy to use and the defaults generally do a pretty good job.

The example below will create a spinner that (1) blocks all user input to the main application for as long as the spinner is active, (2) automatically centres itself on its parent widget every time "start" is called and (3) makes use of the default settings.

```
	QtWaitingSpinner* spinner = new QtWaitingSpinner(this, Qt::ApplicationModal, true);
	spinner->start(); // starts spinning
```

(the configuration options mentioned above can be set via the various mutators)

Thanks
======

QtWaitingSpinner was inspired by the [spin.js](http://fgnass.github.io/spin.js/)  project.

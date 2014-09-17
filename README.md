QtWaitingSpinner
================

QtWaitingSpinner is a configurable custom Qt widget for showing a "waiting" or "loading" spinner icon.

###Configuration

Some spinners with different configurations: 

![waiting spinner](https://github.com/goblincoding/QtWaitingSpinner/blob/gh-pages/waiting-spinners.gif)

The following configuration options are available:

* Colour
* "Roundness" of the lines
* Speed (rotations per second)
* Number of lines to be drawn
* Line length
* Line width
* Radius of the spinner's "dead space" or inner circle
* The percentage fade the "trail"
* The minimum opacity of the "trail"

###Usage

Despite being highly configurable, "QtWaitingSpinner" is extremely easy to use and, to make things even easier, "QtWaitingSpinnerTest" can assist you in determining the exact shape, size and colour configuration you'd like your spinner to have.

As an easy reference example, the code below will create a spinner that (1) blocks all user input to the main application for as long as the spinner is active, (2) automatically centres itself on its parent widget every time "start" is called and (3) makes use of the default shape, size and colour settings.

```
	QtWaitingSpinner* spinner = new QtWaitingSpinner(this, Qt::ApplicationModal, true);
	spinner->start(); // starts spinning
```

###Thanks

QtWaitingSpinner was inspired by the [spin.js](http://fgnass.github.io/spin.js/)  project.

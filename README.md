QtWaitingSpinner
================

This is configurable custom Qt widget for showing waiting spinner icon. If you're looking for somewhat like loading icon, implemented as Qt widget, you're in the right place.

How does it look?
=============

Some spinners with different parameters: 

![waiting spinner](https://raw.github.com/snowwlex/QtWaitingSpinner/gh-pages/waiting-spinners.gif)

Configuration
================

Following parameters can be used for configuration:

*   Main
  *   Number of lines
  *   Length of lines
  *   Width of lines
  *   Radius of circle
*   Additional 
  *   "Roundness" 
  *   Color 
  *   Speed (in rounds per second)
  *   "Trail" parameter
  *   Opacity
  
Code usage
==========

Minimum code that is needed to write for using spinner:
```
	QtWaitingSpinner* spinner = new QtWaitingSpinner(10,7,3,5);
	spinner->start(); // starts spinning
```

Main parameters are setted in constructor. This is a widget, that can be placed anywhere.

Main and additional parameters can be setted like that:
```
  spinner->setLinesNumber(10);
  spinner->setSpeed(1.5);
  spinner->setColor(QColor(255,0,0));
```

For example:
```
	QVBoxLayout *layout = new QVBoxLayout;
	QtWaitingSpinner* spinner = new QtWaitingSpinner(10,7,3,5);
	spinner->setSpeed(1.5);
	layout->addWidget(spinner);
	setLayout(layout);
	spinner->start();
```

Thanks
======

The spinner is inspired by [spin.js](http://fgnass.github.io/spin.js/)  project. 

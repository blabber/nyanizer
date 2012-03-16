nyanizer
========

Description
-----------

This is a small tool to nyanize pictures. It uses the MagickWand API for
ImageMagick to read a picture and then iterates the pixels of the picture. The
saturation of every pixel is raised to the maximum and the hue is increased
every row in a way that you get a full color cycle over the whole image.

License
-------

The example image is taken from
[here](https://de.wikipedia.org/w/index.php?title=Datei:Burma_creme.JPG).  It
has been published by Linda Andersson under the [CC BY-SA 3.0
License](https://creativecommons.org/licenses/by-sa/3.0/).

The nyanizer itself is licensed under the beerware license (see the header of the source).

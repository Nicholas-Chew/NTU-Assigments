## Introduction
Pixels for each frame of a video are streamed through the system (VmodCAM - Digilent) serially,
ordered according to raster scan format. Pixel colour is typically represented as red, green, and
blue components, RGB. Hence, each pixel has a value for each of the three components, and
these taken together determine the colour for that pixel. Other colourspaces exist. You may be
familiar with the CMYK colourspace used in print publishing, where four (additive) components,
cyan, magenta, yellow, and black are combined to create any colour. Another alternative is the
YUV colourspace, that better takes human vision into account. Here, they Y represents the
luminance, or brightness of a pixel, and is equivalent to the black-and-white representation of an
image. The U and V components are colour difference signals that encode colour information.

Conversion between colourspaces can be done using a matrix multiplication. For RGB to
YUV, the following is used:

![RGB To CYMK Conversion Formula](/RGBToCYMK.jpg?raw=true "RGB To CYMK Conversion Formula")

It turns out that detecting skin colour in the YUV colourspace is more efficient. In this lab,
we will convert RGB signals from a camera to YUV, determine skin pixels, then apply a colour
shift.

## About this project
This Project Features a 5-stage pipelined RGB to CMYK conversion using Verilog Design. It also features basic image filtering techniques.
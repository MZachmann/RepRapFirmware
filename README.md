# Changes in the Fork - the Screwmap_Z Branch
This adds code to perform multi-axis screwmapping.
This is a piecewise-linear transformation of the input coordinates to repair physical errors in software
In particular, this repairs, in software, errors due to:
 1) Non-linearities in a ballscrew or leadscrew drive
 2) Linear rails which are not straight and flat
 3) Linear rails which are not parallel
 4) A bed which is tilted or bowed or twisted or ...
Documentation is in src/Movement/Kinematics/Screwmap.h
#
# Original Readme
This is firmware for controlling 3D printers and related devices using electronics based on ARM Cortex main processors. The current processors supported are the ATSAM4E, ATSAM4S, SAME70 and SAME5x. There is a fork of this firmware that supports LPC1768/1769 and STM processors.

# Documentation
All documentation has been moved to the [RepRapFirmware GitHub Wiki](https://github.com/Duet3D/RepRapFirmware/wiki).

# Licence
The source files in this project (RepRapFirmware) are licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html. The associated CoreNG project, which provides a partial hardware abstraction layer, includes files derived from the Advanced Software Framework (formerly Atmel Software Framework) from Microchip. Those files have a more restrictive license, in particular they may only be used for code that targets Atmel/Microchip processors.

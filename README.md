# Changes in the Fork - the Screwmap_Z Branch
This adds code to perform multi-axis screwmapping. That is a transform of all or some of the entire machining volume
that repairs physical machine defects in software.

The syntax seems wordy but makes it very simple to set single node values on the fly and to create gcode macro files that define the entire screwmap transformation array. The design uses as few resources (RAM and CPU) as possible.

Four M-codes are added to let the user define piecewise-linear transformations of the input coordinates to repair physical errors.

The following errors can be repaired in software:
 1) Non-linearities in a ballscrew or leadscrew drive
 2) Linear rails which are not straight and flat
 3) Linear rails which are not parallel
 4) A bed which is tilted or bowed or twisted or
 5) A rack and pinion where the rack is not linear

**Screwmap Documentation is in src/Movement/Kinematics/Screwmap.cpp**
#
# Original Readme
This is firmware for controlling 3D printers and related devices using electronics based on ARM Cortex main processors. The current processors supported are the ATSAM4E, ATSAM4S, SAME70 and SAME5x. There is a fork of this firmware that supports LPC1768/1769 and STM processors.

# Documentation
All documentation has been moved to the [RepRapFirmware GitHub Wiki](https://github.com/Duet3D/RepRapFirmware/wiki).

# Licence
The source files in this project (RepRapFirmware) are licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html. The associated CoreNG project, which provides a partial hardware abstraction layer, includes files derived from the Advanced Software Framework (formerly Atmel Software Framework) from Microchip. Those files have a more restrictive license, in particular they may only be used for code that targets Atmel/Microchip processors.

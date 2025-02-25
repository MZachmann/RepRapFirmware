These examples are actual screw map files. The first-tested precision part of the CNC is the 16x16" square on the left where the bed clamps start.

Each SetnScrewMap file defines a 2d vector for a piecewise-linear machine coordinate transform. The entry values are the -error terms to apply based on the axis coordinate to compensate for the error. If your limit switches move just change the start coordinate. Errors terms are assumed to be small relative to the overall dynamic range.

The config.g system file has these lines to support the screwmap:

```
; create and enable the screw maps to compensate for the rail nonlinearity
M98 P"0:/macros/SetXScrewMap.g"
M98 P"0:/macros/SetYScrewMap.g"
```


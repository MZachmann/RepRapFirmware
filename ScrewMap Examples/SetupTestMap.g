; create a screwmap X->XY with 3 entries starting at X=50mm (machine posn) with interval 100mm
m641 R"X" A"XY" S50 I100 N3
; a device that has bad (and weird) linearity issues in the range 50-250
m642 R"X" X0:0.1:0
; enable
m640 S1

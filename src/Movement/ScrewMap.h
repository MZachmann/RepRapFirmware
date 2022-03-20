/*
 * ScrewMap.h
 *
 *  Created on: 11 Dec 2020
 *      Author: MarkZ
 */

#ifndef SCREWMAP_H_
#define SCREWMAP_H_

#include "RepRapFirmware.h"

struct ScrewMapInfo
 {
	bool enable;				// manual disable maps
	uint8_t count;				// # of entries
	float start;				// Starting coordinate
	float increment;			// Grid size
	float* mapTable = nullptr;	// Allocated #floats == count*subaxes (nullptr == disabled)
	// helpers
	inline bool IsEnabled() const 	{ return enable && (mapTable != nullptr); }			// is this maptable in use?
	inline void SetEnabled(bool b) 	{ enable = b; }										// set manual enable bit
	inline float End() const 		{ return start + increment * (count-1); }			// end coordinate (calculated)
	inline int IndexOf(float coord) const { return (int)((coord - smi.start) / smi.increment);}		// index of coordinate (not clipped)
 };

 class ScrewMap
 {
 public:
	ScrewMap();
	void ClearAllMaps();	// delete any maps and disable mapping all axes
	bool InitScrewMap(ScrewMapInfo&info, float start, float increment, int count);		// allocate a default table and enable the map
	void Transform(float xyzPoint[MaxAxes], const Tool *tool);							// convert all axes
	void InverseTransform(float xyzPoint[MaxAxes], const Tool *tool);					// unconvert all axes
 	bool LoadFromFile(FileStore *f, const char* fname, const StringRef& r);				// load
 	bool SaveToFile(FileStore *f, const char* fname, const StringRef& r);				// save

 private:
	static void ClearMap(ScrewMapInfo* psmi);
	void TransformAxis(float xyzPoint[MaxAxes], int axis) const;
	void InverseTransformAxis(float xyzPoint[MaxAxes], int axis) const;
	static float TransformCoord(float coord, const ScrewMapInfo& smi);
	static float InverseTransformCoord(float coord, const ScrewMapInfo& smi);
	ScrewMapInfo screwInfos[MaxAxes];
 };

 #endif

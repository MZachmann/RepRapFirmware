/*
 * ScrewMap.cpp
 *
 *  Created on: 11 Dec 2020
 *      Author: MarkZ
 */

#include "ScrewMap.h"

#define assert(x)

#define TESTING_SCREW_MAP 1

ScrewMap::ScrewMap()
 {
	// initial hard set of null pointers (disable the tables)
	size_t i;
	for (i = 0; i < MaxAxes; i++)
	{
		screwInfos[i].mapTable = nullptr;
		screwInfos[i].enable = false;
	}

#if TESTING_SCREW_MAP
	InitScrewMap(screwInfos[X_AXIS], 0.0f, 1.0f, 10);
	InitScrewMap(screwInfos[Y_AXIS], 0.0f, 2.0f, 10);
	InitScrewMap(screwInfos[Z_AXIS], 0.0f, 0.5f, 20);
	assert(screwInfos[X_AXIS].count == 10 && screwInfos[X_AXIS].start == 0.0f && screwInfos[X_AXIS].increment == 1.0f);
	assert(screwInfos[X_AXIS].mapTable[0] == 0.0f && screwInfos[X_AXIS].mapTable[9] == 9.0f);
	assert(screwInfos[Y_AXIS].count == 10 && screwInfos[Y_AXIS].start == 0.0f && screwInfos[Y_AXIS].increment == 2.0f);
	assert(screwInfos[Y_AXIS].mapTable[0] == 0.0f && screwInfos[Y_AXIS].mapTable[9] == 18.0f);
	assert(screwInfos[Z_AXIS].count == 10 && screwInfos[Z_AXIS].start == 0.0f && screwInfos[Z_AXIS].increment == 0.5f);
	assert(screwInfos[Z_AXIS].mapTable[0] == 0.0f && screwInfos[Z_AXIS].mapTable[19] == 9.5f);
	ScrewMapInfo& smi = screwInfos[X_AXIS];
	// for default straight map check we make no changes
	int maxCount = 4 * smi.count;	// check every quarter of a segment
	for (i=0; i<(maxCount+2); i++)
	{
		float coord = (i - 1) * smi.increment / 4 + smi.start;
		assert(coord == TransformCoord(coord, smi));
		assert(coord == InverseTransformCoord(coord, smi));
	}
	// now create a 2 slope
	for (i = 0; i < smi.count; i++)
	{
		smi.mapTable[i] = i * 2 * smi.increment - smi.increment;	// -1, 1, 3, 5, ...
	}
	// and check it
	for (i = 0; i < (maxCount+2); i++)
	{
		float coord =  smi.start + (i-1) * smi.increment / 4; 	// Check every quarter increment
		float recoord = TransformCoord(coord, smi);
		assert(coord == InverseTransformCoord(recoord, smi));
	}

#endif
}

void ScrewMap::ClearAllMaps()
{
	for (size_t i = 0; i < MaxAxes; i++)
	{
		ClearMap(&screwInfos[i]);
	}
}

void ScrewMap::ClearMap(ScrewMapInfo* psmi)
{
	if (psmi->mapTable != nullptr)
	{
		delete[] psmi->mapTable;
		psmi->mapTable = nullptr;
	}
	psmi->enable = false;
}

// set the screw map properties and allocate the map table area
bool ScrewMap::InitScrewMap(ScrewMapInfo& smi, float start, float increment, int count)
{
	ClearMap(&smi);

	smi.enable = true;
	smi.start = start;
	smi.increment = increment;
	smi.count = count;
	smi.mapTable = (count > 0) ? (new float[count]) : nullptr;

	// default straight line
	for (size_t i = 0; i < smi.count; i++)
	{
		smi.mapTable[i] = smi.start + i * smi.increment;
 	}
	return true;
}

// apply screw mapping transform to input coord
float ScrewMap::TransformCoord(float coord, const ScrewMapInfo& smi)
 {
	const int idx = smi.IndexOf(coord);							// index of coord within table
	if (idx < 0)
		coord += smi.mapTable[0] - smi.start;					// use constant delta if less than min
	else if (idx >= smi.count)
		coord += smi.mapTable[smi.count-1] - smi.End();			// use constant delta if greater than max
	else
	{
		// in range of the corrections so linear interpolate
		coord = smi.mapTable[idx] + (smi.mapTable[idx+1]-smi.mapTable[idx])*(coord - smi.start - idx * smi.increment) / smi.increment;
	}
	return coord;
}

// Find original coord given screw-mapped coord
// For the inverse transform to work the screw map must be monotonic
float ScrewMap::InverseTransformCoord(float coord, const ScrewMapInfo& smi)
{
	int idx = 0;
	float outco = 0.0f;
	if(coord <= smi.mapTable[0])
	{
		outco = coord + (smi.start - smi.mapTable[0]);
	}
	else if (coord >= smi.mapTable[smi.count-1])
	{
		outco = coord + (smi.End() - smi.mapTable[smi.count - 1]);
	}
	else
	{
		// find the indices coord is between
		for (idx = 1; coord <= smi.mapTable[idx]; idx++)
 		{
			// Nothing to do here, idx can't get too large
 		}
		// Unlinear interpolate
		outco = smi.mapTable[idx-1] + smi.increment * (coord - smi.mapTable[idx-1]) / (smi.mapTable[idx] - smi.mapTable[idx-1]);
 	}
	return outco;
}

bool ScrewMap::LoadFromFile(FileStore *f, const char* fname, const StringRef& r)
{
	return false;
}

bool ScrewMap::SaveToFile(FileStore *f, const char* fname, const StringRef& r)
{
	return false;
}

// transform this coord, where axis is actual X, Y, or Z
void ScrewMap::TransformAxis(float coords[MaxAxes], int axis) const
{
	const ScrewMapInfo& smi = screwInfos[axis];
	if (smi.IsEnabled())
	{
		coords[axis] = TransformCoord( coords[axis], smi);
	}
}

// inverse transform this coord, where axis is actual X, Y, or Z
void ScrewMap::InverseTransformAxis(float coords[MaxAxes], int axis) const
{
	const ScrewMapInfo& smi = screwInfos[axis];
	if (smi.IsEnabled())
	{
		coords[axis] = InverseTransformCoord( coords[axis], smi);
	}
}

// convert all axes
void ScrewMap::Transform(float xyzPoint[MaxAxes], const Tool *tool) const
{
	for (size_t i = 0; i < MaxAxes; i++)
	{
		TransformAxis( xyzPoint, i);
	}
}

// unconvert all axes
void ScrewMap::InverseTransform(float xyzPoint[MaxAxes], const Tool *tool) const
{
	// inverse goes backwards in the axes to be a true inverse
	for (size_t i = MaxAxes-1; i >= 0; i--)
	{
		InverseTransformAxis( xyzPoint, i);
	}
}

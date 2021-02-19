/*
	File: Includes.h

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#pragma once

#pragma region Definitions

//-----------------------------------------------------------------------------
// Orion definitions
//-----------------------------------------------------------------------------
#define ORION_DX11

#pragma endregion Definitions

#pragma region Includes

//-----------------------------------------------------------------------------
// Precompiled header includes
//-----------------------------------------------------------------------------
#include "stdafx.h"

//-----------------------------------------------------------------------------
// Common includes
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <iosfwd>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// Orion Utils includes
//-----------------------------------------------------------------------------
#include "../includes/utils/IncludesUtils.h"

//-----------------------------------------------------------------------------
// Orion Math includes
//-----------------------------------------------------------------------------
#include "../includes/math/IncludesMath.h"

//-----------------------------------------------------------------------------
// Orion Physics includes
//-----------------------------------------------------------------------------
//#include "../includes/bullet/IncludesBullet.h"

//-----------------------------------------------------------------------------
// Orion Widget includes
//-----------------------------------------------------------------------------
#include "../../../engine/public/interfaces/panel/widget/IWidget.h"
#include "../../../engine/public/interfaces/panel/HFont.h"

#include "../../../engine/public/interfaces/panel/widget/gradientwidget/IGradientWidget.h"
#include "../../../engine/public/interfaces/panel/widget/imagewidget/IImageWidget.h"
#include "../../../engine/public/interfaces/panel/widget/textwidget/ITextWidget.h"
#include "../../../engine/public/interfaces/panel/widget/editfieldwidget/IEditField.h"

#pragma endregion Includes
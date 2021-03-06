////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxchicomponent.h
/// @brief Landing methods for CamX implementation of Chi
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXCHICOMPONENT_H
#define CAMXCHICOMPONENT_H

#include "camxhwenvironment.h"

CAMX_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ProbeChiComponents
///
/// @brief  Probe External Components.
///
/// @param  pExternalComponentInfo  info pointer to be filled in
/// @param  pNumExternalComponent   pointer for the number of external components
///
/// @return CamxResultSuccess if successful
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult ProbeChiComponents(
    ExternalComponentInfo* pExternalComponentInfo,
    UINT*                  pNumExternalComponent);

CAMX_NAMESPACE_END
#endif // CAMXCHICOMPONENT_H

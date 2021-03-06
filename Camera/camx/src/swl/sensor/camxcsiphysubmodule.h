////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxcsiphysubmodule.h
/// @brief Class declarations for csiphy sub module
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXCSIPHYSUBMODULE_H
#define CAMXCSIPHYSUBMODULE_H

#include "camxsensorsubmodulebase.h"

CAMX_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class that implements the csiphy sub module class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSIPHYSubmodule final : public SensorSubModuleBase
{

public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create csiphy submodule object
    ///
    /// @param  pHwContext               pointer to Hw Context
    /// @param  hCSLSession              csl session handle
    /// @param  ppCSIPHYSubModule        pointer to pointer to CSIPHY submodule
    /// @param  csiPHYDeviceIndex        CSiPhy device index
    /// @param  cameraId                 current camera ID
    /// @param  pDeviceName              pDeviceName
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static CamxResult Create(
        HwContext*        pHwContext,
        CSLHandle         hCSLSession,
        CSIPHYSubmodule** ppCSIPHYSubModule,
        INT32             csiPHYDeviceIndex,
        UINT32            cameraId,
        const CHAR*       pDeviceName);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Configure
    ///
    /// @brief  Configures the CSI Phy hardware
    ///
    /// @param  hCSLSession      CSL Session handle
    /// @param  pCmdCSIPHYConfig Pointer to Sensor CSIPHYSubmodule Info
    ///
    ///
    /// @return CamxResultSuccess, if SUCCESS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Configure(
        CSLHandle                  hCSLSession,
        const CSLSensorCSIPHYInfo* pCmdCSIPHYConfig);

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~CSIPHYSubmodule
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~CSIPHYSubmodule();

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CSIPHYSubmodule
    ///
    /// @brief  Constructor
    ///
    /// @param  pHwContext     Pointer to HW context
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    explicit CSIPHYSubmodule(
        HwContext*  pHwContext);

    CSIPHYSubmodule(const CSIPHYSubmodule&) = delete;             ///< Disallow the copy constructor.
    CSIPHYSubmodule& operator=(const CSIPHYSubmodule&) = delete;  ///< Disallow assignment operator.
};

CAMX_NAMESPACE_END

#endif // CAMXCSIPHYSUBMODULE_H

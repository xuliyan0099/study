////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxifecamiflite.h
/// @brief camxifecamiflite class declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXIFECAMIFLITE_H
#define CAMXIFECAMIFLITE_H
#include "camxispiqmodule.h"
#include "camxsensorproperty.h"

CAMX_NAMESPACE_BEGIN

CAMX_BEGIN_PACKED
/// @brief IFE CAMIF Module Register
struct IFECAMIFLiteRegCmd
{
    IFE_IFE_0_VFE_CAMIF_LITE_CMD                   statusRegister;      ///< CAMIF LITE Status Register 0xfc0
    IFE_IFE_0_VFE_CAMIF_LITE_CFG                   configRegister;      ///< CAMIF LITE Config Register 0xfc4
    IFE_IFE_0_VFE_CAMIF_LITE_SKIP_PERIOD           skipPeriodRegister;  ///< CAMIF Skip Period Register 0xfc8
    IFE_IFE_0_VFE_CAMIF_LITE_IRQ_SUBSAMPLE_PATTERN irqSubsamplePattern; ///< IRQ Subsample Pattern Register 0xfcc
    IFE_IFE_0_VFE_CAMIF_LITE_EPOCH_IRQ             irqEpochRegister;    ///< Define When the EPOCH IRQ should happen 0xfd0
} CAMX_PACKED;

CAMX_END_PACKED

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class for IFE CAMIF Module
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IFECAMIFLite final : public ISPIQModule
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create IFECAMIFLite Object
    ///
    /// @param  pCreateData Pointer to data for CAMIF Creation
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static CamxResult Create(
        IFEModuleCreateData* pCreateData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Execute
    ///
    /// @brief  Generate Settings for CAMIFLite Object
    ///
    /// @param  pInputData Pointer to the Inputdata
    ///
    /// @return CamxResultSuccess if successful.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult Execute(
        ISPInputData* pInputData);

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~IFECAMIFLite
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~IFECAMIFLite();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IFECAMIFLite
    ///
    /// @brief  Constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    IFECAMIFLite();

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CheckDependenceChange
    ///
    /// @brief  Check if the Dependence Data has changed
    ///
    /// @param  pInputData Point to the Input Data
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL CheckDependenceChange(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RunCalculation
    ///
    /// @brief  Perform the Interpolation and Calculation
    ///
    /// @param  pInputData Point to the Input Data
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult RunCalculation(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CreateCmdList
    ///
    /// @brief  Generate the Command List
    ///
    /// @param  pInputData Point to the Input Data
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult CreateCmdList(
        ISPInputData* pInputData);

    IFECAMIFLiteRegCmd     m_regCmd;        ///< Register List of this module

    IFECAMIFLite(const IFECAMIFLite&)            = delete;    ///< Disallow the copy constructor
    IFECAMIFLite& operator=(const IFECAMIFLite&) = delete;    ///< Disallow assignment operator
};

CAMX_NAMESPACE_END

#endif // CAMXIFECAMIFLITE_H

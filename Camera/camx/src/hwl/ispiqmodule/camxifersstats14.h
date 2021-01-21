////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxifersstats14.h
/// @brief Row Sum stats v1.4 class declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CAMXIFERSSTATS14_H
#define CAMXIFERSSTATS14_H

#include "camxispstatsmodule.h"

CAMX_NAMESPACE_BEGIN

static const UINT32 RSInputDepth                    = 12;   ///< Input depth to RS stats
static const UINT32 RSOutputDepth                   = 16;   ///< Output bit depths of RS stats

// Register range from the SWI/HPG
static const UINT32 RSStats14MaxRegionHeight        = 16;   ///< Maximum RS stats region width
static const UINT32 RSStats14MinRegionHeight        = 1;    ///< Minimum RS stats region width

static const UINT32 RSStats14MinHorizRegions        = 1;    ///< Minimum RS stats horizontal region
static const UINT32 RSStats14MaxHorizRegions        = 16;   ///< Maximum RS stats horizontal region
static const UINT32 RSStats14MinVertRegions         = 1;    ///< Maximum RS stats vertical region
static const UINT32 RSStats14MaxVertRegions         = 1024; ///< Maximum RS stats vertical region

CAMX_BEGIN_PACKED

/// @brief RS Stats Configuration
struct IFERS14RegionConfig
{
    IFE_IFE_0_VFE_STATS_RS_RGN_OFFSET_CFG   regionOffset;   ///< RS stats region offset config
    IFE_IFE_0_VFE_STATS_RS_RGN_NUM_CFG      regionNum;      ///< RS stats region number config
    IFE_IFE_0_VFE_STATS_RS_RGN_SIZE_CFG     regionSize;     ///< RS stats region size config
} CAMX_PACKED;

CAMX_END_PACKED

struct IFERS14RegCmd
{
    IFERS14RegionConfig regionConfig;   ///< RS stats region config
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief RS Stats14 Class Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RSStats14 final : public ISPStatsModule
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create RSStats14 Object
    ///
    /// @param  pCreateData Pointer to the RSStats14 Creation
    ///
    /// @return CamxResultSuccess if successful.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static CamxResult Create(
        IFEStatsModuleCreateData* pCreateData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Execute
    ///
    /// @brief  Execute process capture request to configure module
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResultSuccess if successful.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult Execute(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// PrepareStripingParameters
    ///
    /// @brief  Prepare striping parameters for striping lib
    ///
    /// @param  pInputData Pointer to the Inputdata
    ///
    /// @return CamxResultSuccess if successful.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult PrepareStripingParameters(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~RSStats14
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~RSStats14();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RSStats14
    ///
    /// @brief  Constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    RSStats14();

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ConfigureRegs
    ///
    /// @brief  Configure scaler registers
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID ConfigureRegs(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DumpRegConfig
    ///
    /// @brief  Print register configuration of RS Stats module for debugging
    ///
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DumpRegConfig();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CheckDependency
    ///
    /// @brief  Check to see if the Dependencies have been met
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return BOOL
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL CheckDependency(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// UpdateIFEInternalData
    ///
    /// @brief  Update IFE internal data
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID UpdateIFEInternalData(
        ISPInputData * pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CreateCmdList
    ///
    /// @brief  Create the Command List
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult CreateCmdList(
        ISPInputData* pInputData);

    RSStats14(const RSStats14&)            = delete;    ///< Disallow the copy constructor
    RSStats14& operator=(const RSStats14&) = delete;   ///< Disallow assignment operator

    IFERS14RegCmd       m_regCmd;       ///< Register list for RS stats
    ISPRSStatsConfig    m_RSConfig;     ///< RS configuration information
    UINT32              m_CAMIFWidth;   ///< CAMIF width
    UINT32              m_CAMIFHeight;  ///< CAMIF height
    UINT16              m_shiftBits;    ///< Number of bit shift required to get 16 bits row sum output
    UINT32              m_calculatedRegnWidth;  ///< Calculated Region Width
    UINT32              m_calculatedRegnHeight; ///< Calculated Region Height
};

CAMX_NAMESPACE_END

#endif // CAMXIFERSSTATS14_H
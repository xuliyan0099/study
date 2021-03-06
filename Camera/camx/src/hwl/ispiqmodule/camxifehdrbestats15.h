////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017,2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxifehdrbestats15.h
/// @brief HDR BE Stats15 class declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CAMXIFEHDRBESTATS15_H
#define CAMXIFEHDRBESTATS15_H

#include "camxispstatsmodule.h"

CAMX_NAMESPACE_BEGIN

// Register range from the SWI/HPG
static const UINT32 HDRBEStats15RegionMinWidth  = 6;                    ///< Minimum HDR BE stats region width
static const UINT32 HDRBEStats15RegionMaxWidth  = 390;                  ///< Maximum HDR BE stats region width
static const UINT32 HDRBEStats15RegionMinHeight = 2;                    ///< Minimum HDR BE stats region Height
static const UINT32 HDRBEStats15RegionMaxHeight = 512;                  ///< Maximum HDR BE stats region Height

static const INT32 HDRBEStats15MaxHorizontalregions = 64;               ///< Maximum HDR BE stats horizontal region
static const INT32 HDRBEStats15MaxVerticalregions   = 48;               ///< Maximum HDR BE stats vertical region

static const UINT32 HDRBEStats15MaxChannelThreshold = (1 << IFEPipelineBitWidth) - 1;   ///< Max HDR BE stats Channel threshold

CAMX_BEGIN_PACKED

/// @brief HDR BE Stats Configuration
struct IFEHDRBE15RegionConfig
{
    IFE_IFE_0_VFE_STATS_HDR_BE_RGN_OFFSET_CFG        regionOffset;      ///< HDR BE stats region offset config
    IFE_IFE_0_VFE_STATS_HDR_BE_RGN_NUM_CFG           regionNumber;      ///< HDR BE stats region number config
    IFE_IFE_0_VFE_STATS_HDR_BE_RGN_SIZE_CFG          regionSize;        ///< HDR BE stats region size config
    IFE_IFE_0_VFE_STATS_HDR_BE_HI_THRESHOLD_CFG_0    highThreshold0;    ///< HDR BE stats pixel upper threshold config
    IFE_IFE_0_VFE_STATS_HDR_BE_HI_THRESHOLD_CFG_1    highThreshold1;    ///< HDR BE stats pixel upper threshold config
    IFE_IFE_0_VFE_STATS_HDR_BE_LO_THRESHOLD_CFG_0    lowThreshold0;     ///< HDR BE stats pixel lower threshold config
    IFE_IFE_0_VFE_STATS_HDR_BE_LO_THRESHOLD_CFG_1    lowThreshold1;     ///< HDR BE stats pixel lower threshold config
} CAMX_PACKED;
CAMX_END_PACKED

struct IFEHDRBE15RegCmd
{
    IFEHDRBE15RegionConfig                 regionConfig;                ///< HDR BE stats region and threshold config
    IFE_IFE_0_VFE_STATS_HDR_BE_CH_Y_CFG    lumaConfig;                  ///< HDR BE stats luma channel config
    IFE_IFE_0_VFE_STATS_HDR_BE_CFG         HDRBEStatsconfig;            ///< HDR BE stats config
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief HDR BE Stats14 Class Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HDRBEStats15 final : public ISPStatsModule
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create HDRBEStats15 Object
    ///
    /// @param  pCreateData Pointer to the HDRBEStats15 Creation
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
    /// GetDMITable
    ///
    /// @brief  Retrieve the DMI LUT
    ///
    /// @param  ppDMITable Pointer to which the module should update different DMI tables
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual VOID GetDMITable(
       UINT32** ppDMITable);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~HDRBEStats15
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~HDRBEStats15();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// HDRBEStats15
    ///
    /// @brief  Constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HDRBEStats15();

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ValidateDependenceParams
    ///
    /// @brief  Validate the stats region of interest configuration from stats module
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult Indicates if the input is valid or invalid
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult ValidateDependenceParams(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CheckDependenceChange
    ///
    /// @brief  Check to see if the Dependence Trigger Data Changed
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return BOOL
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL CheckDependenceChange(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RunCalculation
    ///
    /// @brief  Calculate the Register Value
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID RunCalculation(
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
    /// ConfigureRegisters
    ///
    /// @brief  Configure HDR BE stats module registers
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID ConfigureRegisters();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AdjustROIParams
    ///
    /// @brief  Adjust ROI from stats to requirement based on hardware
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID AdjustROIParams();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DumpRegConfig
    ///
    /// @brief  Print register configuration of HDR BE module for debug
    ///
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DumpRegConfig();

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

    HDRBEStats15(const HDRBEStats15&)            = delete;    ///< Disallow the copy constructor
    HDRBEStats15& operator=(const HDRBEStats15&) = delete;    ///< Disallow assignment operator

    IFEHDRBE15RegCmd    m_regCmd;                             ///< Register list for HDR BE stats
    BGBEConfig          m_HDRBEConfig;                        ///< HDR BE configuration data from stats
    UINT32              m_HDRBEStatsTapout;                   ///< HDR BE stats tapout point
    UINT32              m_regionMultipleFactor;               ///< HDR BE region offset and dimension multiple factor
    UINT32              m_fieldSelect;                        ///< Lines with in ROI which would contribute to HDR stats from Hw
    UINT32              m_regionWidth;                        ///< DR BE individual region width
    UINT32              m_regionHeight;                       ///< DR BE individual region height
    BOOL                m_isAdjusted;                         ///< Flag to indicate if ROI from stats was modified
};

CAMX_NAMESPACE_END

#endif // CAMXIFEHDRBESTATS15_H

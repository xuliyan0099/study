////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxipechromaenhancement12.h
/// @brief IPEChromaEnhancement class declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXIPECHROMAENHANCEMENT12_H
#define CAMXIPECHROMAENHANCEMENT12_H

#include "camxispiqmodule.h"
#include "iqcommondefs.h"
#include "titan170_ipe.h"

CAMX_NAMESPACE_BEGIN

CAMX_BEGIN_PACKED

/// @brief: This structure contains chroma enhancement registers programmed by software
struct IPEChromaEnhancementRegCmd
{
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_LUMA_CFG_0     lumaConfig0; ///< RGB2Y conversion multiplication coefficents
                                                                            ///< V0 and V1
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_LUMA_CFG_1     lumaConfig1; ///< RGB2Y conversion multiplication coefficent
                                                                            ///< V2 and offset coefficent.
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_COEFF_A_CFG    aConfig;     ///< RGB2Cb conversion matrix parameters (AM, AP)
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_COEFF_B_CFG    bConfig;     ///< RGB2Cb conversion matrix parameters (BM, BP)
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_COEFF_C_CFG    cConfig;     ///< RGB2Cb conversion matrix parameters (CM, CP)
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_COEFF_D_CFG    dConfig;     ///< RGB2Cb conversion matrix parameters (DM, DP)
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_OFFSET_KCB_CFG cbConfig;    ///< RGB2CbCr offset for matrix conversion(KCB)
    IPE_IPE_0_PPS_CLC_CHROMA_ENHAN_CHROMA_ENHAN_OFFSET_KCR_CFG crConfig;    ///< RGB2CbCr offset for matrix conversion(KCR)
} CAMX_PACKED;

CAMX_END_PACKED

static const UINT32 IPEChromaEnhancementRegLength = sizeof(IPEChromaEnhancementRegCmd) / RegisterWidthInBytes;
CAMX_STATIC_ASSERT((8 * 4) == sizeof(IPEChromaEnhancementRegCmd));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Class for IPE Chroma Enhancement Module
///
///         This IQ block supports two separate functions: RGB->YUV color transform and Chorma enhancement
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPEChromaEnhancement12 final : public ISPIQModule
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create ChromaEnhancement Object
    ///
    /// @param  pCreateData  Pointer to resource and intialization data for ChromaEnhancement12 Creation
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static CamxResult Create(
        IPEModuleCreateData* pCreateData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Initialize
    ///
    /// @brief  Initialize parameters
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult Initialize();

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
    /// GetRegCmd
    ///
    /// @brief  Retrieve the buffer of the register value
    ///
    /// @return Pointer of the register buffer
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual VOID* GetRegCmd();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~IPEChromaEnhancement12
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~IPEChromaEnhancement12();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IPEChromaEnhancement12
    ///
    /// @brief  Constructor
    ///
    /// @param  pNodeIdentifier     String identifier for the Node that creating this IQ Module object
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    explicit IPEChromaEnhancement12(
        const CHAR* pNodeIdentifier);

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AllocateCommonLibraryData
    ///
    /// @brief  Allocate memory required for common library
    ///
    /// @return CamxResult success if the write operation is success
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult AllocateCommonLibraryData();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DeallocateCommonLibraryData
    ///
    /// @brief  Deallocate memory required for common library
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DeallocateCommonLibraryData();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ValidateDependenceParams
    ///
    /// @brief  Validate the input configuration from app
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult Indicates if the input is valid or invalid
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult ValidateDependenceParams(
        const ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CheckDependenceChange
    ///
    /// @brief  Check to see if the Dependence Trigger Data Changed
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return BOOL Indicates if the settings have changed compared to last setting
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL CheckDependenceChange(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// UpdateIPEInternalData
    ///
    /// @brief  Update Pipeline input data, such as metadata, IQSettings.
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult success if the write operation is success
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult UpdateIPEInternalData(
        const ISPInputData* pInputData
        ) const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RunCalculation
    ///
    /// @brief  Calculate the Register Value
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult Indicates if configuration calculation was success or failure
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult RunCalculation(
        const ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DumpRegConfig
    ///
    /// @brief  Print register configuration of Chroma Enhancement module for debug
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DumpRegConfig() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CreateCmdList
    ///
    /// @brief  Create the Command List
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult success if the write operation is success
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult CreateCmdList(
        const ISPInputData* pInputData);

    IPEChromaEnhancement12(const IPEChromaEnhancement12&)            = delete;  ///< Disallow the copy constructor
    IPEChromaEnhancement12& operator=(const IPEChromaEnhancement12&) = delete;  ///< Disallow assignment operator

    const CHAR*                   m_pNodeIdentifier;    ///< String identifier for the Node that created this object
    CV12InputData                 m_dependenceData;     ///< Dependence Data for this Module
    IPEChromaEnhancementRegCmd    m_regCmd;             ///< Register List of this Module
    cv_1_2_0::chromatix_cv12Type* m_pChromatix;         ///< Pointer to tuning mode data
};

CAMX_NAMESPACE_END

#endif // CAMXIPECHROMAENHANCEMENT12_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxipegrainadder10.h
/// @brief IPEGrainAdder class declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXIPEGRAINADDER10_H
#define CAMXIPEGRAINADDER10_H

#include "camxispiqmodule.h"
#include "gra10setting.h"
#include "gra_1_0_0.h"
#include "ipe_data.h"

CAMX_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Class for IPE GrainAdder10 Module
///
///         This IQ block adds fine grain (dither, LUT random generator) to remove banding artifacts
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IPEGrainAdder10 final : public ISPIQModule
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Create Grain Adder Object
    ///
    /// @param  pCreateData  Pointer to resource and intialization data for GrainAdder10 Creation
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static CamxResult Create(
        IPEModuleCreateData* pCreateData);

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
    /// FillCmdBufferManagerParams
    ///
    /// @brief  Fills the command buffer manager params needed by IQ Module
    ///
    /// @param  pInputData Pointer to the IQ Module Input data structure
    /// @param  pParam     Pointer to the structure containing the command buffer manager param to be filled by IQ Module
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult FillCmdBufferManagerParams(
       const ISPInputData*     pInputData,
       IQModuleCmdBufferParam* pParam);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetRegCmd
    ///
    /// @brief  Retrieve the buffer of the register value
    ///
    /// @return Pointer of the register buffer
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual VOID* GetRegCmd();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~IPEGrainAdder10
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~IPEGrainAdder10();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IPEGrainAdder10
    ///
    /// @brief  Constructor
    ///
    /// @param  pNodeIdentifier     String identifier for the Node that creating this IQ Module object
    /// @param  pCreateData         Initialization data for IPEGRA
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    explicit IPEGrainAdder10(
        const CHAR*          pNodeIdentifier,
        IPEModuleCreateData* pCreateData);

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
    /// Initialize
    ///
    /// @brief  Initialize parameters
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual CamxResult Initialize();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ValidateDependenceParams
    ///
    /// @brief  Validate the input info from client
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult Indicates if the input is valid or invalid
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult ValidateDependenceParams(
        const ISPInputData* pInputData
        ) const;

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
    /// UpdateLUTFromChromatix
    ///
    /// @brief  Check to see if the Dependence Trigger Data Changed
    ///
    /// @param  pLUT Pointer to start of command buffer where Look up tables are present
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID UpdateLUTFromChromatix(
        UINT32* pLUT);

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
    /// @param  pInputData Pointer to the IQ Module Input data
    ///
    /// @return CamxResult Indicates if configuration calculation was success or failure
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult RunCalculation(
        ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// FetchDMIBuffer
    ///
    /// @brief  Fetch GrainAdder10 DMI LUT
    ///
    /// @return CamxResult Indicates if fetch DMI was success or failure
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult FetchDMIBuffer();

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// WriteLUTtoDMI
    ///
    /// @brief  Write Look up table data pointer into DMI header
    ///
    /// @param  pInputData Pointer to the ISP input data
    ///
    /// @return CamxResult Indicates if configuration calculation was success or failure
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult WriteLUTtoDMI(
        const ISPInputData* pInputData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DumpRegConfig
    ///
    /// @brief  Print register configuration of Grain Adder module for debug
    ///
    /// @param  pDMIDataPtr Pointer to the DMI data
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DumpRegConfig(
        UINT32* pDMIDataPtr
        ) const;

    IPEGrainAdder10(const IPEGrainAdder10&)            = delete;      ///< Disallow the copy constructor
    IPEGrainAdder10& operator=(const IPEGrainAdder10&) = delete;      ///< Disallow assignment operator

    const CHAR*                     m_pNodeIdentifier;                ///< String identifier for the Node that created this
    GRA10IQInput                    m_dependenceData;                 ///< Dependence Data for this Module
    UINT                            m_enableDitheringC;               ///< dithering C enable
    UINT                            m_enableDitheringY;               ///< dithering Y enable
    CmdBufferManager*               m_pLUTCmdBufferManager;           ///< Command buffer manager for all LUTs of GRA
    CmdBuffer*                      m_pLUTCmdBuffer;                  ///< Command buffer for holding all 3 LUTs
    UINT                            m_offsetLUTCmdBuffer[GRALUTMax];  ///< Offset of all tables within LUT CmdBuffer
    UINT                            m_grainStrength;                  ///< Grain Strength
    UINT                            m_grainSeed;                      ///< Grain seed value
    UINT                            m_mcgA;                           ///< Multiplier parameter for MCG calculation
    UINT                            m_skipAheadJump;                  ///< It will be equal to mcg_an mod m.
    BOOL                            m_enableCommonIQ;                 ///< EnableCommon IQ module
    UINT32*                         m_pGrainAdderLUTs;                ///< Tuning, hold LUTs
    gra_1_0_0::chromatix_gra10Type* m_pChromatix;                     ///< Pointer to tuning mode data
};

CAMX_NAMESPACE_END

#endif // CAMXIPEGRAINADDER10_H
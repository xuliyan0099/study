// NOWHINE NC009 <- Shared file with system team so uses non-CamX file naming
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  hdr23interpolation.cpp
/// @brief IFE HDR23 tuning data interpolation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "hdr23interpolation.h"

// This table defines the function of each level of node to search for the child node
static NodeOperation HDR23OperationTable[] =
{
    {IFEHDR23Interpolation::HDRAECSearchNode, 2},
    {IFEHDR23Interpolation::AECSearchNode,    2}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// IFEHDR23Interpolation::CheckUpdateTrigger
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL IFEHDR23Interpolation::CheckUpdateTrigger(
    ISPIQTriggerData* pInput,
    HDR23InputData*   pTriggerData)
{
    BOOL isChanged = FALSE;

    if ((FALSE == IQSettingUtils::FEqual(pTriggerData->luxIndex, pInput->AECLuxIndex))                   ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->AECGain,  pInput->AECGain))                       ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->AECSensitivity, pInput->AECSensitivity))          ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->exposureTime, pInput->AECexposureTime))           ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->exposureGainRatio, pInput->AECexposureGainRatio)) ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->leftGGainWB, pInput->AWBleftGGainWB))             ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->leftBGainWB, pInput->AWBleftBGainWB))             ||
        (FALSE == IQSettingUtils::FEqual(pTriggerData->leftRGainWB, pInput->AWBleftRGainWB))             ||
        (pTriggerData->blackLevelOffset != pInput->blackLevelOffset))
    {
        pTriggerData->luxIndex          = pInput->AECLuxIndex;
        pTriggerData->AECGain           = pInput->AECGain;
        pTriggerData->AECSensitivity    = pInput->AECSensitivity;
        pTriggerData->exposureTime      = pInput->AECexposureTime;
        pTriggerData->exposureGainRatio = pInput->AECexposureGainRatio;
        pTriggerData->leftGGainWB       = pInput->AWBleftGGainWB;
        pTriggerData->leftBGainWB       = pInput->AWBleftBGainWB;
        pTriggerData->leftRGainWB       = pInput->AWBleftRGainWB;
        pTriggerData->blackLevelOffset  = pInput->blackLevelOffset;

        isChanged = TRUE;
    }

    return isChanged;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// IFEHDR23Interpolation::RunInterpolation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL IFEHDR23Interpolation::RunInterpolation(
    const HDR23InputData*          pInput,
    hdr_2_3_0::hdr23_rgn_dataType* pData)
{
    BOOL                          result = TRUE;
    TuningNode                    nodeSet[HDR23MaxmiumNode]; // The interpolation tree total Node
    HDR23TriggerList              hdrTrigger;                // HDR23 Trigger List

    if ((NULL != pInput) && (NULL != pData) && (NULL != pInput->pChromatix))
    {
        // Initialize all the nodes
        for (UINT count = 0; count < HDR23MaxmiumNode; count++)
        {
            if (count < HDR23MaxmiumNonLeafNode)
            {
                IQSettingUtils::InitializeNode(&nodeSet[count], &pData[count + 1]);
            }
            else
            {
                IQSettingUtils::InitializeNode(&nodeSet[count], NULL);
            }
        }

        // Setup the Top Node
        IQSettingUtils::AddNodeToInterpolationTree(NULL, &nodeSet[0],
            static_cast<VOID*>(&pInput->pChromatix->chromatix_hdr23_core), NULL);

        // Setup Trigger Data
        IQSettingUtils::Memcpy(&hdrTrigger.controlType,
                               &(pInput->pChromatix->control_method),
                               sizeof(hdr_2_3_0::chromatix_hdr23Type::control_methodStruct));

        hdrTrigger.triggerHDRAEC =
            IQSettingUtils::GettriggerHDRAEC(pInput->pChromatix->control_method.aec_hdr_control,
                                             pInput->exposureTime,
                                             pInput->AECSensitivity,
                                             pInput->exposureGainRatio);

        hdrTrigger.triggerAEC    =
            IQSettingUtils::GettriggerAEC(pInput->pChromatix->control_method.aec_exp_control,
                                          pInput->luxIndex,
                                          pInput->AECGain);

        // Set up Interpolation Tree
        result = IQSettingUtils::SetupInterpolationTree(&nodeSet[0],
                                                        HDR23InterpolationLevel,
                                                        &HDR23OperationTable[0],
                                                        static_cast<VOID*>(&hdrTrigger));
    }
    else
    {
        /// @todo (CAMX-1812) Need to add logging for Common library
        result = FALSE;
    }
    if (FALSE != result)
    {
        // Calculate the Interpolation Result
        result = IQSettingUtils::InterpolateTuningData(&nodeSet[0],
                                                       HDR23MaxmiumNonLeafNode,
                                                       HDR23InterpolationLevel,
                                                       IFEHDR23Interpolation::DoInterpolation);
        if (FALSE != result)
        {
            IQSettingUtils::Memcpy(pData, nodeSet[0].pData, sizeof(hdr_2_3_0::hdr23_rgn_dataType));
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// IFEHDR23Interpolation::DoInterpolation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL IFEHDR23Interpolation::DoInterpolation(
    VOID* pData1,
    VOID* pData2,
    FLOAT ratio,
    VOID* pResult)
{
    BOOL result = TRUE;

    if ((NULL != pData1) && (NULL != pData2) && (NULL != pResult))
    {
        /// pInput1 and pInput2 are the Data region1 and Data region 2
        /// ....Region1           Interpolation     Region2
        ///    ---------- | ------------------- | ----------
        /// ....ratio= 0.0......ratio (>0 && <1).....ratio = 1.0

        hdr_2_3_0::hdr23_rgn_dataType* pInput1 = static_cast<hdr_2_3_0::hdr23_rgn_dataType*>(pData1);
        hdr_2_3_0::hdr23_rgn_dataType* pInput2 = static_cast<hdr_2_3_0::hdr23_rgn_dataType*>(pData2);
        hdr_2_3_0::hdr23_rgn_dataType* pOutput = static_cast<hdr_2_3_0::hdr23_rgn_dataType*>(pResult);

        if (pInput1 == pInput2)
        {
            IQSettingUtils::Memcpy(pOutput, pInput1, sizeof(hdr_2_3_0::hdr23_rgn_dataType));
        }
        else if ((ratio > 0.0f) && (ratio < 1.0f))
        {
            result = IFEHDR23Interpolation::InterpolationData(pInput1, pInput2, ratio, pOutput);
        }
        else
        {
            if (IQSettingUtils::FEqual(ratio, 0.0f))
            {
                IQSettingUtils::Memcpy(pOutput, pInput1, sizeof(hdr_2_3_0::hdr23_rgn_dataType));
            }
            else if (IQSettingUtils::FEqual(ratio, 1.0f))
            {
                IQSettingUtils::Memcpy(pOutput, pInput2, sizeof(hdr_2_3_0::hdr23_rgn_dataType));
            }
            else
            {
                result = FALSE;
                /// @todo (CAMX-1812) Need to add logging for Common library
            }
        }
    }
    else
    {
        result = FALSE;
        /// @todo (CAMX-1812) Need to add logging for Common library
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// IFEHDR23Interpolation::InterpolationData
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL IFEHDR23Interpolation::InterpolationData(
    hdr_2_3_0::hdr23_rgn_dataType* pInput1,
    hdr_2_3_0::hdr23_rgn_dataType* pInput2,
    FLOAT                          ratio,
    hdr_2_3_0::hdr23_rgn_dataType* pOutput)
{
    BOOL result = TRUE;

    if ((NULL != pInput1) && (NULL != pInput2) && (NULL != pOutput))
    {
        pOutput->hdr_zrec_g_grad_th1     = IQSettingUtils::InterpolationFloatBilinear(pInput1->hdr_zrec_g_grad_th1,
                                                                                      pInput2->hdr_zrec_g_grad_th1,
                                                                                      ratio);
        pOutput->hdr_zrec_prefilt_tap0   = IQSettingUtils::InterpolationFloatBilinear(pInput1->hdr_zrec_prefilt_tap0,
                                                                                      pInput2->hdr_zrec_prefilt_tap0,
                                                                                      ratio);
        pOutput->hdr_zrec_rb_grad_th1    = IQSettingUtils::InterpolationFloatBilinear(pInput1->hdr_zrec_rb_grad_th1,
                                                                                      pInput2->hdr_zrec_rb_grad_th1,
                                                                                      ratio);
        pOutput->mac_high_light_dth_log2 = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_high_light_dth_log2,
                                                                                      pInput2->mac_high_light_dth_log2,
                                                                                      ratio);
        pOutput->mac_high_light_th1      = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_high_light_th1,
                                                                                      pInput2->mac_high_light_th1,
                                                                                      ratio);
        pOutput->mac_low_light_strength  = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_low_light_strength,
                                                                                      pInput2->mac_low_light_strength,
                                                                                      ratio);
        pOutput->mac_low_light_th1       = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_low_light_th1,
                                                                                      pInput2->mac_low_light_th1,
                                                                                      ratio);
        pOutput->mac_motion0_strength    = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_motion0_strength,
                                                                                      pInput2->mac_motion0_strength,
                                                                                      ratio);
        pOutput->mac_motion0_th1         = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_motion0_th1,
                                                                                      pInput2->mac_motion0_th1,
                                                                                      ratio);
        pOutput->mac_motion0_th2         = IQSettingUtils::InterpolationFloatBilinear(pInput1->mac_motion0_th2,
                                                                                      pInput2->mac_motion0_th2,
                                                                                      ratio);
        pOutput->recon_dark_dth_log2     = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_dark_dth_log2,
                                                                                      pInput2->recon_dark_dth_log2,
                                                                                      ratio);
        pOutput->recon_dark_th1          = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_dark_th1,
                                                                                      pInput2->recon_dark_th1,
                                                                                      ratio);
        pOutput->recon_flat_region_th    = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_flat_region_th,
                                                                                      pInput2->recon_flat_region_th,
                                                                                      ratio);
        pOutput->recon_h_edge_dth_log2   = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_h_edge_dth_log2,
                                                                                      pInput2->recon_h_edge_dth_log2,
                                                                                      ratio);
        pOutput->recon_h_edge_th1        = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_h_edge_th1,
                                                                                      pInput2->recon_h_edge_th1,
                                                                                      ratio);
        pOutput->recon_min_factor        = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_min_factor,
                                                                                      pInput2->recon_min_factor,
                                                                                      ratio);
        pOutput->recon_motion_dth_log2   = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_motion_dth_log2,
                                                                                      pInput2->recon_motion_dth_log2,
                                                                                      ratio);
        pOutput->recon_motion_th1        = IQSettingUtils::InterpolationFloatBilinear(pInput1->recon_motion_th1,
                                                                                      pInput2->recon_motion_th1,
                                                                                      ratio);
    }
    else
    {
        result = FALSE;
        /// @todo (CAMX-1812) Need to add logging for Common library
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IFEHDR23Interpolation::HDRAECSearchNode
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT IFEHDR23Interpolation::HDRAECSearchNode(
    TuningNode* pParentNode,
    VOID*       pTriggerData,
    TuningNode* pChildNode)
{
    UINT   childCount   = 0;
    FLOAT  triggerValue = 0.0f;
    UINT32 regionNumber = 0;

    TriggerRegion       triggerRegion[MaxNumRegion];
    InterpolationOutput regionOutput;

    hdr_2_3_0::chromatix_hdr23_coreType*   pParentDataType = NULL;
    HDR23TriggerList*  pTriggerList    = NULL;

    if ((NULL != pParentNode)    &&
        (NULL != pTriggerData)   &&
        (NULL != pChildNode))
    {
        pParentDataType = static_cast<hdr_2_3_0::chromatix_hdr23_coreType*>(pParentNode->pNodeData);
        regionNumber    = pParentDataType->mod_hdr23_hdr_aec_dataCount;
        pTriggerList    = static_cast<HDR23TriggerList*>(pTriggerData);

        for (UINT count = 0; count < regionNumber; count++)
        {
            IQSettingUtils::CopyTriggerRegionHDRAEC(
                pTriggerList->controlType.aec_hdr_control,
                &(pParentDataType->mod_hdr23_hdr_aec_data[count].hdr_aec_trigger),
                &(triggerRegion[count]));
        }

        triggerValue = pTriggerList->triggerHDRAEC;

        // Find the index based on the trigger value
        IQSettingUtils::GetIndexPtTrigger(&triggerRegion[0], regionNumber, triggerValue, &regionOutput);

        // Adding Intepolation Value to ParentNode
        pParentNode->interpolationValue[0] = regionOutput.interpolationRatio;

        // Set up child 1
        IQSettingUtils::AddNodeToInterpolationTree(pParentNode, &pChildNode[childCount],
           static_cast<VOID*>(&pParentDataType->mod_hdr23_hdr_aec_data[regionOutput.startIndex]),
           NULL);
        childCount++;

        if (regionOutput.startIndex != regionOutput.endIndex)
        {
            // Set up child 2
            IQSettingUtils::AddNodeToInterpolationTree(pParentNode, &pChildNode[childCount],
                static_cast<VOID*>(&pParentDataType->mod_hdr23_hdr_aec_data[regionOutput.endIndex]),
                NULL);
            childCount++;
        }

        pParentNode->numChild = childCount;
    }
    else
    {
        /// @todo (CAMX-1812) Need to add logging for Common library
        childCount = 0;
    }

    return childCount;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IFEHDR23Interpolation::AECSearchNode
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT IFEHDR23Interpolation::AECSearchNode(
    TuningNode* pParentNode,
    VOID*       pTriggerData,
    TuningNode* pChildNode)
{
    UINT   childCount   = 0;
    FLOAT  triggerValue = 0.0f;
    UINT32 regionNumber = 0;

    TriggerRegion       triggerRegion[MaxNumRegion];
    InterpolationOutput regionOutput;

    hdr_2_3_0::mod_hdr23_hdr_aec_dataType*   pParentDataType = NULL;
    HDR23TriggerList*  pTriggerList    = NULL;

    if ((NULL != pParentNode)    &&
        (NULL != pTriggerData)   &&
        (NULL != pChildNode))
    {
        pParentDataType = static_cast<hdr_2_3_0::mod_hdr23_hdr_aec_dataType*>(pParentNode->pNodeData);
        regionNumber    = pParentDataType->hdr_aec_data.mod_hdr23_aec_dataCount;
        pTriggerList    = static_cast<HDR23TriggerList*>(pTriggerData);

        for (UINT count = 0; count < regionNumber; count++)
        {
            IQSettingUtils::CopyTriggerRegionAEC(
                pTriggerList->controlType.aec_exp_control,
                &(pParentDataType->hdr_aec_data.mod_hdr23_aec_data[count].aec_trigger),
                &(triggerRegion[count]));
        }

        triggerValue = pTriggerList->triggerAEC;

        // Find the index based on the trigger value
        IQSettingUtils::GetIndexPtTrigger(&triggerRegion[0], regionNumber, triggerValue, &regionOutput);

        // Adding Intepolation Value to ParentNode
        pParentNode->interpolationValue[0] = regionOutput.interpolationRatio;

        // Set up child 1
        IQSettingUtils::AddNodeToInterpolationTree(pParentNode, &pChildNode[childCount],
           static_cast<VOID*>(&pParentDataType->hdr_aec_data.mod_hdr23_aec_data[regionOutput.startIndex]),
           static_cast<VOID*>(&pParentDataType->hdr_aec_data.mod_hdr23_aec_data[regionOutput.startIndex].hdr23_rgn_data));
        childCount++;

        if (regionOutput.startIndex != regionOutput.endIndex)
        {
            // Set up child 2
            IQSettingUtils::AddNodeToInterpolationTree(pParentNode, &pChildNode[childCount],
                static_cast<VOID*>(&pParentDataType->hdr_aec_data.mod_hdr23_aec_data[regionOutput.endIndex]),
                static_cast<VOID*>(&pParentDataType->hdr_aec_data.mod_hdr23_aec_data[regionOutput.endIndex].hdr23_rgn_data));
            childCount++;
        }

        pParentNode->numChild = childCount;
    }
    else
    {
        /// @todo (CAMX-1812) Need to add logging for Common library
        childCount = 0;
    }

    return childCount;
};

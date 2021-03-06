////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxncssensordata.h
/// @brief CamX NCS Sensor Data accessor header
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXNCSSENSORDATA_H
#define CAMXNCSSENSORDATA_H

#include "camxncsintf.h"

CAMX_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class that implements the NCS sensor data accessor object
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NOWHINE CP044: Need to set visibility, false positive
class NCSSensorData
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// NCSSensorData
    ///
    /// @brief  the default constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC NCSSensorData() = default;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetFirst
    ///
    /// @brief  Get the first sample
    ///
    /// @return returns data sample
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID* GetFirst();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetNext
    ///
    /// @brief  Get the next sample
    ///
    /// @return returns data sample
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID* GetNext();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetCurrent
    ///
    /// @brief  Get the current sample
    ///
    /// @return returns data sample
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID* GetCurrent();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetNumSamples
    ///
    /// @brief  Get the number of samples
    ///
    /// @return returns number of samples
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC INT  GetNumSamples();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetIndex
    ///
    /// @brief  Set the current index
    ///
    /// @param  index location
    ///
    /// @return CamxResultSuccess  on success
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC CamxResult SetIndex(
        INT index);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetDataLimits
    ///
    /// @brief  Set the data limits
    ///
    /// @param  start         Start location
    /// @param  end           Endlocation
    /// @param  pBaseAddress  base address location
    /// @param  bufferQLength buffer Q length
    ///
    /// @return CamxResultSuccess  on success
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC CamxResult SetDataLimits(
        INT   start,
        INT   end,
        VOID* pBaseAddress,
        INT   bufferQLength);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetHaveBufLocked
    ///
    /// @brief  Set the have locked the buffer variable to true, done in case this acessor object has locked the buffer Q
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID SetHaveBufLocked();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetBufferStride
    ///
    /// @brief  Set the stride of this buffer type
    ///
    /// @param  stride stride length
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID SetBufferStride(
        UINT stride);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ClearHaveBufLocked
    ///
    /// @brief  Clear the buffer lock
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_VISIBILITY_PUBLIC VOID ClearHaveBufLocked();

private:
    INT   m_startIndexOrig;   ///< Index of the start point w.r.t to the original buffer.
    INT   m_endIndexOrig;     ///< Index of the end point with repect to the original buffer.
    UINT8* m_pBaseAddress;    ///< Base address of original sensor data buffer.
    INT   m_numSamples;       ///< Number of samples in this data object.
    INT   m_totalNumSamples;  ///< Total number of samples in the sensor buffer.
    INT   m_currentIndex;     ///< Offset from start index.
    BOOL  m_haveLockedBuffer; ///< Flag to indicate this accessor has locked buffer q for its access
    UINT  m_bufferStride;     ///< Sensor type

    NCSSensorData(const NCSSensorData&) = delete;    ///< Disallow the copy constructor
    NCSSensorData& operator=(const NCSSensorData&) = delete;    ///< Disallow assignment operator
};

CAMX_NAMESPACE_END

#endif // CAMXNCSSENSORDATA_H

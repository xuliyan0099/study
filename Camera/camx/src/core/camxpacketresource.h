////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016, 2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxpacketresource.h
/// @brief PacketResource class declaration
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXPACKETRESOURCE_H
#define CAMXPACKETRESOURCE_H

#include "camxpacketdefs.h"

CAMX_NAMESPACE_BEGIN

/// @brief Used to specify usage flags for resources. Add additional bits as necessary.
struct PacketResourceUsageFlags
{
    BIT cmdBuffer    : 1;    ///< Indicates a resource is a command buffer
    BIT packet       : 1;    ///< Indicates a resource is a packet
    BIT reserved     : 30;   ///< Reserved
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief  Class that implements the CAMX packet resource.
///         PacketResource encapsulates a CSL memory resource, mainly intended for command buffers and packets.
///         A packet resource does not own its internal memory handle; instead, it is managed by a manager that
///         will own the shared memory handle and possibly implement efficient sharing of handles among
///         multiple PacketResource objects.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PacketResource
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetMemHandle
    ///
    /// @brief  Returns the CSL memory handle backing this resource
    ///
    /// @return CSL memory handle
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE CSLMemHandle GetMemHandle()
    {
        return m_bufferInfo.hHandle;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetDeviceAddr
    ///
    /// @brief  Returns the device (physical) address of the memory for this resource.
    ///
    /// @return device (physical) address of the memory for this resource
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE CSLDeviceAddress GetDeviceAddr()
    {
        return m_bufferInfo.deviceAddr + static_cast<CSLDeviceAddress>(m_offsetInBytes);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetHostAddr
    ///
    /// @brief  Returns a pointer to the resource that can be used by the host to modify the resource's memory.
    ///
    /// @return Pointer to the memory
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID* GetHostAddr()
    {
        return static_cast<UCHAR*>(m_bufferInfo.pVirtualAddr) + m_offsetInBytes;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetOffset
    ///
    /// @brief  Returns the offset in memory
    ///
    /// @return Offset in memory
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE SIZE_T GetOffset()
    {
        return m_offsetInBytes;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetMaxLength
    ///
    /// @brief  Returns the capacity of this resource
    ///
    /// @return Capacity of the resource
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE SIZE_T GetMaxLength()
    {
        return m_sizeInBytes;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetUserData
    ///
    /// @brief  Set user data
    ///
    /// @param  pUserdata Pointer to user data
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID SetUserData(
        VOID* pUserdata)
    {
        m_pUserdata = pUserdata;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetUserData
    ///
    /// @brief  Get associated user data of resource
    ///
    /// @return User data
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID* GetUserData()
    {
        return m_pUserdata;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetUsageFlags
    ///
    /// @brief  Set user data
    ///
    /// @param  flags Usage flags
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID SetUsageFlags(
        PacketResourceUsageFlags flags)
    {
        m_usageFlags = flags;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetUsageFlags
    ///
    /// @brief  Get usage flags
    ///
    /// @return Usage flags
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE PacketResourceUsageFlags GetUsageFlags()
    {
        return m_usageFlags;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetRequestId
    ///
    /// @brief  Set the last requestId that uses this resource.
    ///
    /// @param  requestId Request this packet is associated with
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID SetRequestId(
        UINT64 requestId)
    {
        m_requestId = requestId;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetRequestId
    ///
    /// @brief  Get the last requestId that uses this resource.
    ///
    /// @return Request Id associated with this resource
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE UINT64 GetRequestId()
    {
        return m_requestId;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destroy
    ///
    /// @brief  Destroys this instance of this class.
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual VOID Destroy() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Reset
    ///
    /// @brief  Reset clears the current state of the resource to prepare for reuse.
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual VOID Reset() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetResourceUsedDwords
    ///
    /// @brief  Get the current length of valid commands in the buffer.
    ///
    /// @return UINT32 number of dwords written so far
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual UINT32 GetResourceUsedDwords()
    {
        return static_cast<UINT32>(m_sizeInBytes);
    }

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// PacketResource
    ///
    /// @brief  Constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    PacketResource();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Initialize
    ///
    /// @brief  Method to initialize a packet resource object.
    ///
    /// @param  pBufferInfo Pointer to CSL-allocated memory
    /// @param  offset      Start offset in the region of the memory hMem represents
    /// @param  size        Size of the memory region this resource can assume
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Initialize(
        const CSLBufferInfo*    pBufferInfo,
        SIZE_T                  offset,
        SIZE_T                  size);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~PacketResource
    ///
    /// @brief  Destructor.
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~PacketResource();

private:
    PacketResource(const PacketResource&)            = delete;     // Disallow the copy constructor.
    PacketResource& operator=(const PacketResource&) = delete;     // Disallow assignment operator.

    CSLBufferInfo               m_bufferInfo;       ///< Memory info of the backing buffer for this resource, retrieved from CSL
    SIZE_T                      m_offsetInBytes;    ///< The offset from the start of the memory described by mem
    SIZE_T                      m_sizeInBytes;      ///< Max size of this resource in bytes
    PacketResourceUsageFlags    m_usageFlags;       ///< Usage flags used to manage the resource
    VOID*                       m_pUserdata;        ///< User data for management
    UINT64                      m_requestId;        ///< The last request Id using this resource
};

CAMX_NAMESPACE_END

#endif // CAMXPACKETRESOURCE_H
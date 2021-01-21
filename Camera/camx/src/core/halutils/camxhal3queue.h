////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file camxhal3queue.h
/// @brief Defines a HAL3 Blocking Queue data structure
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXHAL3QUEUE_H
#define CAMXHAL3QUEUE_H

#include "camxdefs.h"
#include "camxtypes.h"
#include "camxosutils.h"

CAMX_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SlotDescriptor;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Type definitions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Queue is created as Full or Empty, memory is always allocated for capacity
enum class CreatedAs
{
    Full,   ///< Queue created as full
    Empty   ///< Queue created as empty
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief A thread safe Blocking Queue implementation suitable to contain POD for HAL request/response processing
///
///        High-level objectives of the Queue -
///
///        a. Inordered queue i.e. inordered enqueue/dequeue, but out of order release of queue elements i.e.
///           enqueue/dequeue will always happen in queue element (0, 1, 2, ... maxElements, 0, 1, ...). After queue elements
///           are dequeued, the client must inform that it is done using the queue element and the queue implementation
///           can recycle/reuse that element.
///           Since different threads may operate on different queue elements and threads could finish in any order, the
///           queue elements may be released to the queue in any random order. However, this queue implementation still
///           maintains an inordered enqueue/dequeue (irrespective of queue elements release order)
///        b. Provide thread-safe queue APIs, for parallel producer-consumer access scenarios
///        c. Dequeue without memcpy or container at client side, by keeping a separate client head
///        d. Blocking option for client, when queue is either empty or full
///
///        High-level API description  -
///
///        Enqueue                   - Moves the tail, memory ownership with queue after call returns
///        Dequeue                   - Moves the head from the perspective of client, but memory is not released
///        Release                   - Explicitly releases memory for future enqueue, makes an attempt to move the head
///        Recycle                   - First release and then enqueue the element back in a single operation
///        EnqueueWait               - Same as Enqueue, additionally waits till free space is available
///        DequeueWait               - Same as Dequeue, additionally waits till element is available
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HAL3Queue
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Create
    ///
    /// @brief  Static method to create an instance of HAL3Queue
    ///
    /// @param  maxElements         Maximum number of elements in the Queue
    /// @param  numStreamBufferInfo Size of each element of the Queue
    /// @param  createType          View this queue as full or empty when created, as memory is always allocated for
    ///                             full capacity.
    ///
    /// @return Instance pointer to be returned or NULL
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static HAL3Queue* Create(
        UINT32      maxElements,
        UINT32      numStreamBufferInfo,
        CreatedAs   createType);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Destroy
    ///
    /// @brief  Method to delete an instance of HAL3Queue
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID Destroy();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Enqueue
    ///
    /// @brief  Enqueue data to the Queue, return immediately if space is not available
    ///
    /// @param  pData Data to enqueue
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Enqueue(
        VOID* pData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EnqueueWait
    ///
    /// @brief  Enqueue data to the Queue, and wait if space is not available
    ///
    /// @param  pData The specific incoming request
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EnqueueWait(
        VOID* pData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Dequeue
    ///
    /// @brief  Dequeue data from the Queue, return immediately if empty
    ///
    /// @return Element dequeued
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID* Dequeue();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DequeueWait
    ///
    /// @brief  Dequeue data from the Queue, and wait if nothing is available
    ///
    /// @return Pointer to element dequeued
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID* DequeueWait();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Release
    ///
    /// @brief  Explicitly releases memory for future enqueue, makes an attempt to move the head
    ///
    /// @param  pData Element that is being released
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID Release(
        VOID* pData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// WaitEmpty
    ///
    /// @brief  Caller will wait till the Queue becomes empty
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID WaitEmpty();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CancelWait
    ///
    /// @brief  Enqueue will not wait if Queue is full and will not Enqueue
    ///         Dequeue will not wait if Queue is empty and will not Dequeue
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID CancelWait();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EnableWait
    ///
    /// @brief  Enqueue will wait if Queue is full
    ///         Dequeue will wait if Queue is empty
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID EnableWait();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IsEmpty
    ///
    /// @brief  Check if Queue is empty
    ///
    /// @return TRUE or FALSE
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL IsEmpty() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DumpState
    ///
    /// @brief  Dump the durrent state of the queue to a file
    ///
    /// @param  fd      file descriptor
    /// @param  indent  Number of spaces to indent
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID DumpState(
        INT     fd,
        UINT32  indent);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetRecoveryStatus
    ///
    /// @brief  Set the status of recovery
    ///
    /// @param  isRecoveryInProgress    informs the status for recovery for the session
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE VOID SetRecoveryStatus(
        BOOL isRecoveryInProgress)
    {
        m_recoveryInProgress = isRecoveryInProgress;
    }

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetSlotDescriptor
    ///
    /// @brief  Utility function to return pointer to the slot descriptor
    ///
    /// @param  slotIndex Index corresponding to the slot descriptor
    ///
    /// @return Pointer to the SlotDescriptor
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE SlotDescriptor* GetSlotDescriptor(
        UINT32 slotIndex
        ) const
    {
        CAMX_ASSERT(slotIndex < m_maxSlots);

        return (reinterpret_cast<SlotDescriptor*>(m_pDataBlob + (slotIndex * m_perSlotSize)));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// IsSlotInUse
    ///
    /// @brief  Utility function to determine if a slot is in use or not
    ///
    /// @param  slotIndex Index corresponding to the slot descriptor
    ///
    /// @return TRUE if the slot is busy/inuse, FALSE otherwise
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE BOOL IsSlotInUse(
        UINT32 slotIndex
        ) const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Initialize
    ///
    /// @brief  Initialize internal data structures for the queue
    ///
    /// @param  createType View initial Q full or empty
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Initialize(
        CreatedAs createType);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CanEnqueue
    ///
    /// @brief  Check if we can enqueue one more element in the queue (If we cannot it doesn't necessarily mean the queue is
    ///         full. It only means that the inordered slot in which we must enqueue is currently busy i.e. used by some thread
    ///         and we need to wait for that thread to release it before we can enqueue in that inordered enqueue slot)
    ///
    /// @return TRUE or FALSE
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BOOL CanEnqueue() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EnqueueCore
    ///
    /// @brief  Internal implementation for Enqueue
    ///
    /// @param  pData Data to enqueue
    ///
    /// @return CamxResultSuccess if successful
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EnqueueCore(
        VOID* pData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DequeueCore
    ///
    /// @brief  Internal implementation for Dequeue
    ///
    /// @return Pointer to element dequeued
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID* DequeueCore();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ReleaseCore
    ///
    /// @brief  Internal implementation for Release
    ///
    /// @param  pData Element that is being released
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID ReleaseCore(
        VOID* pData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// HAL3Queue
    ///
    /// @brief  Constructor for HAL3Queue object.
    ///
    /// @param  maxElements         Maximum number of elements in the Queue
    /// @param  numStreamBufferInfo Size of each element of the Queue
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    HAL3Queue(
       UINT32  maxElements,
       UINT32  numStreamBufferInfo);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~HAL3Queue
    ///
    /// @brief  Destructor for HAL3Queue object.
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~HAL3Queue();

    // Do not implement the copy constructor or assignment operator
    HAL3Queue(const HAL3Queue& rHAL3Queue) = delete;
    HAL3Queue& operator= (const HAL3Queue& rHAL3Queue) = delete;

    SIZE_T      m_perSlotDataSize;   ///< Size of each queue element client wants to add (i.e. the size of the slot data)
                                     ///  Each element corresponds to a slot in the queue and "slot data" is the data the client
                                     ///  wants to save off in that queue slot. A slot == client-slot-data + per-slot-metadata
                                     ///  per-slot-metadata == struct SlotDescriptor, so,
                                     ///  Slot = "struct SlotDescriptor + Client-Sort-Data"
    SIZE_T      m_perSlotSize;       ///< m_perSlotDataSize + sizeof per-slot-metadata
    UINT32      m_maxSlots;          ///< Maximum number of queue elements (aka slots in the queue)
    UINT32      m_head;              ///< Head position of the queue. It points to some slot in the queue.
                                     ///  Head slot is dequeued upon a dequeue request
    UINT32      m_tail;              ///< Tail position of the queue. It points to some slot in the queue.
                                     ///  Tail slot is where the new incoming enqueue request goes i.e. incoming enqueue data
                                     ///  is saved off in the slot pointed to by m_tail
    BYTE*       m_pDataBlob;         ///< Memory representing the entire queue i.e. (numSlots * perSlotSize)
    BOOL        m_cancelFullWait;    ///< wake up those waiting on Enqueue, if true, don't enqueue
    BOOL        m_cancelEmptyWait;   ///< wake up those waiting on Dequeue, if true, don't dequeue
    Mutex*      m_pQueueLock;        ///< Lock for queue operations
    Condition*  m_pWaitEmpty;        ///< Condition to wake up waiting Dequeues
    Condition*  m_pWaitFull;         ///< Condition to wake up waiting Enqueues
    Condition*  m_pWaitFlush;        ///< Condition to wake up waiting Flush

    UINT32      m_numStreamBufferInfo;  ///< Number of StreamBufferInfo structs to allocate per CaptureRequest
    BOOL        m_recoveryInProgress;   ///< Indicate if recovery is in progress
};

CAMX_NAMESPACE_END

#endif // CAMXHAL3QUEUE_H
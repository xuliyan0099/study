////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxjpegexifcomposer.h
/// @brief JPEG EXIF composer class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// @todo (CAMX-1988) Code clean up apply NC001 coding standard on entire project
/// @todo (CAMX-1989) Code clean up apply GR030 coding standard on entire project

#ifndef CAMXJPEGEXIFCOMPOSER_H
#define CAMXJPEGEXIFCOMPOSER_H

#include "camxdefs.h"
#include "camxtypes.h"
#include "camxutils.h"
#include "camxjpegexifdefs.h"
#include "camxjpegexifparams.h"
#include "camximagebuffer.h"

CAMX_NAMESPACE_BEGIN

/// @brief Exif debug data payload types
enum class ExifPayloadType
{
    ExifStatsDebugData,         ///< 3A debug data
    ExifMobicatData,            ///< Mobicat debug data
    ExifDualCamData,            ///< Dual cam debug data
    ExifOEMAppData,             ///< OEM App data
    ExifDataMax                 ///< Max
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class for JPEG EXIF composer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class JPEGEXIFComposer
{
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// JPEGEXIFComposer
    ///
    /// @brief  Default constructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    JPEGEXIFComposer();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~JPEGEXIFComposer
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~JPEGEXIFComposer();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Initialize
    ///
    /// @brief  Initalize composer
    ///
    /// @return return CamxResult
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Initialize();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AddInputMainBuf
    ///
    /// @brief  Add input buffer for main image
    ///
    /// @param  pImageBuffer  Pointer to buffer
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID AddInputMainBuf(
        ImageBuffer*  pImageBuffer);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AddInputThumbBuffer
    ///
    /// @brief  Add input buffer for thumbnail image
    ///
    /// @param  pImageBuffer  Pointer to buffer
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID AddInputThumbBuffer(
        ImageBuffer*  pImageBuffer);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// AddOutputBuf
    ///
    /// @brief  Add output buffer
    ///
    /// @param  pImageBuffer  Pointer to output buffer
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID AddOutputBuf(
        ImageBuffer*  pImageBuffer);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetParams
    ///
    /// @brief  Sets EXIF params
    ///
    /// @param  pParams  EXIF params
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID SetParams(
        JPEGEXIFParams*  pParams);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetStatsDebugData
    ///
    /// @brief  Sets Stats Debug params
    ///
    /// @param  pStatsDebugDataAddr         debug data pointer
    /// @param  statsDebugDataSize          debug data size
    /// @param  pStatsDebugHeaderString     debug header string
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID SetStatsDebugData(
       UINT8*       pStatsDebugDataAddr,
       UINT32       statsDebugDataSize,
       const CHAR*  pStatsDebugHeaderString);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SetOEMAppData
    ///
    /// @brief  Sets OEM Specific EXIF App header params
    ///
    /// @param  pOEMAppDataAddr         debug data pointer
    /// @param  OEMAppDataSize          debug data size
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID SetOEMAppData(
        UINT8*       pOEMAppDataAddr,
        UINT32       OEMAppDataSize);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// StartComposition
    ///
    /// @brief  Start EXIF composition
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult StartComposition();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GetCurrentOutBufferOffset
    ///
    /// @brief  Get current output buffer offset
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CAMX_INLINE UINT32 GetCurrentOutBufferOffset()
    {
        return m_currentOffset;
    }

private:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitByte
    ///
    /// @brief  Emit byte to exif header
    ///
    /// @param  value           Value to emit
    /// @param  pBuffer         Pointer to buffer to write to
    /// @param  pOffset         Pointer to buffer offset
    /// @param  bufferSize      Buffer size
    /// @param  endian          Flag indicating endianess 1 Big, 0 Little
    /// @param  lineNum         Caller line num for debugging
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitByte(
        UINT8    value,
        UINT8*   pBuffer,
        UINT32*  pOffset,
        UINT32   bufferSize,
        BOOL     endian,
        UINT32   lineNum);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitShort
    ///
    /// @brief  Emit short to exif header
    ///
    /// @param  value           Value to emit
    /// @param  pBuffer         Pointer to buffer to write to
    /// @param  pOffset         Pointer to buffer offset
    /// @param  bufferSize      Buffer size
    /// @param  endian          Flag indicating endianess 1 Big, 0 Little
    /// @param  lineNum         Caller line num for debugging
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitShort(
        UINT16   value,
        UINT8*   pBuffer,
        UINT32*  pOffset,
        UINT32   bufferSize,
        BOOL     endian,
        UINT32   lineNum);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitLong
    ///
    /// @brief  Emit long to exif header
    ///
    /// @param  value           Value to emit
    /// @param  pBuffer         Pointer to buffer to write to
    /// @param  pOffset         Pointer to buffer offset
    /// @param  bufferSize      Buffer size
    /// @param  endian          Flag indicating endianess 1 Big, 0 Little
    /// @param  lineNum         Caller line num for debugging
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitLong(
        UINT32   value,
        UINT8*   pBuffer,
        UINT32*  pOffset,
        UINT32   bufferSize,
        BOOL     endian,
        UINT32   lineNum);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitNBytes
    ///
    /// @brief  Emit long to exif header
    ///
    /// @param  pData           Pointer to data to emit
    /// @param  count           Data count in bytes
    /// @param  pBuffer         Pointer to buffer to write to
    /// @param  pOffset         Pointer to buffer offset
    /// @param  bufferSize      Buffer size
    /// @param  endian          Flag indicating endianess 1 Big, 0 Little
    /// @param  lineNum         Caller line num for debugging
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitNBytes(
        const UINT8*   pData,
        UINT32         count,
        UINT8*         pBuffer,
        UINT32*        pOffset,
        UINT32         bufferSize,
        BOOL           endian,
        UINT32         lineNum);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ReadShort
    ///
    /// @brief  Read short from header
    ///
    /// @param  pBuffer         Pointer to buffer to read from
    /// @param  offset          Buffer offset
    ///
    /// @return 16 bit value
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    UINT16 ReadShort(
        const UINT8* pBuffer,
        UINT32       offset);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ReadLong
    ///
    /// @brief  Read long from header
    ///
    /// @param  pBuffer         Pointer to buffer to read from
    /// @param  offset          Buffer offset
    ///
    /// @return 32 bit value
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    UINT32 ReadLong(
        const UINT8* pBuffer,
        UINT32       offset);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitEXIF
    ///
    /// @brief  Emit Exif header
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitEXIF();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitApp1
    ///
    /// @brief  Emit App1 marker
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitApp1();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitApp2
    ///
    /// @brief  Emit App2 marker
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitApp2();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitAppByType
    ///
    /// @brief  Emit App marker
    ///
    /// @param  payloadType         Exif payload type to emit
    /// @param  pPayload            Pointer to the payload
    /// @param  payloadLength       Length of the payload
    /// @param  payloadWritten      Length of payload written so far
    /// @param  recursionCount      Recurssion count
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitAppByType(
        ExifPayloadType payloadType,
        const UINT8*    pPayload,
        UINT32          payloadLength,
        UINT32          payloadWritten,
        UINT8           recursionCount);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Emit0thIFD
    ///
    /// @brief  Emit 0th IFD header
    ///
    /// @param  pEXIFIfdPointerOffset Pointer to EXIF IFD offset
    /// @param  pGPSIfdPointerOffset  Pointer to GPS IFD offset
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult Emit0thIFD(
        UINT32* pEXIFIfdPointerOffset,
        UINT32* pGPSIfdPointerOffset);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitExifIFD
    ///
    /// @brief  Emit Exif IFD header
    ///
    /// @param  pInteropIFDPointerOffset Pointer to EXIF interop IFD offset
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitExifIFD(
        UINT32* pInteropIFDPointerOffset);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitInteropIFD
    ///
    /// @brief  Emit interop IFD
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitInteropIFD();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitGPSIFD
    ///
    /// @brief  Emit GPS IFD
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitGPSIFD();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitThumbnailIFD
    ///
    /// @brief  Emit Thumbnail IFD
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitThumbnailIFD();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitFrameHeader
    ///
    /// @brief  Emit frame header
    ///
    /// @param  pImgParams  Pointer to image params
    /// @param  bThumbnail  if table for thumbnail
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitFrameHeader(
        EXIFImageParams* pImgParams,
        BOOL bThumbnail);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitScanHeader
    ///
    /// @brief  Emit scan header
    ///
    /// @param  pImgParams Pointer to image params
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitScanHeader(
        EXIFImageParams* pImgParams);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// FlushFileHeader
    ///
    /// @brief  This function is used to flush the file header
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult FlushFileHeader();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitDQT
    ///
    /// @brief  Emit DQT header, will be filled in zig-zag order
    ///
    /// @param  pQuantTable Pointer to the Quantization table
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitDQT(
        UINT16* pQuantTable);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitDHT
    ///
    /// @brief  Emit DHT header
    ///
    /// @param  pHuffTable Pointer to the Huffman table
    /// @param  index      Index to the table
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitDHT(
        HuffTable* pHuffTable,
        UINT32     index);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitSOF
    ///
    /// @brief  Emit SOF header
    ///
    /// @param  code       EXIF marker
    /// @param  pImgParams Pointer to image params
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitSOF(
        UINT8            code,
        EXIFImageParams* pImgParams);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitSOS
    ///
    /// @brief  Emit SOF header
    ///
    /// @param  pImgParams Pointer to image params
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitSOS(
        EXIFImageParams* pImgParams);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// StartIFD
    ///
    /// @brief  Start writing the IFd
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID StartIFD();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// FinishIFD
    ///
    /// @brief  Finish writing the IFd
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult FinishIFD();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// EmitEXIFTags
    ///
    /// @brief  function is used to emit Exif tag entries
    ///
    /// @param  pTagInfo Pointer to EXIT tag array
    ///
    /// @return Camx result
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    CamxResult EmitEXIFTags(
        EXIFTagInfo* pTagInfo);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Cleanup
    ///
    /// @brief  function to cleanup member variables
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VOID Cleanup();

    JPEGEXIFComposer(const JPEGEXIFComposer&) = delete;                 ///< Disallow the copy constructor.
    JPEGEXIFComposer& operator=(const JPEGEXIFComposer&) = delete;      ///< Disallow assignment operator.

    ImageBuffer*     m_pInputMainBuf;             ///< Pointer to main image buffer
    ImageBuffer*     m_pInputThumbBuffer;         ///< Pointer to main image buffer
    ImageBuffer*     m_pOutputBuf;                ///< Pointer to main image buffer
    UINT8*           m_pAheadBuf;                 ///< Pointer to ahead buffer
    JPEGEXIFParams*  m_pEXIFParams;               ///< Pointer to EXIF params
    UINT8*           m_pOutputBufAddr;            ///< Output buffer addr
    UINT8*           m_pInputBufAddr;             ///< Input buffer address
    UINT8*           m_pInputThumbBufferAddr;     ///< Input buffer address
    UINT32           m_outputBufSize;             ///< Output buffer size
    UINT32           m_currentOffset;             ///< Current output buffer offset
    UINT32           m_app1LengthOffset;          ///< App1 length location
    UINT32           m_app2LengthOffset;          ///< App2 length location
    // NOWHINE NC008: TIFF is an abbreviation as per UMD coding guidelines all abbreviation should be uppercase
    UINT32           m_TIFFHeaderOffset;          ///< TIFF header location
    UINT32           m_fieldCount;                ///< Keep count of how many tags are written
    UINT32           m_fieldCountOffset;          ///< Save the location to write the IFD count
    UINT32           m_aheadBufOffset;            ///< current offset filled within the ahead buffer
    UINT32           m_thumbnailIFDPointerOffset; ///< Save the Thumbnail IFD pointer location
    UINT32           m_thumbnailOffset;           ///< Save the thumbnail starting location
    UINT32           m_thumbnailStreamOffset;     ///< Save the thumbnail stream starting location
    BOOL             m_app1Present;               ///< Flag indicating if App1 header is present
    BOOL             m_app2Present;               ///< Flag indicating if App2 header is present
    UINT8*           m_pStatsDebugDataAddr;       ///< 3A debug data pointer
    UINT32           m_statsDebugDataSize;        ///< 3A debug data size
    UINT8*           m_pOEMAppDataAddr;           ///< OEM EXIF App data pointer
    UINT32           m_OEMAppDataSize;            ///< OEM EXIF App data size
    UINT8            m_exitAppMarkerInc;          ///< Exif app marker incrementor
    const CHAR*      m_pStatsDebugHeaderString;   ///< 3A debug header string
    UINT32           m_JPEGInterChangeLOffset;    ///< Save the offset in ThumbnailIfd specifying the end of thumbnail offset
    BOOL             m_skipThumbnailIfLarge;      ///< Flag indicating if App1 header is present
};

CAMX_NAMESPACE_END

#endif // CAMXJPEGEXIFCOMPOSER_H

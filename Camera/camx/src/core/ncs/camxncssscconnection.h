////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxncssscconnection.h
/// @brief CamX NCS ssc connection class definition
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMXNCSSSCCONNECTION_H
#define CAMXNCSSSCCONNECTION_H

// NOWHINE FILE CP006:  QSEE Sensor interface requires us to use std string class
// NOWHINE FILE CP019:  constructor explicitly
// NOWHINE FILE PR007b: QSEE Sensor interface
// NOWHINE FILE CP011:  C++ using keyword

#include <condition_variable>
#include <functional>
#include <memory>
#include <string>
#include "camxdefs.h"

CAMX_NAMESPACE_BEGIN

/* forward declaration of qmi implementation class */
class SSCQmiConnection;

/**
 * type alias for ssc connection event callback
 */
using ssc_event_cb = std::function<void(const uint8_t* data, size_t size)>;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Class that implements the NCS SSC connection
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SSCConnection
{
public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SSCConnection
    ///
    /// @brief  Constructor
    ///
    /// @param  event_cb   callback function for the connecion
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SSCConnection(
        ssc_event_cb event_cb);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ~SSCConnection
    ///
    /// @brief  Destructor
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ~SSCConnection();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// send_request
    ///
    /// @brief  send an encoded request message to sensor
    ///
    /// @param  pb_req_message_encoded encoded message
    ///
    /// @return None
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void send_request(
        const std::string& pb_req_message_encoded);

private:

    // Do not implement the copy constructor or assignment operator
    SSCConnection(const SSCConnection& connection)             = delete;
    SSCConnection& operator= (const SSCConnection& connection) = delete;

    std::unique_ptr<SSCQmiConnection> _qmi_conn;       ///< QMI connection object pointer
};

CAMX_NAMESPACE_END

#endif // CAMXNCSSSCCONNECTION_H

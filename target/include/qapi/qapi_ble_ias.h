/*
 * Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 */
// Copyright (c) 2018 Qualcomm Technologies, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below) 
// provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived 
// from this software without specific prior written permission.
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @file qapi_ble_ias.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Immediate Alert Service
 * (GATT based) API Type Definitions, Constants, and
 * Prototypes.
 *
 * @details
 * The Immediate Alert Service (IAS) programming interface defines the
 * protocols and procedures to be used to implement the Immediate Alert
 * Service capabilities.
 */

#ifndef __QAPI_BLE_IAS_H__
#define __QAPI_BLE_IAS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gatt.h"      /* qapi GATT prototypes.                    */
#include "./qapi_ble_iastypes.h"  /* QAPI IAS prototypes.                     */

/** @addtogroup qapi_ble_services
@{
*/

   /* Error Return Codes.                                               */

   /* Error Codes that are smaller than these (less than -1000) are     */
   /* related to the Bluetooth Protocol Stack itself (see               */
   /* qapi_ble_errros.h).                                               */
#define QAPI_BLE_IAS_ERROR_INVALID_PARAMETER             (-1000)
/**< Invalid parameter. */
#define QAPI_BLE_IAS_ERROR_INVALID_BLUETOOTH_STACK_ID    (-1001)
/**< Invalid Bluetooth Stack ID. */
#define QAPI_BLE_IAS_ERROR_INSUFFICIENT_RESOURCES        (-1002)
/**< Insufficent resources. */
#define QAPI_BLE_IAS_ERROR_SERVICE_ALREADY_REGISTERED    (-1003)
/**< Service is already registered. */
#define QAPI_BLE_IAS_ERROR_INVALID_INSTANCE_ID           (-1004)
/**< Invalid service instance ID. */
#define QAPI_BLE_IAS_ERROR_MALFORMATTED_DATA             (-1005)
/**< Malformatted data. */
#define QAPI_BLE_IAS_ERROR_UNKNOWN_ERROR                 (-1006)
/**< Unknown error. */

/**
 * Structure that contains the attribute handles that will need to be
 * cached by an IAS Client in order to only do service discovery once.
 */
typedef struct qapi_BLE_IAS_Client_Information_s
{
   /**
    * IAS Control Point attribute handle.
    */
   uint16_t Control_Point;
} qapi_BLE_IAS_Client_Information_t;

#define QAPI_BLE_IAS_CLIENT_INFORMATION_DATA_SIZE        (sizeof(qapi_BLE_IAS_Client_Information_t))
/**<
 * Size of the #qapi_BLE_IAS_Client_Information_t structure.
 */

/**
 * Enumeration that represents all of the valid commands that may be
 * received in an
 * QAPI_BLE_ET_IAS_SERVER_ALERT_LEVEL_CONTROL_POINT_COMMAND_E Server
 * event or that may be written to a remote IAS Server.
 */
typedef enum
{
   QAPI_BLE_CP_NO_ALERT_E   = QAPI_BLE_IAS_ALERT_LEVEL_NO_ALERT,
   /**< No alert op code. */
   QAPI_BLE_CP_MILD_ALERT_E = QAPI_BLE_IAS_ALERT_LEVEL_MILD_ALERT,
   /**< Mild alert op code. */
   QAPI_BLE_CP_HIGH_ALERT_E = QAPI_BLE_IAS_ALERT_LEVEL_HIGH_ALERT
   /**< High alert op code. */
} qapi_BLE_IAS_Control_Point_Command_t;

/**
 * Enumeration of all events generated by the IAS service.These are used to
 * determine the type of each event generated and to ensure the proper
 * union element is accessed for the #qapi_BLE_IAS_Event_Data_t structure.
 */
typedef enum   qapi_BLE_IAS_Event_Type_s
{
   QAPI_BLE_ET_IAS_SERVER_ALERT_LEVEL_CONTROL_POINT_COMMAND_E
   /**< Write Alert Level Control Point request event. */
} qapi_BLE_IAS_Event_Type_t;

/**
 * Structure that represents the format for the data that is dispatched
 * to an HTS server when an IAS client has sent a request to write the
 * IAS Control Point.
 */
typedef struct qapi_BLE_IAS_Alert_Level_Control_Point_Command_Data_s
{
   /**
    * IAS instance that dispatched the event.
    */
   uint32_t                             InstanceID;

   /**
    * GATT connection ID for the connection with the IAS Client
    * that made the request.
    */
   uint32_t                             ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the IAS client.
    */
   qapi_BLE_GATT_Connection_Type_t      ConnectionType;

   /**
    * Bluetooth address of the IAS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                   RemoteDevice;

   /**
    * IAS Control Point Command.
    */
   qapi_BLE_IAS_Control_Point_Command_t Command;
} qapi_BLE_IAS_Alert_Level_Control_Point_Command_Data_t;

#define QAPI_BLE_IAS_ALERT_LEVEL_CONTROL_POINT_COMMAND_DATA_SIZE  (sizeof(qapi_BLE_IAS_Alert_Level_Control_Point_Command_Data_t))
/**<
 * Size of the #qapi_BLE_IAS_Alert_Level_Control_Point_Command_Data_t
 * structure.
 */

/**
 * Structure that represents the container structure for holding all the
 * event data for an IAS instance.
 */
typedef struct qapi_BLE_IAS_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_IAS_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint8_t                   Event_Data_Size;
   union
   {
     /**
      * IAS Control Point Command data.
      */
     qapi_BLE_IAS_Alert_Level_Control_Point_Command_Data_t *IAS_Alert_Level_Control_Point_Command_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_IAS_Event_Data_t;

#define QAPI_BLE_IAS_EVENT_DATA_SIZE                     (sizeof(qapi_BLE_IAS_Event_Data_t))
/**<
 * Size of the #qapi_BLE_IAS_Event_Data_t structure.
 */

/**
 * @brief
 * This declared type represents the prototype function for
 * a IAS Service Event Receive Data Callback. This function will be called
 * whenever a IAS Service Event occurs that is associated with the
 * specified Bluetooth stack ID.

 * @details
 * The caller should use the contents of the IAS Profile Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (i.e., this
 * function does not have be reentrant). It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another IAS Service Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack on which the
 *                                   event occurred.
 *
 * @param[in]  IAS_Event_Data        Pointer to a structure that contains
 *                                   information about the event that has
 *                                   occurred.
 *
 * @param[in]  CallbackParameter     User-defined value that was supplied
 *                                   as an input parameter from a prior
 *                                   IAS request.
 *
 * @return None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_IAS_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_IAS_Event_Data_t *IAS_Event_Data, uint32_t CallbackParameter);

   /* IAS Server API.                                                   */

/**
 * @brief
 * Opens an IAS server on a specified Bluetooth Stack.
 *
 * @details
 * Only one IAS Server may be open at a time, per the Bluetooth Stack ID.
 *
 * All client requests will be dispatch to the EventCallback function
 * that is specified by the second parameter to this function.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallback        Callback function that is registered
 *                                  to receive events that are associated
 *                                  with the specified service.
 *
 * @param[in]  CallbackParameter    User-defined parameter that will be
 *                                  passed back to the user in the callback
 *                                  function.
 *
 * @param[out]  ServiceID           Unique GATT service ID of the
 *                                  registered IAS service returned from
 *                                  qapi_BLE_GATT_Register_Service() API.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the Service Instance ID of IAS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_IAS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_IAS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BT_GATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BT_GATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BT_GATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BT_GATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BT_GATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_IAS_Initialize_Service(uint32_t BluetoothStackID, qapi_BLE_IAS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

/**
 * @brief
 * Opens an IAS server on a specified Bluetooth Stack with
 * the ability to control the location of the service in the GATT database.
 *
 * @details
 * Only one IAS server may be open at a time, per the Bluetooth Stack ID.
 *
 * All client requests will be dispatch to the EventCallback function
 * that is specified by the second parameter to this function.
 *
 * @param[in]      BluetoothStackID      Unique identifier assigned to
 *                                       this Bluetooth Protocol Stack
 *                                       via a call to
 *                                       qapi_BLE_BSC_Initialize().
 *
 * @param[in]      EventCallback         Callback function that is
 *                                       registered to receive events
 *                                       that are associated with the
 *                                       specified service.
 *
 * @param[in]      CallbackParameter     User-defined parameter that
 *                                       will be passed back to the user
 *                                       in the callback function.
 *
 * @param[out]     ServiceID             Unique GATT Service ID of the
 *                                       registered service returned
 *                                       from
 *                                       qapi_BLE_GATT_Register_Service()
 *                                       API.
 *
 * @param[in,out]  ServiceHandleRange    Pointer to a Service Handle
 *                                       Range structure that, on input,
 *                                       can be used to control the
 *                                       location of the service in the
 *                                       GATT dataiase, and on output
 *                                       returns the handle range that
 *                                       the service is using in the GATT
 *                                       database.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the Service Instance ID of IAS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_IAS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_IAS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_IAS_ERROR_MAXIMUM_NUMBER_OF_INSTANCES_REACHED \n
 *                 QAPI_BLE_BT_GATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BT_GATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BT_GATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BT_GATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_IAS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, qapi_BLE_IAS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with a IAS Service Instance.
 *
 * @details
 * After this function is called, no other IAS service function can be
 * called until after a successful call to either of the qapi_BLE_IAS_Initialize_XXX()
 * functions are performed.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from either of the qapi_BLE_IAS_Initialize_XXX()
 *                                 functions.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_IAS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_IAS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_IAS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queries the number of attributes
 * that are contained in the BAS service that is registered with a
 * call to qapi_BLE_BAS_Initialize_Service() or
 * qapi_BLE_BAS_Initialize_Service_Handle_Range().
 *
 * @return   Positive, nonzero, number of attributes that would be
 *           registered by a BAS service instance.
 *
 * @return   Zero on failure.
 */
QAPI_BLE_DECLARATION unsigned int QAPI_BLE_BTPSAPI qapi_BLE_IAS_Query_Number_Attributes(void);

   /* IAS Client API.                                                   */

/**
 * @brief
 * Formats the IAS Control Point
 * Command into a user-specified buffer for a GATT Write request that
 * will be sent to the IAS server. This function may also be used to
 * determine the size of the buffer to hold the formatted data (see below).
 *
 * @details
 * The BufferLength and Buffer parameter must point to a buffer of at least
 * QAPI_BLE_IAS_ALERT_LEVEL_CONTROL_POINT_VALUE_LENGTH in size.
 *
 * @param[in]       Command            Enumeration for the IAS Control
 *                                     Point Command that will be formatted
 *                                     into the user-specified buffer.
 *
 * @param[in]       BufferLength       Length of the user-specified
 *                                     buffer.
 *
 * @param[out]      Buffer             User-specified buffer that
 *                                     will hold the formatted data if
 *                                     this function is successful.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_IAS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_IAS_ERROR_MALFORMATTED_DATA
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_IAS_Format_Control_Point_Command(qapi_BLE_IAS_Control_Point_Command_t Command, uint32_t BufferLength, uint8_t *Buffer);

/**
 * @}
 */

#endif


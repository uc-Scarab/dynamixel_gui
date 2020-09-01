// Auto-generated. Do not edit!

// (in-package motor_positions.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class motorPosition {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motor_id = null;
      this.position = null;
    }
    else {
      if (initObj.hasOwnProperty('motor_id')) {
        this.motor_id = initObj.motor_id
      }
      else {
        this.motor_id = 0;
      }
      if (initObj.hasOwnProperty('position')) {
        this.position = initObj.position
      }
      else {
        this.position = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type motorPosition
    // Serialize message field [motor_id]
    bufferOffset = _serializer.uint8(obj.motor_id, buffer, bufferOffset);
    // Serialize message field [position]
    bufferOffset = _serializer.uint16(obj.position, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type motorPosition
    let len;
    let data = new motorPosition(null);
    // Deserialize message field [motor_id]
    data.motor_id = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [position]
    data.position = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 3;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motor_positions/motorPosition';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '791e891bae681c33af37a246f28f5485';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8  motor_id
    uint16 position
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new motorPosition(null);
    if (msg.motor_id !== undefined) {
      resolved.motor_id = msg.motor_id;
    }
    else {
      resolved.motor_id = 0
    }

    if (msg.position !== undefined) {
      resolved.position = msg.position;
    }
    else {
      resolved.position = 0
    }

    return resolved;
    }
};

module.exports = motorPosition;

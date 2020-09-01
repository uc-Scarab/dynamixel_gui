// Auto-generated. Do not edit!

// (in-package motor_positions.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let viaPoints = require('./viaPoints.js');

//-----------------------------------------------------------

class trajectory {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.q = null;
    }
    else {
      if (initObj.hasOwnProperty('q')) {
        this.q = initObj.q
      }
      else {
        this.q = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type trajectory
    // Serialize message field [q]
    // Serialize the length for message field [q]
    bufferOffset = _serializer.uint32(obj.q.length, buffer, bufferOffset);
    obj.q.forEach((val) => {
      bufferOffset = viaPoints.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type trajectory
    let len;
    let data = new trajectory(null);
    // Deserialize message field [q]
    // Deserialize array length for message field [q]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.q = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.q[i] = viaPoints.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.q.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motor_positions/trajectory';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e22957dcc8eb24a0e55afb89801e2607';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    viaPoints[] q
    
    ================================================================================
    MSG: motor_positions/viaPoints
    uint16 motor_1
    uint16 motor_2
    uint16 motor_3
    uint16 motor_4
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new trajectory(null);
    if (msg.q !== undefined) {
      resolved.q = new Array(msg.q.length);
      for (let i = 0; i < resolved.q.length; ++i) {
        resolved.q[i] = viaPoints.Resolve(msg.q[i]);
      }
    }
    else {
      resolved.q = []
    }

    return resolved;
    }
};

module.exports = trajectory;

// File:        pb2json.h
// Description: This header file for protobuf message and json interconversion
// Notes:       ---
// Author:      Haust <wyy123_2008@qq.com>
// Revision:    2015-11-23 by Haust

#pragma once

#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#include "../thirdparty/jsoncpp1.9.0/value.h"

using std::string;

class PB2JSONHelper {
public:
    using ProtobufMsg = ::google::protobuf::Message;
    using ProtobufReflection = ::google::protobuf::Reflection;
    using ProtobufFieldDescriptor = ::google::protobuf::FieldDescriptor;
    using ProtobufDescriptor = ::google::protobuf::Descriptor;

public:
    static bool JsonString2Message(const string& strJson, ProtobufMsg& message, bool str2enum = false);
    //static void Message2Json(const ProtobufMsg& message, Json& json, bool enum2str = false);

protected:
    static bool Json2Message(const Json::Value& strJson, ProtobufMsg& message, bool str2enum = false);
    static bool Json2RepeatedMessage(const Json::Value& json, ProtobufMsg& message, const ProtobufFieldDescriptor* field,
        const ProtobufReflection* reflection, bool str2enum);
//     static void RepeatedMessage2Json(const ProtobufMsg& message, const ProtobufFieldDescriptor* field,
//                                      const ProtobufReflection* reflection, Json& json, bool enum2str);
};

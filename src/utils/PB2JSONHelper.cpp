// File:        pb2json.h
// Description: This imply file for protobuf message and json interconversion
// Notes:       ---
// Author:      Haust <wyy123_2008@qq.com>
// Revision:    2015-11-23 by Haust

#include "PB2JSONHelper.h"

#include "../thirdparty/jsoncpp1.9.0/json.h"
#include "../thirdparty/jsoncpp1.9.0/reader.h"

#include <muduo/base/Logging.h>

#include <memory>


bool PB2JSONHelper::JsonString2Message(const string& strJson, ProtobufMsg& message, bool str2enum)
{
    JSONCPP_STRING errs;
    Json::Value  JRoot;

    Json::CharReaderBuilder JBuilder;
    std::shared_ptr<Json::CharReader> pJReader(JBuilder.newCharReader());

    bool bRet = pJReader->parse(
        strJson.data(),
        strJson.data() + strJson.size(),
        &JRoot,
        &errs
    );

    if (!bRet || !errs.empty())
    {
        LOG_ERROR << "Json parse failed !!!\n" << strJson.c_str();
        return false;
    }

    auto descriptor = message.GetDescriptor();
    auto reflection = message.GetReflection();
    if (nullptr == descriptor || nullptr == reflection)
    {
        LOG_ERROR << "Json parse failed !!! nullptr == descriptor || nullptr == reflection";
        return false;
    }

    auto count = descriptor->field_count();
    LOG_DEBUG << "PB field_count:" << count;
    for (auto i = 0; i < count; ++i)
    {
        LOG_DEBUG << "PB field_count: " << count << " index: " << i;
        const auto field = descriptor->field(i);
        if (nullptr == field) {
            LOG_ERROR << "nullptr == field !!! field_count: " << count << " index: " << i;
            continue;
        }

        LOG_DEBUG << "PB field_count: " << count << " index: " << i << " field->name: " << field->name();
        if (!JRoot.isMember(field->name())) {
            LOG_ERROR << "field->name is not Member!!! field_count: " << count << " index: " << i << " field->name: " << field->name();
            continue;
        }

        auto& value = JRoot[field->name()];
        if (value.isNull())
        {
            LOG_ERROR << "field->name value is Null!!! field_count: " << count << " index: " << i << " field->name: " << field->name();
            continue;
        }

        if (field->is_repeated())
        {
            if (!value.isArray())
            {
                return false;
            } else {
                Json2RepeatedMessage(value, message, field, reflection, str2enum);
                continue;
            }
        }

        switch (field->type()) {
            case ProtobufFieldDescriptor::TYPE_BOOL: {
                if (value.isBool())
                    reflection->SetBool(&message, field, value.asBool());
                else if (value.isInt())
                    reflection->SetBool(&message, field, value.asInt() != 0);
                else if (value.isString()) {
                    if (value.asString() == "true")
                        reflection->SetBool(&message, field, true);
                    else if (value.asString() == "false")
                        reflection->SetBool(&message, field, false);
                }
            } break;

            case ProtobufFieldDescriptor::TYPE_ENUM: {
                auto const* pedesc = field->enum_type();
                const ::google::protobuf::EnumValueDescriptor* pevdesc = nullptr;

                if (str2enum) {
                    pevdesc = pedesc->FindValueByName(value.asString());
                } else {
                    pevdesc = pedesc->FindValueByNumber(value.asInt());
                }

                if (nullptr != pevdesc) {
                    reflection->SetEnum(&message, field, pevdesc);
                }
            } break;

            case ProtobufFieldDescriptor::TYPE_INT32:
            case ProtobufFieldDescriptor::TYPE_SINT32:
            case ProtobufFieldDescriptor::TYPE_SFIXED32: {
                if (value.isInt()) reflection->SetInt32(&message, field, value.asInt());
            } break;

            case ProtobufFieldDescriptor::TYPE_UINT32:
            case ProtobufFieldDescriptor::TYPE_FIXED32: {
                if (value.isUInt()) reflection->SetUInt32(&message, field, value.asUInt());
            } break;

            case ProtobufFieldDescriptor::TYPE_INT64:
            case ProtobufFieldDescriptor::TYPE_SINT64:
            case ProtobufFieldDescriptor::TYPE_SFIXED64: {
                if (value.isInt64()) reflection->SetInt64(&message, field, value.asInt64());
            } break;
            case ProtobufFieldDescriptor::TYPE_UINT64:
            case ProtobufFieldDescriptor::TYPE_FIXED64: {
                if (value.isUInt64()) reflection->SetUInt64(&message, field, value.asUInt64());
            } break;

            case ProtobufFieldDescriptor::TYPE_FLOAT: {
                if (value.isDouble()) reflection->SetFloat(&message, field, value.asFloat());
            } break;

            case ProtobufFieldDescriptor::TYPE_DOUBLE: {
                if (value.isDouble()) reflection->SetDouble(&message, field, value.asDouble());
            } break;

            case ProtobufFieldDescriptor::TYPE_STRING:
            case ProtobufFieldDescriptor::TYPE_BYTES: {
                if (value.isString()) reflection->SetString(&message, field, value.asString());
            } break;

            case ProtobufFieldDescriptor::TYPE_MESSAGE: {
                if (value.isObject()) Json2Message(value, *reflection->MutableMessage(&message, field));
            } break;

            default:
                break;
        }
    }
    return true;
}

bool PB2JSONHelper::Json2Message(const Json::Value& JValue, ProtobufMsg& message, bool str2enum)
{
    auto descriptor = message.GetDescriptor();
    auto reflection = message.GetReflection();
    if (nullptr == descriptor || nullptr == reflection) return false;

    auto count = descriptor->field_count();
    for (auto i = 0; i < count; ++i)
    {
        const auto field = descriptor->field(i);
        if (nullptr == field) {
            continue;
        }

        if (!JValue.isMember(field->name())) {
            continue;
        }

        auto& value = JValue[field->name()];
        if (value.isNull()) continue;

        if (field->is_repeated())
        {
            if (!value.isArray())
            {
                return false;
            }
            else {
                Json2RepeatedMessage(value, message, field, reflection, str2enum);
                continue;
            }
        }

        switch (field->type()) {
        case ProtobufFieldDescriptor::TYPE_BOOL: {
            if (value.isBool())
                reflection->SetBool(&message, field, value.asBool());
            else if (value.isInt())
                reflection->SetBool(&message, field, value.asInt() != 0);
            else if (value.isString()) {
                if (value.asString() == "true")
                    reflection->SetBool(&message, field, true);
                else if (value.asString() == "false")
                    reflection->SetBool(&message, field, false);
            }
        } break;

        case ProtobufFieldDescriptor::TYPE_ENUM: {
            auto const* pedesc = field->enum_type();
            const ::google::protobuf::EnumValueDescriptor* pevdesc = nullptr;

            if (str2enum) {
                pevdesc = pedesc->FindValueByName(value.asString());
            }
            else {
                pevdesc = pedesc->FindValueByNumber(value.asInt());
            }

            if (nullptr != pevdesc) {
                reflection->SetEnum(&message, field, pevdesc);
            }
        } break;

        case ProtobufFieldDescriptor::TYPE_INT32:
        case ProtobufFieldDescriptor::TYPE_SINT32:
        case ProtobufFieldDescriptor::TYPE_SFIXED32: {
            if (value.isInt()) reflection->SetInt32(&message, field, value.asInt());
        } break;

        case ProtobufFieldDescriptor::TYPE_UINT32:
        case ProtobufFieldDescriptor::TYPE_FIXED32: {
            if (value.isUInt()) reflection->SetUInt32(&message, field, value.asUInt());
        } break;

        case ProtobufFieldDescriptor::TYPE_INT64:
        case ProtobufFieldDescriptor::TYPE_SINT64:
        case ProtobufFieldDescriptor::TYPE_SFIXED64: {
            if (value.isInt64()) reflection->SetInt64(&message, field, value.asInt64());
        } break;
        case ProtobufFieldDescriptor::TYPE_UINT64:
        case ProtobufFieldDescriptor::TYPE_FIXED64: {
            if (value.isUInt64()) reflection->SetUInt64(&message, field, value.asUInt64());
        } break;

        case ProtobufFieldDescriptor::TYPE_FLOAT: {
            if (value.isDouble()) reflection->SetFloat(&message, field, value.asFloat());
        } break;

        case ProtobufFieldDescriptor::TYPE_DOUBLE: {
            if (value.isDouble()) reflection->SetDouble(&message, field, value.asDouble());
        } break;

        case ProtobufFieldDescriptor::TYPE_STRING:
        case ProtobufFieldDescriptor::TYPE_BYTES: {
            if (value.isString()) reflection->SetString(&message, field, value.asString());
        } break;

        case ProtobufFieldDescriptor::TYPE_MESSAGE: {
            if (value.isObject()) Json2Message(value, *reflection->MutableMessage(&message, field));
        } break;

        default:
            break;
        }
    }

    return true;
}

bool PB2JSONHelper::Json2RepeatedMessage(const Json::Value& json, ProtobufMsg& message, const ProtobufFieldDescriptor* field,
    const ProtobufReflection* reflection, bool str2enum) {
    int count = json.size();
    for (auto j = 0; j < count; ++j) {
        switch (field->type()) {
        case ProtobufFieldDescriptor::TYPE_BOOL: {
            if (json[j].isBool())
                reflection->AddBool(&message, field, json[j].asBool());
            else if (json[j].isNumeric())
                reflection->AddBool(&message, field, json[j].asUInt() != 0);
            else if (json[j].isString()) {
                if (json[j].asString() == "true")
                    reflection->AddBool(&message, field, true);
                else if (json[j].asString() == "false")
                    reflection->AddBool(&message, field, false);
            }
        } break;

        case ProtobufFieldDescriptor::TYPE_ENUM: {
            auto const* pedesc = field->enum_type();
            const ::google::protobuf::EnumValueDescriptor* pevdesc = nullptr;
            if (str2enum) {
                pevdesc = pedesc->FindValueByName(json[j].asString());

            }
            else {
                pevdesc = pedesc->FindValueByNumber(json[j].asInt());
            }
            if (nullptr != pevdesc) {
                reflection->AddEnum(&message, field, pevdesc);
            }

        } break;

        case ProtobufFieldDescriptor::TYPE_INT32:
        case ProtobufFieldDescriptor::TYPE_SINT32:
        case ProtobufFieldDescriptor::TYPE_SFIXED32: {
            if (json[j].isNumeric()) reflection->AddInt32(&message, field, json[j].asInt());
        } break;

        case ProtobufFieldDescriptor::TYPE_UINT32:
        case ProtobufFieldDescriptor::TYPE_FIXED32: {
            if (json[j].isNumeric()) reflection->AddUInt32(&message, field, json[j].asUInt());
        } break;

        case ProtobufFieldDescriptor::TYPE_INT64:
        case ProtobufFieldDescriptor::TYPE_SINT64:
        case ProtobufFieldDescriptor::TYPE_SFIXED64: {
            if (json[j].isNumeric()) reflection->AddInt64(&message, field, json[j].asInt64());
        } break;

        case ProtobufFieldDescriptor::TYPE_UINT64:
        case ProtobufFieldDescriptor::TYPE_FIXED64: {
            if (json[j].isNumeric()) reflection->AddUInt64(&message, field, json[j].asUInt64());
        } break;

        case ProtobufFieldDescriptor::TYPE_FLOAT: {
            if (json[j].isNumeric()) reflection->AddFloat(&message, field, json[j].asFloat());
        } break;

        case ProtobufFieldDescriptor::TYPE_DOUBLE: {
            if (json[j].isNumeric()) reflection->AddDouble(&message, field, json[j].asDouble());
        } break;

        case ProtobufFieldDescriptor::TYPE_MESSAGE: {
            if (json[j].isObject()) Json2Message(json[j], *reflection->AddMessage(&message, field));
        } break;

        case ProtobufFieldDescriptor::TYPE_STRING:
        case ProtobufFieldDescriptor::TYPE_BYTES: {
            if (json[j].isString()) reflection->AddString(&message, field, json[j].asString());
        } break;

        default:
            break;
        }
    }
    return true;
}

// void PB2JSONHelper::Message2Json(const ProtobufMsg& message, Json& json, bool enum2str) {
//     auto descriptor = message.GetDescriptor();
//     auto reflection = message.GetReflection();
//     if (nullptr == descriptor || nullptr == descriptor) return;
// 
//     auto count = descriptor->field_count();
// 
//     for (auto i = 0; i < count; ++i) {
//         const auto field = descriptor->field(i);
// 
//         if (field->is_repeated()) {
//             if (reflection->FieldSize(message, field) > 0)
//                 RepeatedMessage2Json(message, field, reflection, json[field->name()], enum2str);
// 
//             continue;
//         }
// 
//         if (!reflection->HasField(message, field)) {
//             continue;
//         }
// 
//         switch (field->type()) {
//             case ProtobufFieldDescriptor::TYPE_MESSAGE: {
//                 const ProtobufMsg& tmp_message = reflection->GetMessage(message, field);
//                 if (0 != tmp_message.ByteSize()) Message2Json(tmp_message, json[field->name()]);
//             } break;
// 
//             case ProtobufFieldDescriptor::TYPE_BOOL:
//                 json[field->name()] = reflection->GetBool(message, field) ? true : false;
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_ENUM: {
//                 auto* enum_value_desc = reflection->GetEnum(message, field);
//                 if (enum2str) {
//                     json[field->name()] = enum_value_desc->name();
//                 } else {
//                     json[field->name()] = enum_value_desc->number();
//                 }
//             } break;
// 
//             case ProtobufFieldDescriptor::TYPE_INT32:
//             case ProtobufFieldDescriptor::TYPE_SINT32:
//             case ProtobufFieldDescriptor::TYPE_SFIXED32:
//                 json[field->name()] = reflection->GetInt32(message, field);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_UINT32:
//             case ProtobufFieldDescriptor::TYPE_FIXED32:
//                 json[field->name()] = reflection->GetUInt32(message, field);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_INT64:
//             case ProtobufFieldDescriptor::TYPE_SINT64:
//             case ProtobufFieldDescriptor::TYPE_SFIXED64:
//                 json[field->name()] = reflection->GetInt64(message, field);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_UINT64:
//             case ProtobufFieldDescriptor::TYPE_FIXED64:
//                 json[field->name()] = reflection->GetUInt64(message, field);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_FLOAT:
//                 json[field->name()] = reflection->GetFloat(message, field);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_STRING:
//             case ProtobufFieldDescriptor::TYPE_BYTES:
//                 json[field->name()] = reflection->GetString(message, field);
//                 break;
// 
//             default:
//                 break;
//         }
//     }
// }
// 
// void PB2JSONHelper::RepeatedMessage2Json(const ProtobufMsg& message, const ProtobufFieldDescriptor* field,
//                                    const ProtobufReflection* reflection, Json& json, bool enum2str) {
//     if (nullptr == field || nullptr == reflection) {
//         Message2Json(message, json);
//     }
// 
//     for (auto i = 0; i < reflection->FieldSize(message, field); ++i) {
//         Json tmp_json;
//         switch (field->type()) {
//             case ProtobufFieldDescriptor::TYPE_MESSAGE: {
//                 const ProtobufMsg& tmp_message = reflection->GetRepeatedMessage(message, field, i);
//                 if (0 != tmp_message.ByteSize()) {
//                     Message2Json(tmp_message, tmp_json);
//                 }
//             } break;
// 
//             case ProtobufFieldDescriptor::TYPE_BOOL:
//                 tmp_json = reflection->GetRepeatedBool(message, field, i) ? true : false;
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_ENUM: {
//                 auto* enum_value_desc = reflection->GetRepeatedEnum(message, field, i);
//                 if (enum2str) {
//                     tmp_json = enum_value_desc->name();
//                 } else {
//                     tmp_json = enum_value_desc->number();
//                 }
//             } break;
// 
//             case ProtobufFieldDescriptor::TYPE_INT32:
//             case ProtobufFieldDescriptor::TYPE_SINT32:
//             case ProtobufFieldDescriptor::TYPE_SFIXED32:
//                 tmp_json = reflection->GetRepeatedInt32(message, field, i);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_UINT32:
//             case ProtobufFieldDescriptor::TYPE_FIXED32:
//                 tmp_json = reflection->GetRepeatedUInt32(message, field, i);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_INT64:
//             case ProtobufFieldDescriptor::TYPE_SINT64:
//             case ProtobufFieldDescriptor::TYPE_SFIXED64:
//                 tmp_json = reflection->GetRepeatedInt64(message, field, i);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_UINT64:
//             case ProtobufFieldDescriptor::TYPE_FIXED64:
//                 tmp_json = reflection->GetRepeatedUInt64(message, field, i);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_FLOAT:
//                 tmp_json = reflection->GetRepeatedFloat(message, field, i);
//                 break;
// 
//             case ProtobufFieldDescriptor::TYPE_STRING:
//             case ProtobufFieldDescriptor::TYPE_BYTES:
//                 tmp_json = reflection->GetRepeatedString(message, field, i);
//                 break;
// 
//             default:
//                 break;
//         }
//         json += tmp_json;
//     }
// }

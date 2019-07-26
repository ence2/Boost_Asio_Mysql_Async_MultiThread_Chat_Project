// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#ifndef PROTOBUF_msg_2eproto__INCLUDED
#define PROTOBUF_msg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace Msg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_msg_2eproto();
void protobuf_AssignDesc_msg_2eproto();
void protobuf_ShutdownFile_msg_2eproto();

class LoginReq;
class EnterRoomReq;
class ChatReq;

enum MessageId {
  Login = 1,
  EnterRoom = 2,
  Chat = 3
};
bool MessageId_IsValid(int value);
const MessageId MessageId_MIN = Login;
const MessageId MessageId_MAX = Chat;
const int MessageId_ARRAYSIZE = MessageId_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageId_descriptor();
inline const ::std::string& MessageId_Name(MessageId value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageId_descriptor(), value);
}
inline bool MessageId_Parse(
    const ::std::string& name, MessageId* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageId>(
    MessageId_descriptor(), name, value);
}
// ===================================================================

class LoginReq : public ::google::protobuf::Message {
 public:
  LoginReq();
  virtual ~LoginReq();
  
  LoginReq(const LoginReq& from);
  
  inline LoginReq& operator=(const LoginReq& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const LoginReq& default_instance();
  
  void Swap(LoginReq* other);
  
  // implements Message ----------------------------------------------
  
  LoginReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LoginReq& from);
  void MergeFrom(const LoginReq& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  
  // @@protoc_insertion_point(class_scope:Msg.LoginReq)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_msg_2eproto();
  friend void protobuf_AssignDesc_msg_2eproto();
  friend void protobuf_ShutdownFile_msg_2eproto();
  
  void InitAsDefaultInstance();
  static LoginReq* default_instance_;
};
// -------------------------------------------------------------------

class EnterRoomReq : public ::google::protobuf::Message {
 public:
  EnterRoomReq();
  virtual ~EnterRoomReq();
  
  EnterRoomReq(const EnterRoomReq& from);
  
  inline EnterRoomReq& operator=(const EnterRoomReq& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const EnterRoomReq& default_instance();
  
  void Swap(EnterRoomReq* other);
  
  // implements Message ----------------------------------------------
  
  EnterRoomReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EnterRoomReq& from);
  void MergeFrom(const EnterRoomReq& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional int32 roomId = 1;
  inline bool has_roomid() const;
  inline void clear_roomid();
  static const int kRoomIdFieldNumber = 1;
  inline ::google::protobuf::int32 roomid() const;
  inline void set_roomid(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:Msg.EnterRoomReq)
 private:
  inline void set_has_roomid();
  inline void clear_has_roomid();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 roomid_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_msg_2eproto();
  friend void protobuf_AssignDesc_msg_2eproto();
  friend void protobuf_ShutdownFile_msg_2eproto();
  
  void InitAsDefaultInstance();
  static EnterRoomReq* default_instance_;
};
// -------------------------------------------------------------------

class ChatReq : public ::google::protobuf::Message {
 public:
  ChatReq();
  virtual ~ChatReq();
  
  ChatReq(const ChatReq& from);
  
  inline ChatReq& operator=(const ChatReq& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const ChatReq& default_instance();
  
  void Swap(ChatReq* other);
  
  // implements Message ----------------------------------------------
  
  ChatReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChatReq& from);
  void MergeFrom(const ChatReq& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string msg = 1;
  inline bool has_msg() const;
  inline void clear_msg();
  static const int kMsgFieldNumber = 1;
  inline const ::std::string& msg() const;
  inline void set_msg(const ::std::string& value);
  inline void set_msg(const char* value);
  inline void set_msg(const char* value, size_t size);
  inline ::std::string* mutable_msg();
  inline ::std::string* release_msg();
  
  // @@protoc_insertion_point(class_scope:Msg.ChatReq)
 private:
  inline void set_has_msg();
  inline void clear_has_msg();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* msg_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_msg_2eproto();
  friend void protobuf_AssignDesc_msg_2eproto();
  friend void protobuf_ShutdownFile_msg_2eproto();
  
  void InitAsDefaultInstance();
  static ChatReq* default_instance_;
};
// ===================================================================


// ===================================================================

// LoginReq

// required string id = 1;
inline bool LoginReq::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LoginReq::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LoginReq::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LoginReq::clear_id() {
  if (id_ != &::google::protobuf::internal::kEmptyString) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& LoginReq::id() const {
  return *id_;
}
inline void LoginReq::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void LoginReq::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(value);
}
inline void LoginReq::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LoginReq::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    id_ = new ::std::string;
  }
  return id_;
}
inline ::std::string* LoginReq::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// EnterRoomReq

// optional int32 roomId = 1;
inline bool EnterRoomReq::has_roomid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EnterRoomReq::set_has_roomid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EnterRoomReq::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EnterRoomReq::clear_roomid() {
  roomid_ = 0;
  clear_has_roomid();
}
inline ::google::protobuf::int32 EnterRoomReq::roomid() const {
  return roomid_;
}
inline void EnterRoomReq::set_roomid(::google::protobuf::int32 value) {
  set_has_roomid();
  roomid_ = value;
}

// -------------------------------------------------------------------

// ChatReq

// optional string msg = 1;
inline bool ChatReq::has_msg() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChatReq::set_has_msg() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChatReq::clear_has_msg() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChatReq::clear_msg() {
  if (msg_ != &::google::protobuf::internal::kEmptyString) {
    msg_->clear();
  }
  clear_has_msg();
}
inline const ::std::string& ChatReq::msg() const {
  return *msg_;
}
inline void ChatReq::set_msg(const ::std::string& value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void ChatReq::set_msg(const char* value) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(value);
}
inline void ChatReq::set_msg(const char* value, size_t size) {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  msg_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ChatReq::mutable_msg() {
  set_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    msg_ = new ::std::string;
  }
  return msg_;
}
inline ::std::string* ChatReq::release_msg() {
  clear_has_msg();
  if (msg_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = msg_;
    msg_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Msg

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< Msg::MessageId>() {
  return Msg::MessageId_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_msg_2eproto__INCLUDED